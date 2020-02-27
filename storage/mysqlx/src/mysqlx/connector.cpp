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

#include <zapata/connector/connector.h>

zpt::storage::connection::connection(zpt::storage::connection const& _rhs)
  : __underlying{ _rhs.__underlying.get() } {}

zpt::storage::connection::connection(zpt::storage::connection&& _rhs)
  : __underlying{ _rhs.__underlying.get() } {
    _rhs.__underlying.reset();
}

auto
zpt::storage::connection::operator=(zpt::storage::connection const& _rhs)
  -> zpt::storage::connection& {
    this->__underlying = _rhs.__underlying;
    return (*this);
}

auto
zpt::storage::connection::operator=(zpt::storage::connection&& _rhs) -> zpt::storage::connection& {
    this->__underlying.swap(_rhs.__underlying);
    return (*this);
}

auto zpt::storage::connection::operator-> () -> zpt::storage::connection::type* {
    return this->__underlying.get();
}

auto zpt::storage::connection::operator*() -> zpt::storage::connection::type& {
    return *this->__underlying.get();
}

zpt::storage::session::session(zpt::storage::session const& _rhs)
  : __underlying{ _rhs.__underlying.get() } {}

zpt::storage::session::session(zpt::storage::session&& _rhs)
  : __underlying{ _rhs.__underlying.get() } {
    _rhs.__underlying.reset();
}

auto
zpt::storage::session::operator=(zpt::storage::session const& _rhs)
  -> zpt::storage::session& {
    this->__underlying = _rhs.__underlying;
    return (*this);
}

auto
zpt::storage::session::operator=(zpt::storage::session&& _rhs) -> zpt::storage::session& {
    this->__underlying.swap(_rhs.__underlying);
    return (*this);
}

auto zpt::storage::session::operator-> () -> zpt::storage::session::type* {
    return this->__underlying.get();
}

auto zpt::storage::session::operator*() -> zpt::storage::session::type& {
    return *this->__underlying.get();
}

zpt::storage::database::database(zpt::storage::database const& _rhs)
  : __underlying{ _rhs.__underlying.get() } {}

zpt::storage::database::database(zpt::storage::database&& _rhs)
  : __underlying{ _rhs.__underlying.get() } {
    _rhs.__underlying.reset();
}

auto
zpt::storage::database::operator=(zpt::storage::database const& _rhs)
  -> zpt::storage::database& {
    this->__underlying = _rhs.__underlying;
    return (*this);
}

auto
zpt::storage::database::operator=(zpt::storage::database&& _rhs) -> zpt::storage::database& {
    this->__underlying.swap(_rhs.__underlying);
    return (*this);
}

auto zpt::storage::database::operator-> () -> zpt::storage::database::type* {
    return this->__underlying.get();
}

auto zpt::storage::database::operator*() -> zpt::storage::database::type& {
    return *this->__underlying.get();
}

zpt::storage::collection::collection(zpt::storage::collection const& _rhs)
  : __underlying{ _rhs.__underlying.get() } {}

zpt::storage::collection::collection(zpt::storage::collection&& _rhs)
  : __underlying{ _rhs.__underlying.get() } {
    _rhs.__underlying.reset();
}

auto
zpt::storage::collection::operator=(zpt::storage::collection const& _rhs)
  -> zpt::storage::collection& {
    this->__underlying = _rhs.__underlying;
    return (*this);
}

auto
zpt::storage::collection::operator=(zpt::storage::collection&& _rhs) -> zpt::storage::collection& {
    this->__underlying.swap(_rhs.__underlying);
    return (*this);
}

auto zpt::storage::collection::operator-> () -> zpt::storage::collection::type* {
    return this->__underlying.get();
}

auto zpt::storage::collection::operator*() -> zpt::storage::collection::type& {
    return *this->__underlying.get();
}

zpt::storage::filter::filter(zpt::storage::filter const& _rhs)
  : __underlying{ _rhs.__underlying.get() } {}

zpt::storage::filter::filter(zpt::storage::filter&& _rhs)
  : __underlying{ _rhs.__underlying.get() } {
    _rhs.__underlying.reset();
}

auto
zpt::storage::filter::operator=(zpt::storage::filter const& _rhs)
  -> zpt::storage::filter& {
    this->__underlying = _rhs.__underlying;
    return (*this);
}

auto
zpt::storage::filter::operator=(zpt::storage::filter&& _rhs) -> zpt::storage::filter& {
    this->__underlying.swap(_rhs.__underlying);
    return (*this);
}

auto zpt::storage::filter::operator-> () -> zpt::storage::filter::type* {
    return this->__underlying.get();
}

auto zpt::storage::filter::operator*() -> zpt::storage::filter::type& {
    return *this->__underlying.get();
}

zpt::storage::result::result(zpt::storage::result const& _rhs)
  : __underlying{ _rhs.__underlying.get() } {}

zpt::storage::result::result(zpt::storage::result&& _rhs)
  : __underlying{ _rhs.__underlying.get() } {
    _rhs.__underlying.reset();
}

auto
zpt::storage::result::operator=(zpt::storage::result const& _rhs)
  -> zpt::storage::result& {
    this->__underlying = _rhs.__underlying;
    return (*this);
}

auto
zpt::storage::result::operator=(zpt::storage::result&& _rhs) -> zpt::storage::result& {
    this->__underlying.swap(_rhs.__underlying);
    return (*this);
}

auto zpt::storage::result::operator-> () -> zpt::storage::result::type* {
    return this->__underlying.get();
}

auto zpt::storage::result::operator*() -> zpt::storage::result::type& {
    return *this->__underlying.get();
}
