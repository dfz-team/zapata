#pragma once

#include <zapata/lockfree/queue.h>

namespace zpt {
namespace events {

class factory {
  public:
    factory() = default;
    virtual ~factory() = default;
};

template<typename C, typename E, typename V>
class dispatcher : public factory {
  public:
    dispatcher(int _max_threads = 1, int _max_per_thread = 1);
    virtual ~dispatcher() = default;

    auto trigger(E _type, V _content) -> dispatcher&;
    auto trap() -> dispatcher&;
    template<typename F>
    auto listen(E _type, F _callback) -> dispatcher&;
    auto loop() -> void;

  public:
    zpt::lf::queue<std::tuple<E, V>> __queue;
};

} // namespace events
} // namespace zpt

template<typename C, typename E, typename V>
zpt::events::dispatcher<C, E, V>::dispatcher(int _max_threads, int _max_per_thread)
  : __queue{ _max_threads, _max_per_thread } {
    expect(_max_threads > 0, "`_max_threads` expected to be higher than 0", 500, 0);
    expect(_max_per_thread > 0, "`_max_per_thread` expected to be higher than 0", 500, 0);
}

template<typename C, typename E, typename V>
auto
zpt::events::dispatcher<C, E, V>::trigger(E _event, V _content)
  -> zpt::events::dispatcher<C, E, V>& {
    this->__queue.push(std::make_pair(_event, _content));
    return (*this);
}

template<typename C, typename E, typename V>
auto
zpt::events::dispatcher<C, E, V>::trap() -> zpt::events::dispatcher<C, E, V>& {
    auto [_event, _content] = this->__queue.pop();
    static_cast<C*>(this)->trapped(_event, _content);
    return (*this);
}

template<typename C, typename E, typename V>
template<typename F>
auto
zpt::events::dispatcher<C, E, V>::listen(E _event, F _listener)
  -> zpt::events::dispatcher<C, E, V>& {
    static_cast<C*>(this)->listen_to(_event, _listener);
    return (*this);
}

template<typename C, typename E, typename V>
auto
zpt::events::dispatcher<C, E, V>::loop() -> void {
    do {
        try {
            this->trap();
        }
        catch (zpt::NoMoreElementsException& e) {
            std::this_thread::yield();
        }
    } while (true);
}
