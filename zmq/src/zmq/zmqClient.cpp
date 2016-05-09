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

#include <zapata/zmq/ZMQPolling.h>

zapata::ZMQ::ZMQ(std::string _connection) : __context( 1), __connection(_connection), __self(this) {
}

zapata::ZMQ::~ZMQ() {
}

zapata::JSONObj& zapata::ZMQ::options() {
	return this->__options;
}

zmq::context_t& zapata::ZMQ::context() {
	return this->__context;
}

std::string& zapata::ZMQ::connection() {
	return this->__connection;
}

zapata::ZMQPtr zapata::ZMQ::self() {
	return this->__self;
}

zapata::JSONPtr zapata::ZMQ::recv() {
	std::vector<std::string> _parts;
	int _more = 0;
	size_t _more_size = sizeof (_more);

	do {
		zmq::message_t _request;
		try {
			this->in().recv(& _request);
		}
		catch(zmq::error_t& e) {
			throw;
		}
		_parts.push_back(string(static_cast<char*>(_request.data()), _request.size()));

		_more = 0;
		this->in().getsockopt(ZMQ_RCVMORE, & _more, & _more_size);
	}
	while(_more);

	string _method_url(_parts[0]);
	string _body(_parts[_parts.size() - 1]);

	zapata::JSONPtr _headers = zapata::make_obj();
	if (_parts.size() > 2) {
		for (size_t _idx = 1; _idx != _parts.size() - 1; _idx++) {
			zapata::JSONPtr _pair = zapata::split(_parts[_idx], ":");
			std::string _key(_pair[0]->str());
			std::string _value(_pair[1]->str());
			zapata::trim(_key);
			zapata::trim(_value);
			_headers << _key << _value;
		}
	}

	zapata::JSONPtr _payload;
	std::istringstream _iss;
	_iss.str(_body);
	try {
		_iss >> _payload;
	}
	catch(zapata::SyntaxErrorException& _e) {
		_payload = zapata::undefined;
	}

	if (_method_url.find(" ") != string::npos) {
		std::string _method_str(_method_url.substr(0, _method_url.find(" ")));
		std::string _url(_method_url.substr(_method_url.find(" ") + 1));

		return zapata::make_ptr(JSON(
			"performative" << zapata::ev::from_str(_method_str) <<
			"resource" << _url <<
			"headers" << _headers <<
			"payload" << _payload
		));
	}
	else {
		return zapata::make_ptr(JSON(
			"status" << std::stoi(_method_url) <<
			"headers" << _headers <<
			"payload" << _payload
		));
	}
}

void zapata::ZMQ::send(zapata::JSONPtr _envelope) {
	assertz((_envelope["performative"]->ok() || _envelope["status"]->ok()) && (_envelope["resource"]->ok() || _envelope["status"]->ok()) && _envelope["payload"]->ok(), "'performative', 'resource' and 'payload' attributes are required", 412, 0);
	assertz(!_envelope["headers"]->ok() || _envelope["headers"]->type() == zapata::JSObject, "'headers' must be of type JSON object", 412, 0);

	if (_envelope["performative"]->ok()) {
		_envelope << "headers" << (zapata::ev::init_request() + _envelope["headers"]);

		std::string _method_url(zapata::ev::to_str((zapata::ev::Performative) ((int) _envelope["performative"])));
		_method_url += string(" ") + _envelope["resource"]->str();
		zmq::message_t _request_method(_method_url.size());
		memcpy ((void *) _request_method.data(), _method_url.data(), _method_url.size());
		this->out().send(_request_method, ZMQ_SNDMORE);
	}
	else {
		std::string _method_url((string) _envelope["status"]);
		zmq::message_t _request_method(_method_url.size());
		memcpy ((void *) _request_method.data(), _method_url.data(), _method_url.size());
		this->out().send(_request_method, ZMQ_SNDMORE);
	}

	if (_envelope["headers"]->ok()) {
		for (auto _header : _envelope["headers"]->obj()) {
			std::string _header_str(_header.first + string(": ") + ((string) _header.second));
			zmq::message_t _header_zmq(_header_str.size());
			memcpy ((void *) _header_zmq.data(), _header_str.data(), _header_str.size());
			this->out().send(_header_zmq, ZMQ_SNDMORE);
		}
	}

	string _payload_str = (string) _envelope["payload"];
	zmq::message_t _request(_payload_str.size());
	memcpy ((void *) _request.data(), _payload_str.data(), _payload_str.size());
	this->out().send(_request);
}

zapata::ZMQReq::ZMQReq(std::string _connection) : zapata::ZMQ( _connection ) {
	this->connection() = _connection;
	this->__socket = new zmq::socket_t(this->context(), ZMQ_REQ);
	this->__socket->connect(this->connection().data());
}

zapata::ZMQReq::~ZMQReq() {
	this->__socket->close();
	delete this->__socket;
}

zmq::socket_t& zapata::ZMQReq::socket() {
	return * this->__socket;
}

zmq::socket_t& zapata::ZMQReq::in() {
	return * this->__socket;
}

zmq::socket_t& zapata::ZMQReq::out() {
	return * this->__socket;
}

short int zapata::ZMQReq::type() {
	return ZMQ_REQ;
}

void zapata::ZMQReq::listen(zapata::ZMQPollPtr _poll) {
	_poll->poll(this->self());
}

zapata::ZMQRep::ZMQRep(std::string _connection) : zapata::ZMQ( _connection ) {
	this->connection() = _connection;
	this->__socket = new zmq::socket_t(this->context(), ZMQ_REP);
	this->__socket->bind(this->connection().data());
}

zapata::ZMQRep::~ZMQRep() {
	this->__socket->close();
	delete this->__socket;
}

zmq::socket_t& zapata::ZMQRep::socket() {
	return * this->__socket;
}

zmq::socket_t& zapata::ZMQRep::in() {
	return * this->__socket;
}

zmq::socket_t& zapata::ZMQRep::out() {
	return * this->__socket;
}

short int zapata::ZMQRep::type() {
	return ZMQ_REP;
}

void zapata::ZMQRep::listen(zapata::ZMQPollPtr _poll) {
}

zapata::ZMQXPubXSub::ZMQXPubXSub(std::string _connection) : zapata::ZMQ( _connection ) {
	this->connection() = _connection;
	this->__socket_sub = new zmq::socket_t(this->context(), ZMQ_XSUB);
	this->__socket_sub->bind(this->connection().data());
	this->__socket_pub = new zmq::socket_t(this->context(), ZMQ_XPUB);
	this->__socket_pub->bind(this->connection().data());
}

zapata::ZMQXPubXSub::~ZMQXPubXSub() {
	this->__socket_sub->close();
	delete this->__socket_sub;
	this->__socket_pub->close();
	delete this->__socket_pub;
}

zmq::socket_t& zapata::ZMQXPubXSub::socket() {
	return * this->__socket_sub;
}

zmq::socket_t& zapata::ZMQXPubXSub::in() {
	return * this->__socket_sub;
}

zmq::socket_t& zapata::ZMQXPubXSub::out() {
	return * this->__socket_pub;
}

void zapata::ZMQXPubXSub::loop() {
	try {
		zmq::proxy(* this->__socket_pub, * this->__socket_sub, nullptr);
	}
	catch(zmq::error_t& _e) {
		zlog(_e.what(), zapata::emergency);
	}
}

short int zapata::ZMQXPubXSub::type() {
	return ZMQ_XPUB;
}

void zapata::ZMQXPubXSub::listen(zapata::ZMQPollPtr _poll) {
}

zapata::ZMQPubSub::ZMQPubSub(std::string _connection) : zapata::ZMQ( _connection ) {
	this->connection() = _connection;
	this->__socket_sub = new zmq::socket_t(this->context(), ZMQ_SUB);
	this->__socket_sub->bind(this->connection().data());
	this->__socket_pub = new zmq::socket_t(this->context(), ZMQ_PUB);
	this->__socket_pub->bind(this->connection().data());
}

zapata::ZMQPubSub::~ZMQPubSub() {
	this->__socket_sub->close();
	delete this->__socket_sub;
	this->__socket_pub->close();
	delete this->__socket_pub;
}

zmq::socket_t& zapata::ZMQPubSub::socket() {
	return * this->__socket_sub;
}

zmq::socket_t& zapata::ZMQPubSub::in() {
	return * this->__socket_sub;
}

zmq::socket_t& zapata::ZMQPubSub::out() {
	return * this->__socket_pub;
}

short int zapata::ZMQPubSub::type() {
	return ZMQ_PUB;
}

void zapata::ZMQPubSub::listen(zapata::ZMQPollPtr _poll) {
	_poll->poll(this->self());
}

