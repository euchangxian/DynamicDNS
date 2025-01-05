#include "parser.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string_view>

#include "src/core/error/error.hpp"

namespace json {

std::expected<nlohmann::json, Error> Parser::parse(std::string_view obj) const {
  try {
    return nlohmann::json::parse(obj);
  } catch (const nlohmann::json::parse_error& e) {
    return std::unexpected{error::PARSE_ERROR(e.what(), e.id, e.byte)};
  }
}

std::expected<nlohmann::json, Error> Parser::parse(
    std::filesystem::path& filePath) const {
  std::ifstream ifs(filePath);
  if (!ifs) {
    return std::unexpected{error::FILE_OPEN_ERROR(filePath)};
  }

  try {
    return nlohmann::json::parse(ifs);
  } catch (const nlohmann::json::parse_error& e) {
    return std::unexpected{error::PARSE_ERROR(e.what(), e.id, e.byte)};
  }
}

}  // namespace json
