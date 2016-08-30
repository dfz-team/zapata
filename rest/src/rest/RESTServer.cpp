/*
                                         ._wwwmQQWQQQmywa,.                                         
                                       syQQ8TY1vlllll1YT$QQ/                                        
                                      jQQEvvvvvvvvvvvvngmQQ[                                        
                                       $QEvnvnvnnnvnnnUQQQQQ,                                       
                             ._ssaaaaaamQmwgwqoonnnonnnnnnQQ6                                       
                    ._aaaZ$WmQmmwmwmmmdgm#WhmUQ@VWQggpno2odQQL                                      
               .sayWQQW#WBWmBmmmmBBmmmWBBWmWWmQmWS$ETWQmpoS$QQ,                                     
            _awW#mmmmmmmmmmmmBmWmmmBmmmmmmmmmmmBWWWmZ4WWQmS2QWm                                     
          .jm##mmmmmmmmmmmmmmmm##mmmmmmmmmmmmmmm##WWQWwmQQZXdQQL                                    
      _aw#m#######################################ZWQQwVQQmXZ#QQ/                                   
    .wW#Z#Z##Z#Z#Z#Z#UU#Z##Z#UZ#Z#Z#Z#Z#Z#Z#Z#Z#ZUZ#QQ@VQQQmZZQQm                                   
   _QWZZ#ZZZZZZ#ZZZ#ZZZZZZZZZZUZZZUZZZZZZZZZZZZZZZUZQWQ@oQQQm##WQc                                  
  <QWZZZZXZZZZZZXZZZXZZZZZZZZZZXZZZXZZZZZZZZZZZZZZZXZQWQQoQQQQm#QQ,                                 
 _QQXXXXXXZXXZXXXZXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX$QQQmdQQQQWQ6                                 
 mQ#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXSdWWQmm#WQQQQc                           awaa,
)QQXSSSSSSS2X2SSS2SS2SS2SS2SS2SS2SS2SS2S2S2S2S2S2S2S22S22dWQQQg#$WQQQwaa.                  ._amQWWQQ
jQBo2222222222So2222222222222222222222222222222222222222SooXUQQQQyBQWQWWQQQwaaaaaaaaaaawmQWHBmQQQQQE
mQ#o222o2o2222o222o222o222o22o22o2o2o2o2o2o2o2o2o2o2o2oooo2onoXUWQQWmWQQQQQQBHUBUUUUUUXSS2SSqQQQQQW'
QQEooooooooooooooooooooooooooooooooooooooooooooooooooooooooooonnnXVWQQQQQQQQQQmmqXXXXSXXmmmQWQQQQQ^ 
WQmnnnonononnnnnnnnnnnnnnnnnnnnnogmpnnnnnnnnnnnnnnnnnnnnnnnnnnnnnvnvXVQWQQQQQQQWQQQQQQQQWWWWQQQQ@'  
3QQvnnvnnvnnvnnvnnvnnvnnvnnvnnvndQQQpvnvnnvnnvnnvnvnvnvvnvnvvnvvvnvvvvvXYVVHUHHBHHVHHVVVHWQQQQQY    
)WQpvvvvvvvvvvvvvvvvvvvvvvvvvvvvmQQQWguvvvvvvnnuwyggggmQQWQQmmgwvvvvvvvIvvvIIvIvIIvIIvqmQQQQQY`     
 4QQplvvvvvvvvvvvvvvvvvvvvvvvvomQQQQQQQQQQQQQQQQQQQQQQQQWWWWQWQQQmgggyyyyyyyyyyyymmQQQQQQQD!        
  $QWpiIIlIlIlIlIlIowwywymmQWQQQQQQ$QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQWQQQQQWQWQQWQQWQQQ@T??`          
   4QQgzlllIllllqmQQQQQWQQQQQQQQQQQ-QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ/^"""""""^~-                   
    "$QQmuIllIlqWWQQQQQQQQQQQQQQQQE )WQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQWm,                             
      "9QQQmyuumQQQQQQQQQQQQQQQQQQ'  "$QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQm                             
         "?HWQQQQQQQQQQQQQQQQQQWD'     ??WWWWWWWWWWWBBUHHVTTTV$QWQQQQQQL                            
              -QQWP???????!!""~                                 -9WQQQQQ,                           
               QW[                                                -$QQQQL                           
               $W.                                                 -QWQQQ/                          
                                                                    -^^^"~                          

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

#include <dlfcn.h>
#include <zapata/exceptions/ClosedException.h>
#include <zapata/exceptions/InterruptedException.h>
#include <zapata/json.h>
#include <zapata/log/log.h>
#include <sys/sem.h>
#include <zapata/text/convert.h>
#include <zapata/file/manip.h>
#include <zapata/rest/RESTServer.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <zapata/rest/codes_rest.h>

zpt::RESTServerPtr::RESTServerPtr(std::string _name, zpt::json _options) : std::shared_ptr<zpt::RESTServer>(new zpt::RESTServer(_name, _options)) {
}

zpt::RESTServerPtr::RESTServerPtr(zpt::RESTServer * _ptr) : std::shared_ptr<zpt::RESTServer>(_ptr) {
}

zpt::RESTServerPtr::~RESTServerPtr() {
}

zpt::RESTServer::RESTServer(std::string _name, zpt::json _options) : __name(_name), __emitter( new zpt::RESTEmitter(_options)), __poll(new zpt::ZMQPoll(_options, __emitter)), __options(_options) {
	assertz(this->__options["zmq"]->ok() && this->__options["zmq"]->type() == zpt::JSArray && this->__options["zmq"]->arr()->size() != 0, "zmq settings (bind, type) must be provided in the configuration file", 500, 0);
	((zpt::RESTEmitter*) this->__emitter.get())->poll(this->__poll);

	if (zpt::log_lvl == -1 && !!this->__options["log"]["level"]) {
		zpt::log_lvl = (int) this->__options["log"]["level"];
	}
	if (zpt::log_lvl == -1) {
		zpt::log_lvl = 4;
	}
	if (!!this->__options["log"]["file"]) {
		zpt::log_fd = new ofstream();
		((std::ofstream *) zpt::log_fd)->open(((string) this->__options["log"]["file"]).data());
	}

	for (auto _definition : this->__options["zmq"]->arr()) {
		short int _type = zpt::str2type(_definition["type"]->str());

		switch(_type) {
			case ZMQ_ROUTER_DEALER : {
				this->__router_dealer.push_back(this->__poll->bind(ZMQ_ROUTER_DEALER, _definition["bind"]->str()));
				break;
			}
			case ZMQ_PUB_SUB : {
				this->__pub_sub.push_back(this->__poll->bind(ZMQ_XPUB_XSUB, _definition["bind"]->str()));
				std::string _connect(_definition["bind"]->str());
				zpt::replace(_connect, "*", ((string) this->__options["host"]));
				this->__poll->bind(ZMQ_PUB_SUB, _connect)->in().setsockopt(ZMQ_SUBSCRIBE, "/", 1);
				break;
			}
			default : {
				this->__poll->bind(_type, _definition["bind"]->str());
			}
		}
	}

	if (this->__options["rest"]["modules"]->ok()) {
		for (auto _i : this->__options["rest"]["modules"]->arr()) {
			string _lib_file("lib");
			_lib_file.append((string) _i);
			_lib_file.append(".so");

			if (_lib_file.length() > 6) {
				void *hndl = dlopen(_lib_file.data(), RTLD_NOW);
				if (hndl == nullptr) {
					zlog(string(dlerror()), zpt::error);
				}
				else {
					void (*_populate)(zpt::ev::emitter);
					_populate = (void (*)(zpt::ev::emitter)) dlsym(hndl, "restify");
					_populate(this->__emitter);
				}
			}
		}
	}

	if (!!this->__options["rest"]["uploads"]["upload_controller"]) {
		/*
		 *  definition of handlers for the file upload controller
		 *  registered as a Controller
		 */
		this->__emitter->on(zpt::ev::Post, string("^/api/") + this->__options["rest"]["version"]->str() + string("/files$"), [] (zpt::ev::performative _performative, std::string _resource, zpt::json _payload, zpt::ev::emitter _pool) -> zpt::json {
			return zpt::undefined;
		});

		/*
		 *  definition of handlers for the file upload removal controller
		 *  registered as a Controller
		 */
		this->__emitter->on(zpt::ev::Delete, string("^/api/") + this->__options["rest"]["version"]->str() + string("/files/(.+)$"), [] (zpt::ev::performative _performative, std::string _resource, zpt::json _payload, zpt::ev::emitter _pool) -> zpt::json {
			return zpt::undefined;
		});
	}

}

zpt::RESTServer::~RESTServer(){
	zpt::ZMQPoll* _poll = this->__poll.get();
	this->__poll.reset();
	_poll->unbind();
}

std::string zpt::RESTServer::name() {
	return this->__name;
}

zpt::poll zpt::RESTServer::poll() {
	return this->__poll;
}

zpt::ev::emitter zpt::RESTServer::emitter() {
	return this->__emitter;
}

zpt::json zpt::RESTServer::options() {
	return this->__options;
}

void zpt::RESTServer::start() {
	try {
		if (this->__options["http"]->ok() && this->__options["http"]["bind"]->ok() && this->__options["http"]["port"]->ok()) {
			std::shared_ptr< std::thread > _http(
				new std::thread(
					[ & ] () -> void {
						zlog(string("starting HTTP listener on port ") + std::to_string((uint) this->__options["http"]["port"]), zpt::notice);

						zpt::serversocketstream_ptr _ss(new zpt::serversocketstream());
						_ss->bind((uint) this->__options["http"]["port"]);

						for (; true; ) {
							int _fd = -1;
							_ss->accept(& _fd);
				
							zpt::socketstream_ptr _cs(new zpt::socketstream(_fd));
							try {
								if (this->route_http(_cs)) {
									_cs->close();
								}
							}
							catch(zpt::AssertionException& _e) {
								zpt::http::rep _reply = zpt::rest::zmq2http(
									zpt::json(
										{
											"performative", zpt::ev::Reply,
											"status", 500,
											"headers", zpt::ev::init_reply(),
											"payload", {
												"text", _e.what(),
												"assertion_failed", _e.description(),
												"code", _e.code()
												}
										}
									)
								);
								(*_cs) << _reply << flush;
								_cs->close();								
							}
						}
					}
				)
			);
			this->__threads.push_back(_http);
		}

		if (this->__options["mqtt"]->ok() && this->__options["mqtt"]["bind"]->ok() && this->__options["mqtt"]["port"]->ok()) {
			std::shared_ptr< std::thread > _mqtt(
				new std::thread(
					[ & ] () -> void {
						zlog(string("starting MQTT listener on port ") + std::to_string((uint) this->__options["mqtt"]["port"]), zpt::notice);
					}
				)
			);
			this->__threads.push_back(_mqtt);
		}

		for (size_t _idx = 0; _idx != this->__pub_sub.size(); _idx++) {
			std::shared_ptr< std::thread > _proxy(
				new std::thread(
					[ & ] (size_t _idx) -> void {
						((zpt::ZMQXPubXSub *) this->__pub_sub[_idx].get())->loop();
					}, _idx
				)
			);
			this->__threads.push_back(_proxy);
		}
		for (size_t _idx = 0; _idx != this->__router_dealer.size(); _idx++) {
			std::shared_ptr< std::thread > _proxy(
				new std::thread(
					[ & ] (size_t _idx) -> void {
						((zpt::ZMQRouterDealer *) this->__router_dealer[_idx].get())->loop();
					}, _idx
				)
			);
			this->__threads.push_back(_proxy);
		}
		this->__poll->loop();
		for (auto _thread : this->__threads) {
			_thread->join();
		}
	}
	catch (zpt::InterruptedException& e) {
		return;
	}
}

bool zpt::RESTServer::route_http(zpt::socketstream_ptr _cs) {
	zpt::http::rep _reply;
	_reply->status((zpt::HTTPStatus) 200);
	zpt::http::req _request;
	try {
		(*_cs) >> _request;
	}
	catch(zpt::SyntaxErrorException& _e) {
		assertz(false, "error parsing HTTP data", 500, 0);
	}

	bool _return = false;
	bool _api_found = false;
	std::string _prefix(_request->url());
	if (this->__options["directory"]->ok()) {
		for (auto _api : this->__options["directory"]->obj()) {
			bool _endpoint_found = false;
			for (auto _endpoint : _api.second["endpoints"]->arr()) {
				if (_prefix.find(_endpoint->str()) == 0) {
					_endpoint_found = true;
					_api_found = true;
					short _type = zpt::str2type(_api.second["type"]->str());
					zpt::json _in = zpt::rest::http2zmq(_request);
					switch(_type) {
						case ZMQ_REP :
						case ZMQ_REQ :
						case ZMQ_ROUTER_DEALER : {
							zpt::ZMQAssyncReq* _client = new zpt::ZMQAssyncReq(_api.second["connect"]->str(), this->__options, this->__emitter);
							_client->listen(this->__poll);
							_client->relay_for(_cs);
							_client->send(_in);
							_return = false;
							break;
						}
						case ZMQ_PUB_SUB : {
							std::string _connect = _api.second["connect"]->str();
							zpt::socket _client = this->__poll->bind(ZMQ_PUB, _connect.substr(0, _connect.find(",")));
							_client->send(_in);
							zpt::http::rep _reply = zpt::rest::zmq2http(zpt::rest::accepted(_prefix));
							(*_cs) << _reply << flush;
							_return = true;
							_client->unbind();
							break;
						}
						case ZMQ_PUSH : {
							zpt::socket _client = this->__poll->bind(ZMQ_PUSH, _api.second["connect"]->str());
							_client->send(_in);
							zpt::http::rep _reply = zpt::rest::zmq2http(zpt::rest::accepted(_prefix));
							(*_cs) << _reply << flush;
							_return = true;
							_client->unbind();
							break;
						}
					}
					break;
				}
			}
			if (_endpoint_found) {
				break;
			}
		}
	}
				
	if (!_api_found) {
		zpt::http::rep _reply = zpt::rest::zmq2http(zpt::rest::not_found(_prefix));
		(*_cs) << _reply << flush;
		_return = true;
	}
	return _return;
}

bool zpt::RESTServer::route_mqtt(std::iostream& _cs) {
	return true;
}

zpt::RESTClientPtr::RESTClientPtr(zpt::json _options) : std::shared_ptr<zpt::RESTClient>(new zpt::RESTClient(_options)) {
}

zpt::RESTClientPtr::RESTClientPtr(zpt::RESTClient * _ptr) : std::shared_ptr<zpt::RESTClient>(_ptr) {
}

zpt::RESTClientPtr::~RESTClientPtr() {
}

zpt::RESTClient::RESTClient(zpt::json _options) : __emitter( new zpt::RESTEmitter(_options)), __poll(new zpt::ZMQPoll(_options, __emitter)), __options(_options) {
	((zpt::RESTEmitter*) this->__emitter.get())->poll(this->__poll);
}

zpt::RESTClient::~RESTClient(){
}

zpt::poll zpt::RESTClient::poll() {
	return this->__poll;
}

zpt::ev::emitter zpt::RESTClient::emitter() {
	return this->__emitter;
}

zpt::json zpt::RESTClient::options() {
	return this->__options;
}

zpt::socket zpt::RESTClient::bind(std::string _object_path) {
	zpt::json _zmq_cnf = this->__options->getPath(_object_path);
	short _type = zpt::str2type(_zmq_cnf["type"]->str());
	return this->bind(_type, _zmq_cnf["bind"]->str());
}

zpt::socket zpt::RESTClient::bind(short _type, std::string _connection) {
	return this->__poll->bind(_type, _connection);
}

void zpt::RESTClient::start() {
	try {
		this->__poll->loop();
	}
	catch (zpt::InterruptedException& e) {
		return;
	}
}

void zpt::conf::init(std::string _name, zpt::json _options) {
	zpt::conf::dirs(_options);
	zpt::conf::env(_options);
	if (_options["log"]->ok()) {
		if (_options["log"]["file"]->ok()) {
			zpt::log_fd = new ofstream();
			string _log_file((string) _options["log"]["file"]);
			((std::ofstream *) zpt::log_fd)->open(_log_file.data(), (std::ios_base::out | std::ios_base::app) & ~std::ios_base::ate);
		}
		if (zpt::log_lvl == -1 && _options["log"]["level"]->ok()) {
			zpt::log_lvl = (int) _options["log"]["level"];
		}
	}
	if (zpt::log_lvl == -1) {
		zpt::log_lvl = 4;
	}
	zlog(std::string("starting RESTful server instance: ") + _name, zpt::alert);
}

void zpt::conf::dirs(std::string _dir, zpt::json _options) {
	std::vector<std::string> _files;
	if (zpt::is_dir(_dir)) {
		zpt::glob(_dir, _files, "(.*)\\.conf");
	}
	else {
		_files.push_back(_dir);
	}
	for (auto _file : _files) {
		zpt::json _conf;
		std::ifstream _ifs;
		_ifs.open(_file.data());
		try {
			_ifs >> _conf;
		}
		catch(zpt::SyntaxErrorException& _e) {
			_conf = zpt::undefined;
		}
		_ifs.close();

		assertz(_conf->ok(), std::string("syntax error parsing file: ") + _file, 500, 0);

		for (auto _new_field : _conf->obj()) {
			if (!_options[_new_field.first]->ok()) {
				_options << _new_field.first << _new_field.second;
			}
			else {
				zpt::json _merged = _options[_new_field.first] + _new_field.second;
				_options << _new_field.first << _merged;
			}
		}
	}
}

void zpt::conf::dirs(zpt::json _options) {
	// zpt::conf::dirs("/etc/zapata/conf.d", _options);
	zpt::json _traversable = _options->clone();
	_traversable->inspect(zpt::json({ "$regexp", "(.*)" }),
		[ & ] (std::string _object_path, std::string _key, zpt::JSONElementT& _parent) -> void {
			if (_key == "$include") {
				zpt::json _object = (_object_path.rfind(".") != string::npos ? _options->getPath(_object_path.substr(0, _object_path.rfind("."))) : _options);
				zpt::json _to_include = _options->getPath(_object_path);
				if (_to_include->type() == zpt::JSArray) {
					for (auto _file : _to_include->arr()) {
						zpt::conf::dirs((std::string) _file, _object);
					}
				}
				else {
					zpt::conf::dirs((std::string) _to_include, _object);
				}
				_object >> "$include";
			}
		}
	);
}

void zpt::conf::env(zpt::json _options) {
	zpt::json _traversable = _options->clone();
	_traversable->inspect(zpt::json({ "$regexp", "\\$\\{([^}]+)\\}" }), [ & ] (std::string _object_path, std::string _key, zpt::JSONElementT& _parent) -> void {
		std::string _var = _options->getPath(_object_path);
		_var = _var.substr(2, _var.length() - 3);
		const char * _valuec = std::getenv(_var.data());
		if (_valuec != nullptr) {
			std::string _value(_valuec);
			_options->setPath(_object_path, zpt::mkptr(_value));
		}
	});
}

zpt::json zpt::rest::http2zmq(zpt::http::req _request) {
	zpt::json _return = zpt::mkobj();
	_return <<
		"channel" << _request->url() <<
		"performative" << _request->method() <<
		"resource" << _request->url();
	
	zpt::json _payload;
	if (_request->body() != "") {
		if (_request->header("Content-Type") == "application/x-www-form-urlencoded") {
			_payload = zpt::rest::http::deserialize(_request->body());
		}
		else if (_request->header("Content-Type") == "application/json") {
			try {
				_payload = zpt::json(_request->body());
			}
			catch(zpt::SyntaxErrorException& _e) {
			}
		}
		else {
			_payload = zpt::json({ "text", _request->body() });
		}
	}
	else {
		_payload = zpt::mkobj();
	}
	for (auto _param : _request->params()) {
		_payload << _param.first << _param.second;
	}
	_return << "payload" << _payload;

	zpt::json _headers = zpt::mkobj();
	for (auto _header : _request->headers()) {
		_headers << _header.first << _header.second;
	}
	if (_headers->obj()->size() != 0) {
		_return << "headers" << _headers;
	}
	
	return _return;
}

zpt::http::rep zpt::rest::zmq2http(zpt::json _out) {
	zpt::http::rep _return;
	_return->status((zpt::HTTPStatus) ((int) _out["status"]));
	
	_out["headers"] = zpt::ev::init_reply() + _out["headers"];
	for (auto _header : _out["headers"]->obj()) {
		_return->header(_header.first, ((string) _header.second));
	}
	
	if (_out["payload"]->ok() && _out["payload"]->obj()->size() != 0) {
		std::string _body = (string) _out["payload"];
		_return->body(_body);
		_return->header("Content-Type", "application/json");
		_return->header("Content-Length", std::to_string(_body.length()));
	}

	return _return;
}

zpt::json zpt::rest::http::deserialize(std::string _body) {
	zpt::json _return = zpt::mkobj();
	std::string _name;
	std::string _collected;
	for (const auto& _c : _body) {
		switch(_c) {
			case '=' : {
				_name.assign(_collected.data());
				_collected.assign("");
				break;
			}
			case '&' : {
				zpt::url::decode(_collected);
				_return << _name << _collected;
				_name.assign("");
				_collected.assign("");
				break;
			}
			default : {
				_collected.push_back(_c);
			}
		}
	}
	zpt::url::decode(_collected);
	_return << _name << _collected;
	return _return;
}

zpt::json zpt::rest::authorization::deserialize(std::string _token) {
	return zpt::rest::cookies::deserialize(_token);
}

std::string zpt::rest::authorization::extract(zpt::json _envelope) {
	if (_envelope[ZPT_HEADERS]["Authorization"]->ok()) {
		return std::string(zpt::split(_envelope[ZPT_HEADERS]["Authorization"], " ")[1]);
	}
	if (_envelope[ZPT_HEADERS]["Cookie"]->ok()) {
		return std::string(zpt::split(_envelope[ZPT_HEADERS]["Cookie"], ";")[0]);
	}
	if (_envelope[ZPT_PAYLOAD]["access_token"]->ok()) {
		return std::string(_envelope[ZPT_PAYLOAD]["access_token"]);
	}
	return zpt::undefined;
}

zpt::ZMQAssyncReq::ZMQAssyncReq(std::string _connection, zpt::json _options, zpt::ev::emitter _emitter) : zpt::ZMQ(_connection, _options, _emitter) {
	this->__socket = new zmq::socket_t(this->context(), ZMQ_REQ);
	if (_connection.find("://*") != string::npos) {
		this->__socket->bind(_connection.data());
		zlog(string("binding assync REQ socket on ") + _connection, zpt::notice);
	}
	else {
		this->__socket->connect(_connection.data());
		zlog(string("connecting assync REQ socket on ") + _connection, zpt::notice);
	}
}

zpt::ZMQAssyncReq::~ZMQAssyncReq() {
	this->__socket->close();
	delete this->__socket;
	this->__relayed_socket->close();
	zlog(string("releasing assync REQ from ") + this->connection(), zpt::notice);
}

zmq::socket_t& zpt::ZMQAssyncReq::socket() {
	return * this->__socket;
}

zmq::socket_t& zpt::ZMQAssyncReq::in() {
	return * this->__socket;
}

zmq::socket_t& zpt::ZMQAssyncReq::out() {
	return * this->__socket;
}

short int zpt::ZMQAssyncReq::type() {
	return ZMQ_ASSYNC_REQ;
}

bool zpt::ZMQAssyncReq::once() {
	return true;
}

zpt::json zpt::ZMQAssyncReq::send(zpt::json _envelope) {
	zpt::ZMQ::send(_envelope);
	return zpt::undefined;
}

zpt::json zpt::ZMQAssyncReq::recv() {
	zpt::json _envelope = zpt::ZMQ::recv();
	if (!_envelope["status"]->ok() || ((int) _envelope["status"]) < 100) {
		_envelope << "status" << 501;
	}
	zpt::http::rep _reply = zpt::rest::zmq2http(_envelope);
	(* this->__relayed_socket) << _reply << flush;
	return zpt::undefined;
}

void zpt::ZMQAssyncReq::relay_for(zpt::socketstream_ptr _socket) {
	this->__relayed_socket = _socket;
}

void zpt::ZMQAssyncReq::listen(zpt::poll _poll) {
	_poll->poll(this->self());
}

