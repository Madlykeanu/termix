#include "config.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace termix {
namespace utils {

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

void Config::setApiKey(const std::string& provider, const std::string& key) {
    apiKeys[provider] = key;
}

std::string Config::getApiKey(const std::string& provider) const {
    auto it = apiKeys.find(provider);
    return (it != apiKeys.end()) ? it->second : "";
}

void Config::setValue(const std::string& key, const std::string& value) {
    settings[key] = value;
}

std::string Config::getValue(const std::string& key) const {
    auto it = settings.find(key);
    return (it != settings.end()) ? it->second : "";
}

bool Config::loadFromFile(const std::string& filepath) {
    try {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            spdlog::error("Failed to open config file: {}", filepath);
            return false;
        }

        nlohmann::json j;
        file >> j;

        // Load API keys
        if (j.contains("api_keys")) {
            auto keys = j["api_keys"];
            for (auto it = keys.begin(); it != keys.end(); ++it) {
                apiKeys[it.key()] = it.value();
            }
        }

        // Load settings
        if (j.contains("settings")) {
            auto configs = j["settings"];
            for (auto it = configs.begin(); it != configs.end(); ++it) {
                settings[it.key()] = it.value();
            }
        }

        return true;
    } catch (const std::exception& e) {
        spdlog::error("Error loading config: {}", e.what());
        return false;
    }
}

bool Config::saveToFile(const std::string& filepath) const {
    try {
        nlohmann::json j;
        j["api_keys"] = apiKeys;
        j["settings"] = settings;

        std::ofstream file(filepath);
        if (!file.is_open()) {
            spdlog::error("Failed to open config file for writing: {}", filepath);
            return false;
        }

        file << j.dump(4);
        return true;
    } catch (const std::exception& e) {
        spdlog::error("Error saving config: {}", e.what());
        return false;
    }
}

} // namespace utils
} // namespace termix
