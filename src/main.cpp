#include <iostream>

#include "core/http/client.hpp"
#include "core/ip/resolver.hpp"

int main() {
  std::cout << ip::Resolver<ip::V4>{}.getCurrentIP().address << '\n';
  std::cout << ip::Resolver<ip::V6>{}.getCurrentIP().address << '\n';

  http::Client client{};
  auto result = client.get(ip::V4::SERVICE_URL);
  if (result) {
    std::cout << (*result) << '\n';
  } else {
    std::cout << result.error() << '\n';
  }

  return 0;
}
