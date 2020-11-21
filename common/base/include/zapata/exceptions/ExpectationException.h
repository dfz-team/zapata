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

#include <exception>
#include <iostream>
#include <string>

namespace zpt {

class ExpectationException : public std::exception {
  public:
    ExpectationException(std::string const& _what,
                         int _http_code,
                         int _code,
                         std::string _desc,
                         int _line = 0,
                         std::string _file = "");
    ExpectationException(std::string const& _what,
                         int _http_code,
                         int _code,
                         std::string _desc,
                         int _line,
                         std::string _file,
                         char** _backtrace,
                         size_t _backtrace_size);
    virtual ~ExpectationException() throw();

    virtual auto what() const noexcept -> const char* override;
    virtual auto description() const -> const char*;
    virtual auto backtrace() const -> const char*;
    virtual auto code() const -> int;
    virtual auto status() const -> int;

    friend auto operator<<(std::ostream& _out, zpt::ExpectationException const& _in)
      -> std::ostream& {
        _out << _in.description() << ": " << _in.what() << " ERROR(" << _in.code() << ")";
        return _out;
    }

  private:
    std::string __what;
    int __http_code;
    int __code;
    std::string __description;
    int __line;
    std::string __file;
    std::string __backtrace;
};

using failed_expectation = ExpectationException;
} // namespace zpt