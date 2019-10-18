/*
The MIT License (MIT)

Copyright (c) 2017 n@zgul <n@zgul.me>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <zapata/base.h>
#include <zapata/json.h>
#include <zmq.h>
#include <zmq.hpp>

namespace zmq {
typedef std::shared_ptr<zmq::socket_t> channel_ptr;
}

namespace zpt {

class drop;
class pipeline;

using callback = std::function<bool(zpt::drop&)>;
using pipe = zpt::lf::queue<std::shared_ptr<zpt::drop>>;

auto
options(zpt::json _options = zpt::undefined) -> zpt::json&;
auto
options(int argc, char* argv[]) -> zpt::json&;

class abstract_channel {
  public:
    abstract_channel(std::string _connection, zpt::json _options);
    virtual ~abstract_channel() = default;

    virtual auto id() -> std::string;
    virtual auto options() -> zpt::json;
    virtual auto connection() -> std::string;
    virtual auto connection(std::string _connection) -> zpt::abstract_channel&;
    virtual auto uri(size_t _idx = 0) -> zpt::json;
    virtual auto uri(std::string _connection) -> zpt::abstract_channel&;
    // virtual auto detach() -> void;
    // virtual auto available() -> bool;

    virtual auto recv() -> zpt::json = 0;
    virtual auto send(zpt::json _envelope) -> zpt::abstract_channel& = 0;
    virtual auto close() -> zpt::abstract_channel& = 0;
    // virtual auto loop_iteration() -> void;

    // virtual auto in() -> zmq::channel_ptr = 0;
    // virtual auto out() -> zmq::channel_ptr = 0;
    // virtual auto fd() -> int = 0;
    // virtual auto in_mtx() -> std::mutex& = 0;
    // virtual auto out_mtx() -> std::mutex& = 0;
    // virtual auto type() -> short int = 0;
    // virtual auto protocol() -> std::string = 0;
    // virtual auto is_reusable() -> bool = 0;

  private:
    zpt::json __options{ zpt::undefined };
    std::string __connection{ "" };
    std::string __id{ "" };
    zpt::json __uri{ zpt::undefined };
};

class abstract_channel_factory {
  public:
    abstract_channel_factory() = default;
    virtual ~abstract_channel_factory() = default;

    virtual auto produce(zpt::json _options) -> zpt::abstract_channel& = 0;
    virtual auto dispose(zpt::abstract_channel& _socket) -> bool = 0;
    virtual auto is_reusable(std::string _type) const -> bool = 0;
    virtual auto protocol() const -> std::string = 0;
};

template<typename T>
class channel : public abstract_channel {
  public:
    channel(std::string _connection, zpt::json _options);
    virtual ~channel();
};

template<typename T>
class channel_factory : public abstract_channel_factory {
  public:
    channel_factory(std::string _protocol);
    virtual ~channel_factory();

    virtual auto produce(zpt::json _options) -> zpt::abstract_channel&;
    virtual auto dispose(zpt::abstract_channel& _socket) -> bool;
    virtual auto is_reusable(std::string _type) const -> bool;
    virtual auto protocol() const -> std::string;

  private:
    std::string __protocol{ "" };
};

class drop {
  public:
    drop(zpt::json _content, zpt::abstract_channel& _channel);
    drop(const zpt::drop& _rhs) = delete;
    drop(zpt::drop&& _rhs) = delete;
    virtual ~drop();

    auto operator=(const zpt::drop& _rhs) -> zpt::drop& = delete;
    auto operator=(zpt::drop&& _rhs) -> zpt::drop& = delete;

    operator zpt::abstract_channel&() const;
    operator zpt::json() const;

    auto operator=(zpt::json _rhs) -> zpt::drop&;

    auto forward() -> zpt::drop&;
    auto finish() -> zpt::drop&;
    auto route(zpt::json _request) -> zpt::drop&;

  private:
    size_t __stage{ 0 };
    zpt::json __content{ zpt::undefined };
    zpt::abstract_channel& __channel;
    std::shared_ptr<zpt::drop> __dependency{ nullptr };
};

class service_graph {
  public:
    class node {
      public:
        node(std::string _topic);
        virtual ~node();

        auto find(zpt::json _topic) -> zpt::service_graph::node&;
        auto insert(zpt::json _topic) -> zpt::service_graph::node&;

      private:
        std::regex __resolver;
        std::vector<std::tuple<std::regex, zpt::callback>> __callbacks;
        std::vector<zpt::service_graph::node> __children;

        node(zpt::json _splited, std::regex& _original_topic);

        auto find(zpt::json::iterator _topic) -> zpt::service_graph::node&;
        auto insert(zpt::json::iterator _topic) -> zpt::service_graph::node&;
    };

    service_graph();
    virtual ~service_graph();

    virtual auto insert(std::string _topic, zpt::service_graph::node _node) -> zpt::service_graph&;
    virtual auto find(std::string _topic, zpt::performative _performative)
      -> zpt::service_graph::node;
    virtual auto remove(std::string _uuid) -> zpt::service_graph&;
    virtual auto list(std::string _uuid = "") -> zpt::json;
    virtual auto pretty(std::string _tabs = "", bool _last = false) -> std::string;

  private:
    std::string __resolver;
    zpt::service_graph::node __root;
    std::map<std::string, zpt::service_graph> __children;

    auto merge(zpt::service_graph::node _service) -> void;
    auto insert(zpt::json _topic, zpt::service_graph::node _service) -> zpt::service_graph&;
    auto find(std::string _topic, zpt::json _splited, zpt::performative _performative)
      -> zpt::service_graph::node;
};

class pipeline {
  public:
    pipeline(std::string _name, zpt::json _options);
    pipeline(const zpt::pipeline& _rhs) = delete;
    pipeline(zpt::pipeline&& _rhs) = delete;
    virtual ~pipeline();

    virtual auto name() -> std::string;
    virtual auto uuid() -> std::string;
    virtual auto options() -> zpt::json;

    virtual auto on(size_t _stage,
                    std::initializer_list<std::tuple<std::string, zpt::callback>> _callbacks)
      -> zpt::pipeline&;

    virtual auto add(std::unique_ptr<zpt::abstract_channel_factory> _factory) -> zpt::pipeline&;

    virtual auto loop() -> void;

    auto operator=(const zpt::pipeline& _rhs) -> zpt::pipeline& = delete;
    auto operator=(zpt::pipeline&& _rhs) -> zpt::pipeline& = delete;

  private:
    std::string __name{ "" };
    std::string __uuid{ zpt::generate::r_uuid() };
    zpt::json __options{ zpt::undefined };
    std::map<std::string, std::unique_ptr<zpt::abstract_channel_factory>> __factories;
    zpt::pipe __drops;
    zpt::service_graph __services;
};

namespace uri {
auto
get_simplified_topics(std::string _pattern) -> zpt::json;
}

// extern pid_t root;
// extern bool interrupted;

// auto terminate(int _signal) -> void;
// auto shutdown(int _signal) -> void;

// namespace authorization {
// auto serialize(zpt::json _info) -> std::string;
// auto deserialize(std::string _token) -> zpt::json;
// auto extract(zpt::json _envelope) -> std::string;
// auto headers(std::string _token) -> zpt::json;
// auto validate(std::string _topic,
// 	      zpt::json _envelope,
// 	      zpt::ev::emitter _emitter,
// 	      zpt::json _roles_needed = zpt::undefined) -> zpt::json;
// auto has_roles(zpt::json _indentity, zpt::json _roles_needed) -> bool;
// }

// namespace scopes {
// std::string serialize(zpt::json _info);
// zpt::json deserialize(std::string _scope);
// bool has_permission(std::string _scope, std::string _ns, std::string
// _permissions);
// bool has_permission(zpt::json _scope, std::string _ns, std::string
// _permissions);
// }
} // namespace zpt