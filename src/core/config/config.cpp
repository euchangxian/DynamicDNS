#include "config.hpp"

#include <cassert>
#include <cstdlib>
#include <expected>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <string>

#include "src/core/error/error.hpp"

namespace config {

std::expected<Config, Error> Manager::loadConfig() const {
  auto filePath = ensureConfigFile();
  if (!filePath) {
    // TODO: Check if error messages are copied... Could be lots of memcpy.
    return std::unexpected{filePath.error()};
  }
  return readConfigFile(*filePath);
}

std::expected<bool, Error> Manager::writeConfig(const Config& config) const {
  auto filePath = ensureConfigFile();
  if (!filePath) {
    return std::unexpected{filePath.error()};
  }

  nlohmann::json jsonCfg = config;
  std::ofstream ofs(*filePath);
  ofs << std::setw(4) << jsonCfg << std::endl;  // write prettified
  return true;
}

std::expected<Config, Error> Manager::readConfigFile(
    std::filesystem::path& filePath) const {
  // TODO: determine what errors can be thrown from Serializing
  return jsonParser_.parse(filePath);
}

std::expected<std::filesystem::path, Error> Manager::ensureConfigFile() const {
  const char* home = std::getenv("HOME");
  if (!home) {
    return std::unexpected{error::INVALID_ENV_VAR_ERROR("HOME")};
  }

  std::filesystem::path configDir =
      std::filesystem::path(home) / XDG_CONFIG / APP_CONFIG_DIR;
  std::filesystem::path configPath = configDir / CONFIG_FILE_NAME;

  std::string message = "created:\n";
  bool needEdit = false;
  if (!std::filesystem::exists(configDir)) {
    try {
      std::filesystem::create_directories(configDir);
      message += "directory " + configDir.string() + '\n';
      needEdit = true;
    } catch (const std::filesystem::filesystem_error& e) {
      return std::unexpected{Error(e.what())};
    }
  }

  if (!std::filesystem::exists(configPath)) {
    try {
      std::ofstream ofs(configPath);
      nlohmann::json defaultCfg = defaultConfig();
      ofs << std::setw(4) << defaultCfg;

      message += "file " + configPath.string() + '\n';
      needEdit = true;
    } catch (const std::exception& e) {
      return std::unexpected{Error(e.what())};
    }
  }

  if (needEdit) {
    message += "***please edit the configuration file***";
    return std::unexpected{Error(message)};
  }

  return configPath;
}

Config Manager::defaultConfig() {
  return Config{
      .domain = "example.com",
      .subdomains = {"www", "vpn"},
      .provider = "porkbun",
      .pbApiKey = "pb_api_key",
      .pbSecretKey = "pb_secret_key",
  };
}

}  // namespace config
