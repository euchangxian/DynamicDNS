#include <nlohmann/json.hpp>
#include <ostream>
#include <string>
#include <vector>

namespace config {

struct Config {
  std::string domain;
  std::vector<std::string> subdomains;

  std::string provider;

  // Porkbun
  std::string pbApiKey{};
  std::string pbSecretKey{};

  // TODO: Cloudflare
  std::string cfEmail{};
  std::string cfApiKey{};

  friend std::ostream& operator<<(std::ostream& os, const Config& cfg);
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config,
                                   domain,
                                   subdomains,
                                   provider,
                                   pbApiKey,
                                   pbSecretKey,
                                   cfEmail,
                                   cfApiKey);

}  // namespace config
