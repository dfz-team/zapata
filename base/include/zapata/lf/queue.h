#pragma once

#include <memory>
#include <iterator>
#include <atomic>
#include <math.h>
#include <unistd.h>
#include <iostream>
#include <thread>

#include <zapata/lf/hptr.h>

namespace zpt {
namespace lf {
template <typename T> class queue {
  public:
    using size_type = size_t;

    queue(int _n_threads, int _n_hp_per_thread);
    queue(const queue<T>& _rhs);
    queue(queue<T>&& _rhs);
    virtual ~queue();

    queue<T>& operator=(const queue<T>& _rhs);
    queue<T>& operator=(queue<T>&& _rhs);

    T front();
    T back();

    void push(T value);
    T pop(bool _blocking = true);

  protected:
    class node {
      public:
        T __value;
        node* __next;
    };

  public:
    class iterator {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit iterator(node* _current);
        virtual ~iterator() = default;

        // BASIC ITERATOR METHODS //
        iterator& operator=(const iterator& _rhs);
        iterator& operator++();
        reference operator*() const;
        // END / BASIC ITERATOR METHODS //

        // INPUT ITERATOR METHODS //
        iterator operator++(int);
        pointer operator->() const;
        bool operator==(iterator _rhs) const;
        bool operator!=(iterator _rhs) const;
        // END / INPUT ITERATOR METHODS //

        // OUTPUT ITERATOR METHODS //
        // reference operator*() const; <- already defined
        // iterator operator++(int); <- already defined
        // END / OUTPUT ITERATOR METHODS //

        // FORWARD ITERATOR METHODS //
        // Enable support for both input and output iterator <- already enabled
        // END / FORWARD ITERATOR METHODS //

      private:
        node const* __initial;
        node* __current;
    };

    iterator begin() const;
    iterator end() const;

    friend ostream& operator<<(ostream& _out, zpt::lf::queue<T>& _in) {
        for (auto _e : _in)
            _out << _e << " " << std::flush;
        return _out;
    }

  private:
    std::atomic<node*> __head;
    std::atomic<node*> __tail;
    zpt::lf::hptr_domain<node>* __hptr;
};

template <typename T>
zpt::lf::queue<T>::queue(int _n_threads, int _n_hp_per_thread)
    : __head{nullptr}, __tail{nullptr},
      __hptr{&zpt::lf::hptr_domain<zpt::lf::queue<T>::node>::get_instance(_n_threads,
                                                                          _n_hp_per_thread)} {}

template <typename T> zpt::lf::queue<T>::~queue() {}

template <typename T> T zpt::lf::queue<T>::front() { return *this->__head.load().__value; }

template <typename T> T zpt::lf::queue<T>::back() { return *this->__tail.load().__value; }

template <typename T> void zpt::lf::queue<T>::push(T _value) {
    zpt::lf::queue<T>::node* _new = new zpt::lf::queue<T>::node{_value, nullptr};

    this->__hptr->add(_new);
    do {
        auto _tail = this->__tail.load();
        if (this->__tail.compare_exchange_strong(_tail, _new)) {
            if (_tail != nullptr) {
                _tail->__next = _new;
            }
            zpt::lf::queue<T>::node* _null_node = nullptr;
            this->__head.compare_exchange_strong(_null_node, _new);
            break;
        }
    } while (true);
}

template <typename T> T zpt::lf::queue<T>::pop(bool _blocking) {
    do {
        auto _head = this->__head.load();
        if (_head != nullptr) {
            if (this->__head.compare_exchange_strong(_head, _head->__next)) {
                this->__hptr->remove(_head);
                return _head->__value;
            }
        } else {
            if (_blocking) {
                std::this_thread::yield();
                std::chrono::milliseconds _wait_for_millis{1};
                std::this_thread::sleep_for(_wait_for_millis);
            } else {
                break;
            }
        }
    } while (true);

    return 0;
}

template <typename T> typename zpt::lf::queue<T>::iterator zpt::lf::queue<T>::begin() const {
    return zpt::lf::queue<T>::iterator{this->__head.load()};
}

template <typename T> typename zpt::lf::queue<T>::iterator zpt::lf::queue<T>::end() const {
    return zpt::lf::queue<T>::iterator{nullptr};
}

template <typename T>
zpt::lf::queue<T>::iterator::iterator(node* _current) : __initial(_current), __current(_current) {}

template <typename T>
typename zpt::lf::queue<T>::iterator& zpt::lf::queue<T>::iterator::operator=(const iterator& _rhs) {
    this->__initial = _rhs.__initial;
    this->__current = _rhs.__current;
    return (*this);
}

template <typename T>
typename zpt::lf::queue<T>::iterator& zpt::lf::queue<T>::iterator::operator++() {
    if (this->__current != nullptr) {
        this->__current = this->__current->__next;
    }
    return (*this);
}

template <typename T> T& zpt::lf::queue<T>::iterator::operator*() const {
    return this->__current->__value;
}

template <typename T>
typename zpt::lf::queue<T>::iterator zpt::lf::queue<T>::iterator::operator++(int) {
    zpt::lf::queue<T>::iterator _to_return = (*this);
    ++(*this);
    return _to_return;
}

template <typename T> T* zpt::lf::queue<T>::iterator::operator->() const {
    return &this->__current->__value;
}

template <typename T> bool zpt::lf::queue<T>::iterator::operator==(iterator _rhs) const {
    return this->__current == _rhs.__current;
}

template <typename T> bool zpt::lf::queue<T>::iterator::operator!=(iterator _rhs) const {
    return !((*this) == _rhs);
}

} // namespace lf
} // namespaace zpt
