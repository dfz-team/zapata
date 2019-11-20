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

#include <fstream>
#include <iostream>
#include <signal.h>
#include <string>
#include <unistd.h>

#include <semaphore.h>
#include <zapata/base.h>
#include <zapata/events.h>
#include <zapata/json.h>

int
main(int argc, char* argv[]) {
    try {
        zpt::options(argc, argv);
    }
    catch (zpt::missed_expectation& _e) {
        zlog(_e.what() + std::string(" | ") + _e.description(), zpt::emergency);
        zlog(std::string("\n") + _e.backtrace(), zpt::trace);
        exit(-10);
    }
    catch (std::exception& _e) {
        zlog(_e.what(), zpt::emergency);
        exit(-10);
    }

    return 0;
}

extern "C" auto
zpt_rest() -> int {
    return 1;
}
