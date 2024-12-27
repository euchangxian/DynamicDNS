#pragma once
#include <expected>
#include <ostream>
#include <string>
#include <string_view>

namespace http {

struct Response {
  std::string body{};
  long code{};

  friend std::ostream& operator<<(std::ostream& os, const Response& response);
};

struct Error {
  std::string message{};
  long code{};

  friend std::ostream& operator<<(std::ostream& os, const Error& error);
};

class IClient {
 protected:
 public:
  virtual ~IClient() = default;
  virtual std::expected<Response, Error> get(std::string_view url) = 0;
};

class Client : public IClient {
 public:
  std::expected<Response, Error> get(std::string_view url) override;
};

}  // namespace http
