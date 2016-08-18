/*
The MIT License (MIT)

Copyright (c) 2014 n@zgul <naazgull@dfz.pt>

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

#include <zapata/text/convert.h>
#include <zapata/base/assert.h>
#include <time.h>
#include <sys/time.h>

void zpt::tostr(std::string& s, int i){
	std::ostringstream _oss;
	_oss << i << flush;
	s.insert(s.length(), _oss.str());
}

void zpt::tostr(std::string& s, bool b){
	s.insert(s.length(), b ? "true" : "false");
}

void zpt::tostr(std::string& s, int i, std::ios_base& (&hex)(std::ios_base&)) {
	char oss[512];
	sprintf(oss,"%x", i);
	s.insert(s.length(), oss);
}

#ifdef __LP64__
void zpt::tostr(std::string& s, unsigned int i){
	std::ostringstream _oss;
	_oss << i << flush;
	s.insert(s.length(), _oss.str());
}
#endif

void zpt::tostr(std::string& s, size_t i){
	std::ostringstream _oss;
	_oss << i << flush;
	s.insert(s.length(), _oss.str());
}

void zpt::tostr(std::string& s, long i){
	std::ostringstream _oss;
	_oss << i << flush;
	s.insert(s.length(), _oss.str());
}

void zpt::tostr(std::string& s, long long i){
	std::ostringstream _oss;
	_oss << i << flush;
	s.insert(s.length(), _oss.str());
}

void zpt::tostr(std::string& s, float i){
	std::ostringstream _oss;
	_oss << i << flush;
	s.insert(s.length(), _oss.str());
}

void zpt::tostr(std::string& s, double i){
	std::ostringstream _oss;
	_oss << i << flush;
	s.insert(s.length(), _oss.str());
}

void zpt::tostr(std::string& s, char i){
	std::ostringstream _oss;
	_oss << i << flush;
	s.insert(s.length(), _oss.str());
}

void zpt::tostr(string& s, time_t i, const char* f){
	std::string _current(zpt::get_tz());
	setenv("TZ", "UTC", 1);
	tzset();
	struct tm _ptm;
	char _buffer_date[80];
	bzero(_buffer_date, 80);
	localtime_r(&i, &_ptm);
	strftime(_buffer_date, 80, f, &_ptm);
	s.insert(s.length(), _buffer_date);
	setenv("TZ", _current.data(), 1);
	tzset();
}

std::string zpt::tostr(int i){
	std::ostringstream _oss;
	_oss << i << flush;
	return _oss.str();
}

std::string zpt::tostr(bool b){
	return b ? "true" : "false";
}

std::string zpt::tostr(int i, std::ios_base& (&hex)(std::ios_base&)) {
	char oss[512];
	sprintf(oss,"%x", i);
	return string(oss);
}

#ifdef __LP64__
std::string zpt::tostr(unsigned int i){
	std::ostringstream _oss;
	_oss << i << flush;
	return _oss.str();
}
#endif

std::string zpt::tostr(size_t i){
	std::ostringstream _oss;
	_oss << i << flush;
	return _oss.str();
}

std::string zpt::tostr(long i){
	std::ostringstream _oss;
	_oss << i << flush;
	return _oss.str();
}

std::string zpt::tostr(long long i){
	std::ostringstream _oss;
	_oss << i << flush;
	return _oss.str();
}

std::string zpt::tostr(float i){
	std::ostringstream _oss;
	_oss << i << flush;
	return _oss.str();
}

std::string zpt::tostr(double i){
	std::ostringstream _oss;
	_oss << i << flush;
	return _oss.str();
}

std::string zpt::tostr(char i){
	std::ostringstream _oss;
	_oss << i << flush;
	return _oss.str();
}

std::string zpt::tostr(time_t i, const char* f){
	struct tm _ptm;
	char _buffer_date[80];
	bzero(_buffer_date, 80);
	localtime_r(&i, &_ptm);
	strftime(_buffer_date, 80, f, &_ptm);
	return string(_buffer_date);
}

void zpt::fromstr(std::string s, int* i){
	std::istringstream _in;
	_in.str(s);
	_in >> (* i);
}

#ifdef __LP64__
void zpt::fromstr(std::string s, unsigned int* i){
	std::istringstream _in;
	_in.str(s);
	_in >> (* i);
}
#endif

void zpt::fromstr(std::string s, size_t* i){
#ifdef __LP64__
	std::istringstream _in;
	_in.str(s);
	_in >> (* i);
#else
	std::istringstream _in;
	_in.str(s);
	_in >> (* i);
#endif
}

void zpt::fromstr(std::string s, long* i){
	std::istringstream _in;
	_in.str(s);
	_in >> (* i);
}

void zpt::fromstr(std::string s, long long* i){
	std::istringstream _in;
	_in.str(s);
	_in >> (* i);
}

void zpt::fromstr(std::string s, float* i){
	std::istringstream _in;
	_in.str(s);
	_in >> (* i);
}

void zpt::fromstr(std::string s, double* i){
	std::istringstream _in;
	_in.str(s);
	_in >> (* i);
}

void zpt::fromstr(std::string s, char* i){
	std::istringstream _in;
	_in.str(s);
	_in >> (* i);
}

void zpt::fromstr(std::string s, bool* i){
	*i = s == string("true");
}

void zpt::fromstr(std::string s, time_t* i, const char* f) {
	std::string _current(zpt::get_tz());
	bool _use_utc = (string(f).find("%Z") == string::npos);
	if (_use_utc) {
		setenv("TZ", "UTC", 1);
		tzset();
	}
	struct tm tm[1] = { { 0 } };
	strptime(s.data(), f, tm);
	if (!_use_utc) {
		tzset();
		struct timeval tv;
		struct timezone _current_tz = { 0, 0 };
		gettimeofday(&tv, &_current_tz);

		tm->tm_isdst = _current_tz.tz_dsttime;
		tm->tm_gmtoff = zpt::timezone_offset();
		tm->tm_zone =_current_tz.tz_dsttime == 0 ? tzname[0] : tzname[1];
	} 
	*i = mktime(tm);
	if (_use_utc) {
		setenv("TZ", _current.data(), 1);
		tzset();
	}
}

time_t zpt::timezone_offset() {
	time_t t;
	tm *ptr;
	int day;
	unsigned long num[2];
	t = time(NULL);
	ptr = gmtime(&t); // Standard UTC time
	// Get difference in seconds
	num[0] = (ptr->tm_hour * 3600) + (ptr->tm_min * 60);
	day = ptr->tm_mday;
	ptr = localtime(&t); // Local time w/ time zone
	num[1] = (ptr->tm_hour * 3600) + (ptr->tm_min * 60);
	// If not the same then get difference
	if (day == ptr->tm_mday) { // No date difference
		if (num[0] < num[1]) {
			return (num[1] - num[0]);// Positive ex. CUT +1
		}
		else if (num[0] > num[1]) {
			return -(num[0] - num[1]);// Negative ex. Pacific -8
		}
	}
	else if (day < ptr->tm_mday) {// Ex. 1: 30 am Jan 1 : 11: 30 pm Dec 31
		return (86400 - num[0]) + num[1];
	}
	else {
		return -((86400 - num[1]) + num[0]);// Opposite
	}
	return 0;
}
