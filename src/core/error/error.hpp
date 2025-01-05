#pragma once
#include <cstddef>
#include <filesystem>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace error {

class Error : public std::runtime_error {
 private:
  long code_;

 public:
  std::string message;

  Error(std::string msg, long code = 0)
      : std::runtime_error(std::move(msg)), code_(code) {}

  long code() const noexcept { return code_; }

  friend std::ostream& operator<<(std::ostream& os,
                                  const Error& error) noexcept;
};

constexpr auto FILE_OPEN_ERROR = [](std::filesystem::path& file) -> Error {
  return Error{std::format("failed to open file: {}", file.string())};
};

constexpr auto PARSE_ERROR =
    [](std::string_view what, int id, std::size_t byte) -> Error {
  return Error{std::format("{}\exception id: {}\nbyte position of error: {}",
                           what, id, byte)};
};

constexpr auto JSON_KEY_NOT_FOUND_ERROR = [](std::string_view key) -> Error {
  return std::format("{} key not found", key);
};

constexpr auto INVALID_DOMAIN_ERROR = [](std::string_view domain) -> Error {
  return std::format("invalid domain name: {}", domain);
};

constexpr auto INVALID_ENV_VAR_ERROR = [](std::string_view envKey) -> Error {
  return std::format("invalid environment variable {}", envKey);
};

}  // namespace error
