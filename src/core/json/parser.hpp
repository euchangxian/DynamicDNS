#pragma once
#include <expected>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <string_view>

#include "src/core/error/error.hpp"

namespace json {

using Error = error::Error;

class IParser {
 public:
  virtual ~IParser() = default;

  virtual std::expected<nlohmann::json, Error> parse(
      std::string_view obj) const = 0;

  virtual std::expected<nlohmann::json, Error> parse(
      std::filesystem::path& filePath) const = 0;
};

class Parser : public IParser {
 public:
  std::expected<nlohmann::json, Error> parse(
      std::string_view obj) const override;

  std::expected<nlohmann::json, Error> parse(
      std::filesystem::path& filePath) const override;
};

}  // namespace json
