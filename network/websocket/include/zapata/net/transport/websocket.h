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
#include <string>
#include <utility>
#include <zapata/streams.h>
#include <zapata/transport.h>

#ifndef CRLF
#define CRLF "\r\n"
#endif

namespace zpt {
namespace net {
namespace ws {
auto
handshake(zpt::stream& _stream) -> void;
auto
read(zpt::stream& _stream) -> std::tuple<std::string, int>;
auto
write(zpt::stream& _stream, std::string _in) -> void;
} // namespace ws
namespace transport {
class websocket : public zpt::transport::transport_t {
  public:
    websocket() = default;
    virtual ~websocket() = default;

    auto receive(zpt::message& _message) -> void override;
    auto send(zpt::message& _message) -> void override;
};
} // namespace transport
} // namespace net
} // namespace zpt
