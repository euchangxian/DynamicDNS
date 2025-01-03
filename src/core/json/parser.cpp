#include "parser.hpp"

#include <format>
#include <nlohmann/json.hpp>
#include <string_view>

namespace json {

std::expected<Parsed, Error> Parser::parse(std::string_view obj) const {
  try {
    return nlohmann::json::parse(obj);
  } catch (const nlohmann::json::parse_error& e) {
    return std::unexpected{
        Error(std::format("{}\nexception id: {}\nbyte position of error: {}",
                          e.what(), e.id, e.byte))};
  }
}

}  // namespace json
