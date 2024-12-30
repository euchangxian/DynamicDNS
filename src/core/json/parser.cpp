#include "parser.hpp"

#include <format>
#include <nlohmann/json.hpp>
#include <ostream>
#include <string_view>

namespace json {

std::ostream& operator<<(std::ostream& os, const Error& error) noexcept {
  return os << "json error: " << error.message;
}

std::expected<Parsed, Error> Parser::parse(std::string_view obj) {
  try {
    return nlohmann::json::parse(obj);
  } catch (const nlohmann::json::parse_error& e) {
    return std::format("{}\nexception id: {}\nbyte position of error: {}",
                       e.what(), e.id, e.byte);
  }
}

}  // namespace json
