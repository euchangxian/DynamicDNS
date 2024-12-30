#pragma once
#include <expected>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>

namespace http {

struct Response {
  const std::string body{};
  const long code{};

  explicit Response(std::string body, long code)
      : body(std::move(body)), code(code) {}

  friend std::ostream& operator<<(std::ostream& os,
                                  const Response& response) noexcept;
};

struct Error {
  const std::string message{};
  const long code{};

  explicit Error(std::string msg, long code)
      : message(std::move(msg)), code(code) {}

  friend std::ostream& operator<<(std::ostream& os,
                                  const Error& error) noexcept;
};

class IClient {
 public:
  virtual ~IClient() = default;
  virtual std::expected<Response, Error> get(std::string_view url) = 0;
};

class Client : public IClient {
 public:
  std::expected<Response, Error> get(std::string_view url) override;
};

}  // namespace http
