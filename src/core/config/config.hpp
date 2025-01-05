#include <expected>
#include <filesystem>
#include <string_view>

#include "src/core/error/error.hpp"
#include "src/core/json/parser.hpp"
#include "types.hpp"

namespace config {

using Error = error::Error;

// TODO: check if supporting multiple config file locations is necessary.
constexpr std::string_view CONFIG_PATH{"~/.config/ddns/config.json"};
constexpr std::string_view XDG_CONFIG{".config"};
constexpr std::string_view APP_CONFIG_DIR{"ddns"};
constexpr std::string_view CONFIG_FILE_NAME{"config.json"};

class IManager {
 public:
  virtual ~IManager() = default;

  virtual std::expected<Config, Error> loadConfig() const = 0;

  virtual std::expected<bool, Error> writeConfig(
      const Config& config) const = 0;
};

class Manager final : public IManager {
 public:
  explicit Manager(const json::IParser& parser) : jsonParser_(parser) {}

  std::expected<Config, Error> loadConfig() const override;

  // NOTE: For some reason, returning std::expected<void, Error> is tricky?
  // Not able to get it to work.
  std::expected<bool, Error> writeConfig(const Config& config) const override;

 private:
  const json::IParser& jsonParser_;

  std::expected<Config, Error> readConfigFile(
      std::filesystem::path& filePath) const;

  std::expected<std::filesystem::path, Error> ensureConfigFile() const;

  static Config defaultConfig();
};

}  // namespace config
