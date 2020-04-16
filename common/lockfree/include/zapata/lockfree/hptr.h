/*
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or distribute
  this software, either in source code form or as a compiled binary, for any
  purpose, commercial or non-commercial, and by any means.

  In jurisdictions that recognize copyright laws, the author or authors of this
  software dedicate any and all copyright interest in the software to the public
  domain. We make this dedication for the benefit of the public at large and to
  the detriment of our heirs and successors. We intend this dedication to be an
  overt act of relinquishment in perpetuity of all present and future rights to
  this software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
  AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <atomic>
#include <iostream>
#include <iterator>
#include <map>
#include <math.h>
#include <memory>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <iomanip>

#include <zapata/base/expect.h>
#include <zapata/log/log.h>

namespace zpt {
namespace lf {

inline auto
cache_line_size() -> size_t {
    FILE* p = 0;
    p = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
    unsigned int i = 0;
    if (p) {
        if (fscanf(p, "%d", &i)) {
        }
        fclose(p);
    }
    return i;
}

template<typename T>
class hptr_domain {
  public:
    using size_type = size_t;
    static constexpr int CACHE_LINE_PADDING{ 128 / sizeof(std::atomic<T*>) };

    hptr_domain(long _max_threads, long _ptr_per_thread);
    hptr_domain(const hptr_domain<T>& _rhs) = delete;
    hptr_domain(hptr_domain<T>&& _rhs) = delete;
    virtual ~hptr_domain();

    auto operator=(const hptr_domain<T>& _rhs) -> hptr_domain<T>& = delete;
    auto operator=(hptr_domain<T>&& _rhs) -> hptr_domain<T>& = delete;

    auto operator[](size_t _idx) -> std::atomic<T*>&;
    auto at(size_t _idx) -> std::atomic<T*>&;

    auto acquire(T* _ptr) -> hptr_domain<T>&;
    auto release(T* _ptr) -> hptr_domain<T>&;
    auto retire(T* _ptr) -> hptr_domain<T>&;
    auto clean() -> hptr_domain<T>&;
    auto clear() -> hptr_domain<T>&;

    auto get_thread_dangling_count() -> size_t;
    auto release_thread_idx() -> zpt::lf::hptr_domain<T>&;

    friend auto operator<<(std::ostream& _out, zpt::lf::hptr_domain<T>& _in) -> std::ostream& {
        _out << "* zpt::lf::hptr_domain(" << std::hex << &_in << "):" << std::dec << std::endl;
        _out << "  #alive    -> " << std::dec << _in.__alive.load() << std::endl
             << "  #acquired -> " << std::dec << _in.__acquired.load() << std::endl
             << "  #released -> " << _in.__released.load() << std::endl
             << "  #retired  -> " << _in.__retired.load() << std::endl
             << std::endl
             << std::flush;
        _out << "  #config -> P = " << _in.P << " | K = " << _in.K << " | N = " << _in.N
             << " | R = " << _in.R << std::dec << std::flush;
        return _out;
    }

    class hptr_pending_list {
      public:
        hptr_pending_list() = default;
        virtual ~hptr_pending_list();

        auto operator-> () -> std::map<T*, T*>*;
        auto operator*() -> std::map<T*, T*>&;

      private:
        std::map<T*, T*> __underlying;
    };

    class guard {
      public:
        friend class zpt::lf::hptr_domain<T>;

        guard(T* _target, zpt::lf::hptr_domain<T>& _parent);
        virtual ~guard();

        auto retire() -> guard&;
        auto target() const -> T&;

      private:
        T* __target{ nullptr };
        zpt::lf::hptr_domain<T>& __parent;
        bool __retire{ false };
    };

    friend class guard;

  private:
    alignas(std::atomic<T*>) std::unique_ptr<unsigned char[]> __hp{ nullptr };
    alignas(std::atomic<bool>) std::unique_ptr<std::atomic<bool>[]> __next_thr_idx { nullptr };
    std::atomic<long> __acquired{ 0 };
    std::atomic<long> __released{ 0 };
    std::atomic<long> __alive{ 0 };
    std::atomic<long> __retired{ 0 };
    long FACTOR{ 0 };
    long P{ 0 };
    long K{ 0 };
    long N{ 0 };
    long R{ 0 };

    auto init() -> zpt::lf::hptr_domain<T>&;
    auto get_retired() -> hptr_pending_list&;
    auto get_next_available_idx() -> int;
    auto get_this_thread_idx() -> int;
};

template<typename T>
zpt::lf::hptr_domain<T>::hptr_domain(long _max_threads, long _ptr_per_thread)
  : FACTOR{ (signed)zpt::lf::cache_line_size() }
  , P{ _max_threads }
  , K{ _ptr_per_thread }
  , N{ P * K }
  , R{ N / 2 } {
    expect(_max_threads > 0,
           "Hazard pointer domain for the given template type has not been initialized",
           500,
           0);
    this->__hp = std::make_unique<unsigned char[]>(this->N * this->FACTOR);
    this->__next_thr_idx = std::make_unique<std::atomic<bool>[]>(this->P);
    this->init();
}

template<typename T>
zpt::lf::hptr_domain<T>::~hptr_domain() {
    this->clear();
}

template<typename T>
auto zpt::lf::hptr_domain<T>::operator[](size_t _idx) -> std::atomic<T*>& {
    return *reinterpret_cast<std::atomic<T*>*>(&this->__hp[_idx * this->FACTOR]);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::at(size_t _idx) -> std::atomic<T*>& {
    return *reinterpret_cast<std::atomic<T*>*>(&this->__hp[_idx * this->FACTOR]);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::acquire(T* _ptr) -> zpt::lf::hptr_domain<T>& {
    size_t _idx = zpt::lf::hptr_domain<T>::get_this_thread_idx();

    for (size_t _k = _idx * K; _k != static_cast<size_t>((_idx + 1) * K); ++_k) {
        T* _null{ nullptr };
        if (reinterpret_cast<std::atomic<T*>*>(&this->__hp[_k * this->FACTOR])
              ->compare_exchange_strong(_null, _ptr)) {
            ++this->__acquired;
            ++this->__alive;
            return (*this);
        }
    }

    expect(
      false,
      "No more hazard-pointer slots available for this thread, release some before continuing.",
      500,
      0);
    return (*this);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::release(T* _ptr) -> zpt::lf::hptr_domain<T>& {
    if (_ptr == nullptr) {
        return (*this);
    }

    int _idx{ zpt::lf::hptr_domain<T>::get_this_thread_idx() };
    for (size_t _k = _idx * K; _k != static_cast<size_t>((_idx + 1) * K); ++_k) {
        T* _exchange = _ptr;
        if (reinterpret_cast<std::atomic<T*>*>(&this->__hp[_k * this->FACTOR])
              ->compare_exchange_strong(_exchange, nullptr)) {
            ++this->__released;
            --this->__alive;
            break;
        }
    }
    return (*this);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::retire(T* _ptr) -> zpt::lf::hptr_domain<T>& {
    auto& _retired = zpt::lf::hptr_domain<T>::get_retired();
    _retired->insert(std::make_pair(_ptr, _ptr));
    if (_retired->size() == static_cast<size_t>(R)) {
        this->clean();
    }
    return (*this);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::clean() -> zpt::lf::hptr_domain<T>& {
    auto& _retired = zpt::lf::hptr_domain<T>::get_retired();

    std::map<T*, bool> _to_process;
    for (long _idx = 0; _idx != this->N; ++_idx) {
        auto* _item = reinterpret_cast<std::atomic<T*>*>(&this->__hp[_idx * this->FACTOR]);
        T* _ptr = _item->load();
        if (_ptr != nullptr) {
            _to_process.insert(std::make_pair(_ptr, true));
        }
    }

    for (auto _it = _retired->begin(); _it != _retired->end();) {
        if (_to_process.find(_it->first) == _to_process.end()) {
            delete _it->first;
            ++this->__retired;
            _it = _retired->erase(_it);
        }
        else {
            ++_it;
        }
    }

    return (*this);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::clear() -> zpt::lf::hptr_domain<T>& {
    std::map<T*, bool> _to_process;
    for (long _idx = 0; _idx != this->N; ++_idx) {
        auto* _item = reinterpret_cast<std::atomic<T*>*>(&this->__hp[_idx * this->FACTOR]);
        T* _ptr = _item->load();
        if (_ptr != nullptr) {
            if (_item->compare_exchange_strong(_ptr, nullptr)) {
                ++this->__released;
                --this->__alive;
            }
            _to_process.insert(std::make_pair(_ptr, true));
        }
    }
    std::for_each(
      _to_process.begin(), _to_process.end(), [&](const std::pair<T*, bool>& _item) -> void {
          ++this->__retired;
          delete _item.first;
      });
    return (*this);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::get_thread_dangling_count() -> size_t {
    auto& _retired = zpt::lf::hptr_domain<T>::get_retired();
    return _retired->size();
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::release_thread_idx() -> zpt::lf::hptr_domain<T>& {
    int _idx = this->get_this_thread_idx();

    std::map<T*, bool> _to_process;
    for (long _k = _idx * K; _k != static_cast<size_t>((_idx + 1) * K); ++_k) {
        T* _exchange = reinterpret_cast<std::atomic<T*>*>(&this->__hp[_idx * this->FACTOR])->load();
        if (_exchange != nullptr &&
            reinterpret_cast<std::atomic<T*>*>(&this->__hp[_idx * this->FACTOR])
              ->compare_exchange_strong(_exchange, nullptr)) {
            ++this->__released;
            --this->__alive;
        }
        _to_process.insert(std::make_pair(_exchange, true));
    }
    std::for_each(
      _to_process.begin(), _to_process.end(), [&](const std::pair<T*, bool>& _item) -> void {
          ++this->__retired;
          delete _item.first;
      });
    this->__next_thr_idx[_idx] = false;

    return (*this);
}

template<typename T>
zpt::lf::hptr_domain<T>::hptr_pending_list::~hptr_pending_list() {
    for (auto _it = this->__underlying.begin(); _it != this->__underlying.end(); ++_it) {
        delete _it->first;
    }
}

template<typename T>
auto zpt::lf::hptr_domain<T>::hptr_pending_list::operator-> () -> std::map<T*, T*>* {
    return &this->__underlying;
}

template<typename T>
auto zpt::lf::hptr_domain<T>::hptr_pending_list::operator*() -> std::map<T*, T*>& {
    return this->__underlying;
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::init() -> zpt::lf::hptr_domain<T>& {
    for (long _idx = 0; _idx != this->N; ++_idx) {
        ::new (&this->__hp[_idx * this->FACTOR]) std::atomic<T*>();
    }
    return (*this);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::get_retired() -> zpt::lf::hptr_domain<T>::hptr_pending_list& {
    thread_local static hptr_pending_list _retired;
    return _retired;
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::get_next_available_idx() -> int {
    long _idx{ 0 };
    for (; _idx != this->P; ++_idx) {
        bool _acquired{ false };
        if (this->__next_thr_idx[_idx].compare_exchange_strong(_acquired, true)) {
            break;
        }
    }
    return _idx;
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::get_this_thread_idx() -> int {
    thread_local static int _idx = this->get_next_available_idx();
    return _idx;
}

template<typename T>
zpt::lf::hptr_domain<T>::guard::guard(T* _ptr, zpt::lf::hptr_domain<T>& _parent)
  : __target{ _ptr }
  , __parent{ _parent } {
    this->__parent.acquire(this->__target);
}

template<typename T>
zpt::lf::hptr_domain<T>::guard::~guard() {
    this->__parent.release(this->__target);
    if (this->__retire)
        this->__parent.retire(this->__target);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::guard::retire() -> guard& {
    this->__retire = true;
    return (*this);
}

template<typename T>
auto
zpt::lf::hptr_domain<T>::guard::target() const -> T& {
    return *this->__target;
}

} // namespace lf
} // namespace zpt
