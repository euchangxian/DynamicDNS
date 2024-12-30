#include <iostream>

#include "core/http/client.hpp"
#include "core/ip/resolver.hpp"

int main() {
  http::Client httpClient{};
  json::Parser jsonParser{};
  auto ipv4 = ip::Resolver<ip::V4>{httpClient, jsonParser}.getCurrentIP();
  if (!ipv4) {
    std::cout << ipv4.error() << '\n';
  } else {
    std::cout << ipv4.value().address << '\n';
  }
  return 0;
}
