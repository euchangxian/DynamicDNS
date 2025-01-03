#include "types.hpp"

#include <nlohmann/json.hpp>

namespace dns::record {

void from_json(const nlohmann::json& j, Record& r) {
  std::string type;
  j.at("name").get_to(r.name);
  j.at("type").get_to(type);
  r.type = Type::fromString(type);
  j.at("content").get_to(r.content);
  j.at("ttl").get_to(r.ttl);
}

void to_json(nlohmann::json& j, const Record& r) {
  j = nlohmann::json{
      {"name", r.name},
      {"type", r.type.toString()},
      {"content", r.content},
      {"ttl", r.ttl},
  };
}

}  // namespace dns::record
