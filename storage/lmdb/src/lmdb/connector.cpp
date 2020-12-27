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

#include <zapata/lmdb/connector.h>
#include <algorithm>

auto
zpt::storage::lmdb::to_db_key(zpt::json _document) -> std::string {
    return _document["_id"]->string();
}

auto
zpt::storage::lmdb::to_db_doc(zpt::json _document) -> std::string {
    return static_cast<std::string>(_document);
}

auto
zpt::storage::lmdb::from_db_doc(std::string const& _document) -> zpt::json {
    return zpt::json::parse_json_str(_document);
}

zpt::storage::lmdb::connection::connection(zpt::json _options)
  : __options(_options["storage"]["lmdb"]) {}

auto
zpt::storage::lmdb::connection::open(zpt::json _options) -> zpt::storage::connection::type* {
    this->__options = _options;
    return this;
}

auto
zpt::storage::lmdb::connection::close() -> zpt::storage::connection::type* {
    return this;
}

auto
zpt::storage::lmdb::connection::session() -> zpt::storage::session {
    return zpt::storage::session::alloc<zpt::storage::lmdb::session>(*this);
}

auto
zpt::storage::lmdb::connection::options() -> zpt::json& {
    return this->__options;
}

zpt::storage::lmdb::session::session(zpt::storage::lmdb::connection& _connection)
  : __options{ _connection.options() } {}

auto
zpt::storage::lmdb::session::is_open() -> bool {
    return true;
}

auto
zpt::storage::lmdb::session::commit() -> zpt::storage::session::type* {
    this->__commit = true;
    return this;
}

auto
zpt::storage::lmdb::session::rollback() -> zpt::storage::session::type* {
    this->__commit = false;
    return this;
}

auto
zpt::storage::lmdb::session::is_to_commit() -> bool& {
    return this->__commit;
}

auto
zpt::storage::lmdb::session::database(std::string const& _db) -> zpt::storage::database {
    return zpt::storage::database::alloc<zpt::storage::lmdb::database>(*this, _db);
}

zpt::storage::lmdb::database::database(zpt::storage::lmdb::session& _session,
                                       std::string const& _db)
  : __path{ _session.__options["path"]->string() + std::string{ "/" } + _db }
  , __commit{ _session.is_to_commit() } {}

auto
zpt::storage::lmdb::database::is_to_commit() -> bool& {
    return *this->__commit;
}

auto
zpt::storage::lmdb::database::path() -> std::string& {
    return this->__path;
}

auto
zpt::storage::lmdb::database::collection(std::string const& _collection)
  -> zpt::storage::collection {
    return zpt::storage::collection::alloc<zpt::storage::lmdb::collection>(*this, _collection);
}

zpt::storage::lmdb::collection::collection(zpt::storage::lmdb::database& _database,
                                           std::string const& _collection)
  : __underlying{ ::lmdb::env::create() }
  , __collection_name{ _collection }
  , __collection_file{ _database.path() + std::string{ "/" } + _collection + std::string{ ".mdb" } }
  , __commit{ _database.is_to_commit() } {
    this->__underlying.set_mapsize(1UL * 1024UL * 1024UL * 1024UL); /* 1 GiB */
    this->__underlying.open(this->__collection_file.data(), MDB_NOSUBDIR, 0664);
}

auto
zpt::storage::lmdb::collection::add(zpt::json _document) -> zpt::storage::action {
    return zpt::storage::action::alloc<zpt::storage::lmdb::action_add>(*this, _document);
}

auto
zpt::storage::lmdb::collection::modify(zpt::json _search) -> zpt::storage::action {
    return zpt::storage::action::alloc<zpt::storage::lmdb::action_modify>(*this, _search);
}

auto
zpt::storage::lmdb::collection::remove(zpt::json _search) -> zpt::storage::action {
    return zpt::storage::action::alloc<zpt::storage::lmdb::action_remove>(*this, _search);
}

auto
zpt::storage::lmdb::collection::replace(std::string const& _id, zpt::json _document)
  -> zpt::storage::action {
    return zpt::storage::action::alloc<zpt::storage::lmdb::action_replace>(*this, _id, _document);
}

auto
zpt::storage::lmdb::collection::find(zpt::json _search) -> zpt::storage::action {
    return zpt::storage::action::alloc<zpt::storage::lmdb::action_find>(*this, _search);
}

auto
zpt::storage::lmdb::collection::count() -> size_t {
    try {
        auto _read_trx = ::lmdb::txn::begin(this->__underlying.handle(), nullptr, MDB_RDONLY);
        auto _dbi = ::lmdb::dbi::open(_read_trx, nullptr);
        auto _count = _dbi.size(_read_trx);
        _read_trx.abort();
        return _count;
    }
    catch (...) {
    }
    return 0;
}

auto
zpt::storage::lmdb::collection::file() -> std::string& {
    return this->__collection_file;
}

auto
zpt::storage::lmdb::collection::env() -> ::lmdb::env& {
    return this->__underlying;
}

auto
zpt::storage::lmdb::collection::is_to_commit() -> bool& {
    return *this->__commit;
}

zpt::storage::lmdb::action::action(zpt::storage::lmdb::collection& _collection)
  : __underlying{ _collection } {}

auto
zpt::storage::lmdb::action::is_to_commit() -> bool& {
    return this->__underlying->is_to_commit();
}

auto
zpt::storage::lmdb::action::set_state(::lmdb::error const& _e) -> void {
    this->__state = { "code",
                      _e.code(),
                      "message",
                      std::string{ _e.origin() } + std::string{ ": " } + std::string{ _e.what() } };
}

auto
zpt::storage::lmdb::action::get_state() -> zpt::json {
    return this->__state;
}

auto
zpt::storage::lmdb::action::is_filtered_out(zpt::json _search, zpt::json _to_filter) -> bool {
    if (_search->size() != 0) {
        for (auto [_, _key, _value] : _search) {
            if (_value != _to_filter[_key]) { return true; }
        }
    }
    return false;
}

auto
zpt::storage::lmdb::action::trim(zpt::json _fields, zpt::json _to_trim) -> zpt::json {
    if (_fields->size() != 0) {
        for (auto [_, __, _field] : _fields) { _to_trim->object()->pop(_field->string()); }
    }
    return _to_trim;
}

zpt::storage::lmdb::action_add::action_add(zpt::storage::lmdb::collection& _collection,
                                           zpt::json _document)
  : zpt::storage::lmdb::action::action{ _collection } {
    this->add(_document);
}

auto
zpt::storage::lmdb::action_add::add(zpt::json _document) -> zpt::storage::action::type* {
    if (!_document["_id"]->ok()) {
        std::string _id{ zpt::generate::r_uuid() };
        this->__generated_uuid << zpt::json{ "_id", _id };
        _document << "_id" << _id;
    }
    this->__to_add << _document;
    return this;
}

auto
zpt::storage::lmdb::action_add::modify(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't modify from an 'add' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_add::remove(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't remove from an 'add' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_add::replace(std::string const& _id, zpt::json _document)
  -> zpt::storage::action::type* {
    expect(false, "can't replace from an 'add' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_add::find(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't find from an 'add' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_add::set(std::string const& _attribute, zpt::json _value)
  -> zpt::storage::action::type* {
    expect(false, "can't set from an 'add' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_add::unset(std::string const& _attribute)
  -> zpt::storage::action::type* {
    expect(false, "can't unset from an 'add' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_add::patch(zpt::json _document) -> zpt::storage::action::type* {
    expect(false, "can't patch from an 'add' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_add::sort(std::string const& _attribute) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_add::fields(zpt::json _fields) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_add::offset(size_t _rows) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_add::limit(size_t _number) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_add::bind(zpt::json _map) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_add::execute() -> zpt::storage::result {
    try {
        auto _transaction = ::lmdb::txn::begin(this->__underlying->env().handle());
        auto _dbi = ::lmdb::dbi::open(_transaction);
        for (auto [_, __, _doc] : this->__to_add) {
            ::lmdb::dbi_put(_transaction,
                            _dbi,
                            ::lmdb::val{ zpt::storage::lmdb::to_db_key(_doc).data() },
                            ::lmdb::val{ zpt::storage::lmdb::to_db_doc(_doc).data() });
        }
        _transaction.commit();
    }
    catch (::lmdb::error const& _e) {
        this->set_state(_e);
        this->__generated_uuid = zpt::json::array();
    }
    zpt::json _result{ "state", this->get_state(), "generated", this->__generated_uuid };
    return zpt::storage::result::alloc<zpt::storage::lmdb::result>(_result);
}

zpt::storage::lmdb::action_modify::action_modify(zpt::storage::lmdb::collection& _collection,
                                                 zpt::json _search)
  : zpt::storage::lmdb::action::action{ _collection }
  , __search{ _search }
  , __set{ zpt::json::object() }
  , __unset{ zpt::json::object() } {}

auto
zpt::storage::lmdb::action_modify::add(zpt::json _document) -> zpt::storage::action::type* {
    expect(false, "can't add from a 'modify' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_modify::modify(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't modify from a 'modify' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_modify::remove(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't remove from a 'modify' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_modify::replace(std::string const& _id, zpt::json _document)
  -> zpt::storage::action::type* {
    expect(false, "can't replace from a 'modify' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_modify::find(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't find from a 'modify' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_modify::set(std::string const& _attribute, zpt::json _value)
  -> zpt::storage::action::type* {
    this->__set << _attribute << _value;
    return this;
}

auto
zpt::storage::lmdb::action_modify::unset(std::string const& _attribute)
  -> zpt::storage::action::type* {
    this->__unset << _attribute << true;
    return this;
}

auto
zpt::storage::lmdb::action_modify::patch(zpt::json _document) -> zpt::storage::action::type* {
    for (auto [_, _key, _member] : _document) { this->__set << _key << _member; }
    return this;
}

auto
zpt::storage::lmdb::action_modify::sort(std::string const& _attribute)
  -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_modify::fields(zpt::json _fields) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_modify::offset(size_t _rows) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_modify::limit(size_t _number) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_modify::bind(zpt::json _map) -> zpt::storage::action::type* {
    auto _transform =
      [&](std::string const& _key, zpt::json _item, std::string const& _path) -> void {
        if (_item->type() != zpt::JSString) { return; }
        for (auto [_, _key, _value] : _map) {
            if (_item == _key) { _item << _value; }
        }
    };
    zpt::json::traverse(this->__set, _transform);
    zpt::json::traverse(this->__search, _transform);
    return this;
}

auto
zpt::storage::lmdb::action_modify::execute() -> zpt::storage::result {
    size_t _count{ 0 };
    try {
        auto _transaction = ::lmdb::txn::begin(this->__underlying->env().handle());
        auto _dbi = ::lmdb::dbi::open(_transaction);
        auto _cursor = ::lmdb::cursor::open(_transaction, _dbi);

        try {
            std::string _document_key = zpt::storage::lmdb::to_db_key(this->__search);
            ::lmdb::val _key{ _document_key };
            ::lmdb::val _value;
            if (::lmdb::dbi_get(_transaction.handle(), _dbi.handle(), _key, _value)) {
                auto _doc =
                  zpt::storage::lmdb::from_db_doc(_value.data()) + this->__set - this->__unset;
                ::lmdb::dbi_put(_transaction,
                                _dbi,
                                ::lmdb::val{ zpt::storage::lmdb::to_db_key(_doc).data() },
                                ::lmdb::val{ zpt::storage::lmdb::to_db_doc(_doc).data() });
                ++_count;
            }
            _transaction.commit();
        }
        catch (zpt::failed_expectation& _) {
            std::string _key;
            std::string _value;
            while (_cursor.get(_key, _value, MDB_NEXT)) {
                auto _object = zpt::storage::lmdb::from_db_doc(_value);
                if (!this->is_filtered_out(this->__search, _object)) {
                    auto _doc = _object + this->__set - this->__unset;
                    ::lmdb::dbi_put(_transaction,
                                    _dbi,
                                    ::lmdb::val{ zpt::storage::lmdb::to_db_key(_doc).data() },
                                    ::lmdb::val{ zpt::storage::lmdb::to_db_doc(_doc).data() });
                    ++_count;
                }
            }
            _cursor.close();
            _transaction.commit();
        }
    }
    catch (::lmdb::error const& _e) {
        this->set_state(_e);
        _count = 0;
    }
    zpt::json _result{ "state", this->get_state(), "modified", _count };
    return zpt::storage::result::alloc<zpt::storage::lmdb::result>(_result);
}

zpt::storage::lmdb::action_remove::action_remove(zpt::storage::lmdb::collection& _collection,
                                                 zpt::json _search)
  : zpt::storage::lmdb::action::action{ _collection }
  , __search{ _search } {}

auto
zpt::storage::lmdb::action_remove::add(zpt::json _document) -> zpt::storage::action::type* {
    expect(false, "can't add from a 'remove' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_remove::modify(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't modify from a 'remove' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_remove::remove(zpt::json _search) -> zpt::storage::action::type* {
    this->__search += _search;
    return this;
}

auto
zpt::storage::lmdb::action_remove::replace(std::string const& _id, zpt::json _document)
  -> zpt::storage::action::type* {
    expect(false, "can't replace from a 'remove' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_remove::find(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't find from a 'remove' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_remove::set(std::string const& _attribute, zpt::json _value)
  -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_remove::unset(std::string const& _attribute)
  -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_remove::patch(zpt::json _document) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_remove::sort(std::string const& _attribute)
  -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_remove::fields(zpt::json _fields) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_remove::offset(size_t _rows) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_remove::limit(size_t _number) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_remove::bind(zpt::json _map) -> zpt::storage::action::type* {
    auto _transform =
      [&](std::string const& _key, zpt::json _item, std::string const& _path) -> void {
        if (_item->type() != zpt::JSString) { return; }
        for (auto [_, _key, _value] : _map) {
            if (_item == _key) { _item << _value; }
        }
    };
    zpt::json::traverse(this->__search, _transform);
    return this;
}

auto
zpt::storage::lmdb::action_remove::execute() -> zpt::storage::result {
    size_t _count{ 0 };
    try {
        auto _transaction = ::lmdb::txn::begin(this->__underlying->env().handle());
        auto _dbi = ::lmdb::dbi::open(_transaction);
        auto _cursor = ::lmdb::cursor::open(_transaction, _dbi);

        try {
            std::string _document_key = zpt::storage::lmdb::to_db_key(this->__search);
            ::lmdb::val _key{ _document_key };
            if (::lmdb::dbi_del(_transaction.handle(), _dbi.handle(), _key)) { ++_count; }
            _transaction.commit();
        }
        catch (zpt::failed_expectation& _) {
            std::string _key;
            std::string _value;
            while (_cursor.get(_key, _value, MDB_NEXT)) {
                auto _doc = zpt::storage::lmdb::from_db_doc(_value);
                if (!this->is_filtered_out(this->__search, _doc)) {
                    if (::lmdb::dbi_del(
                          _transaction.handle(),
                          _dbi.handle(),
                          ::lmdb::val{ zpt::storage::lmdb::to_db_key(_doc).data() })) {
                        ++_count;
                    }
                }
            }
            _cursor.close();
            _transaction.commit();
        }
    }
    catch (::lmdb::error const& _e) {
        this->set_state(_e);
        _count = 0;
    }
    zpt::json _result{ "state", this->get_state(), "removed", _count };
    return zpt::storage::result::alloc<zpt::storage::lmdb::result>(_result);
}

zpt::storage::lmdb::action_replace::action_replace(zpt::storage::lmdb::collection& _collection,
                                                   std::string _id,
                                                   zpt::json _document)
  : zpt::storage::lmdb::action::action{ _collection }
  , __id{ _id }
  , __set{ _document } {}

auto
zpt::storage::lmdb::action_replace::add(zpt::json _document) -> zpt::storage::action::type* {
    expect(false, "can't add from a 'replace' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_replace::modify(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't modify from a 'replace' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_replace::remove(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't remove from a 'replace' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_replace::replace(std::string const& _id, zpt::json _document)
  -> zpt::storage::action::type* {
    expect(false, "can't replace from a 'replace' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_replace::find(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't find from a 'replace' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_replace::set(std::string const& _attribute, zpt::json _value)
  -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_replace::unset(std::string const& _attribute)
  -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_replace::patch(zpt::json _document) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_replace::sort(std::string const& _attribute)
  -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_replace::fields(zpt::json _fields) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_replace::offset(size_t _rows) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_replace::limit(size_t _number) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_replace::bind(zpt::json _map) -> zpt::storage::action::type* {
    auto _transform =
      [&](std::string const& _key, zpt::json _item, std::string const& _path) -> void {
        if (_item->type() != zpt::JSString) { return; }
        for (auto [_, _key, _value] : _map) {
            if (_item == _key) { _item << _value; }
        }
    };
    zpt::json::traverse(this->__set, _transform);
    return this;
}

auto
zpt::storage::lmdb::action_replace::execute() -> zpt::storage::result {
    size_t _count{ 0 };
    try {
        auto _transaction = ::lmdb::txn::begin(this->__underlying->env().handle());
        auto _dbi = ::lmdb::dbi::open(_transaction);

        ::lmdb::dbi_put(_transaction,
                        _dbi,
                        ::lmdb::val{ this->__id.data() },
                        ::lmdb::val{ zpt::storage::lmdb::to_db_doc(this->__set).data() });
        _transaction.commit();
        ++_count;
    }
    catch (::lmdb::error const& _e) {
        this->set_state(_e);
        _count = 0;
    }
    zpt::json _result{ "state", this->get_state(), "replaced", _count };
    return zpt::storage::result::alloc<zpt::storage::lmdb::result>(_result);
}

auto
zpt::storage::lmdb::action_replace::replace_one() -> void {
    this->execute();
}

zpt::storage::lmdb::action_find::action_find(zpt::storage::lmdb::collection& _collection)
  : zpt::storage::lmdb::action::action{ _collection }
  , __search{ zpt::json::object() }
  , __sort{ zpt::json::array() }
  , __fields{ zpt::json::array() } {}

zpt::storage::lmdb::action_find::action_find(zpt::storage::lmdb::collection& _collection,
                                             zpt::json _search)
  : zpt::storage::lmdb::action::action{ _collection }
  , __search{ _search }
  , __sort{ zpt::json::array() }
  , __fields{ zpt::json::array() } {}

auto
zpt::storage::lmdb::action_find::add(zpt::json _document) -> zpt::storage::action::type* {
    expect(false, "can't add from a 'find' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_find::modify(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't modify from a 'find' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_find::remove(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't remove from a 'find' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_find::replace(std::string const& _id, zpt::json _document)
  -> zpt::storage::action::type* {
    expect(false, "can't replace from a 'find' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_find::find(zpt::json _search) -> zpt::storage::action::type* {
    expect(false, "can't find from a 'find' action", 500, 0);
    return this;
}

auto
zpt::storage::lmdb::action_find::set(std::string const& _attribute, zpt::json _value)
  -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_find::unset(std::string const& _attribute)
  -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_find::patch(zpt::json _document) -> zpt::storage::action::type* {
    return this;
}

auto
zpt::storage::lmdb::action_find::sort(std::string const& _attribute)
  -> zpt::storage::action::type* {
    this->__sort << _attribute;
    return this;
}

auto
zpt::storage::lmdb::action_find::fields(zpt::json _fields) -> zpt::storage::action::type* {
    this->__fields += _fields;
    return this;
}

auto
zpt::storage::lmdb::action_find::offset(size_t _rows) -> zpt::storage::action::type* {
    this->__offset = _rows;
    return this;
}

auto
zpt::storage::lmdb::action_find::limit(size_t _number) -> zpt::storage::action::type* {
    this->__limit = _number;
    return this;
}

auto
zpt::storage::lmdb::action_find::bind(zpt::json _map) -> zpt::storage::action::type* {
    auto _transform =
      [&](std::string const& _key, zpt::json _item, std::string const& _path) -> void {
        if (_item->type() != zpt::JSString) { return; }
        for (auto [_, _key, _value] : _map) {
            if (_item == _key) { _item << _value; }
        }
    };
    zpt::json::traverse(this->__search, _transform);
    return this;
}

auto
zpt::storage::lmdb::action_find::execute() -> zpt::storage::result {
    auto _found = zpt::json::array();
    try {
        auto _transaction =
          ::lmdb::txn::begin(this->__underlying->env().handle(), nullptr, MDB_RDONLY);
        auto _dbi = ::lmdb::dbi::open(_transaction);
        auto _cursor = ::lmdb::cursor::open(_transaction, _dbi);

        try {
            std::string _document_key = zpt::storage::lmdb::to_db_key(this->__search);
            ::lmdb::val _key{ _document_key };
            ::lmdb::val _value;
            if (::lmdb::dbi_get(_transaction.handle(), _dbi.handle(), _key, _value)) {
                _found << zpt::storage::lmdb::from_db_doc(_value.data());
            }
        }
        catch (zpt::failed_expectation& _) {
            std::string _key;
            std::string _value;
            size_t _offset{ 0 };
            while (_cursor.get(_key, _value, MDB_NEXT)) {
                auto _object = zpt::storage::lmdb::from_db_doc(_value);
                if (!this->is_filtered_out(this->__search, _object)) {
                    ++_offset;
                    if (_offset > this->__offset) { _found << this->trim(this->__fields, _object); }
                }
                if (_found->size() >= this->__limit) { break; }
            }
        }
        _cursor.close();
        _transaction.abort();
    }
    catch (::lmdb::error const& _e) {
        this->set_state(_e);
    }
    zpt::json _result{ "state", this->get_state(), "cursor", _found };
    return zpt::storage::result::alloc<zpt::storage::lmdb::result>(_result);
}

zpt::storage::lmdb::result::result(zpt::json _result)
  : __result{ _result }
  , __current{ __result["cursor"].begin() } {}

auto
zpt::storage::lmdb::result::fetch(size_t _amount) -> zpt::json {
    auto _result = zpt::json::array();
    for (size_t _fetched = 0; this->__current != this->__result["cursor"].end();
         ++this->__current, ++_fetched) {
        _result << std::get<2>(*this->__current);
        if (_fetched == _amount) { break; }
    }
    return _result;
}

auto
zpt::storage::lmdb::result::generated_id() -> zpt::json {
    return this->__result["generated"];
}

auto
zpt::storage::lmdb::result::count() -> size_t {
    if (this->__result["generated"]->ok()) { return this->__result["generated"]->size(); }
    return this->__result["cursor"]->size();
}

auto
zpt::storage::lmdb::result::status() -> zpt::status {
    return static_cast<size_t>(this->__result["state"]["code"]);
}

auto
zpt::storage::lmdb::result::message() -> std::string {
    return this->__result["state"]["message"]->string();
}

auto
zpt::storage::lmdb::result::to_json() -> zpt::json {
    return this->__result;
}
