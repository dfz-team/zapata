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

#include <zapata/log/log.h>

#include <strings.h>
#include <sys/time.h>
#include <unistd.h>
#include <zapata/text/convert.h>

namespace zpt {
short int log_lvl = 8;
std::ostream* log_fd = &std::cout;
long log_pid = 0;
std::unique_ptr<std::string> log_pname = nullptr;
char* log_hname = nullptr;
short log_format = 0;

const char* log_lvl_names[] = { "EMERGENCY", "ALERT", "CRITICAL", "ERROR", "WARNING",
                                "NOTICE",    "INFO",  "DEBUG",    "TRACE", "VERBOSE" };
} // namespace zpt

auto
zpt::to_string(const char* _in) -> std::string {
    return std::string(_in);
}

int
zpt::log(std::string const& _text,
         zpt::LogLevel _level,
         std::string const& _host,
         int _line,
         std::string const& _file) {
    if (zpt::log_fd == nullptr) { return -1; }
    if (!zpt::log_format) {
        std::ostringstream _oss;
        _oss << zpt::log_lvl_names[_level] << " " << _text << std::endl << std::flush;
        (*zpt::log_fd) << _oss.str() << std::flush;
        return 0;
    }

    struct timeval _tp;
    gettimeofday(&_tp, nullptr);

    std::string _log;
    if (zpt::log_format == 1) {
        std::ostringstream _oss;
        _oss << zpt::tostr(time(nullptr), "%b %d %H:%M:%S") << " " << _host << " "
             << *zpt::log_pname << "[" << zpt::log_pid << "]: " << zpt::log_lvl_names[_level] << " "
             << _text;
        if (_level > 6) { _oss << " " << _file << ":" << _line; }
        _oss << std::endl << std::flush;
        (*zpt::log_fd) << _oss.str() << std::flush;
    }
    else {
        std::ostringstream _oss;
        _oss << "{\"version\":\"1.1\",\"host\":\"" << _host << "\",\"source\":\"" << _host
             << "\",\"short_message\":\"" << _text << "\",\"full_message\":\"" << _file << ":"
             << _line << " | " << zpt::r_replace(zpt::r_replace(_text, "\n", "\\n"), "\"", "\\\"")
             << "\",\"timestamp\":" << _tp.tv_sec << "." << (int)(_tp.tv_usec / 1000)
             << ",\"level\":" << (int)_level << ",\"pid\":" << zpt::log_pid << ",\"exec\":\""
             << *zpt::log_pname << "\",\"file\":\"" << _file << "\",\"line\":" << _line << "}"
             << std::endl
             << std::flush;
        (*zpt::log_fd) << _oss.str() << std::flush;
    }
    return 0;
}

char*
zpt::log_hostname() {
    if (zpt::log_hname == nullptr) {
        zpt::log_hname = new char[65];
        bzero(zpt::log_hname, 65);
        gethostname(zpt::log_hname, 64);
    }
    return zpt::log_hname;
}

extern "C" auto
zpt_base() -> int {
    return 1;
}
