#pragma once

#include <zapata/json.h>

namespace zpt {
namespace uri {
auto
parse(std::string _in, zpt::JSONType _type = zpt::JSObject) -> zpt::json;
auto
parse(std::istream& _in, zpt::JSONType _type = zpt::JSObject) -> zpt::json;
auto
to_regex(zpt::json _in) -> zpt::json;
auto
to_regex_object(zpt::json _in) -> zpt::json;
auto
to_regex_array(zpt::json _in) -> zpt::json;
} // namespace uri
} // namespace zpt