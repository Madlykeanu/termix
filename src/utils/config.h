#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace termix {
namespace utils {

class Config {
public:
    static Config& getInstance();

    // API key management
    void setApiKey(const std::string& provider, const std::string& key);
    std::string getApiKey(const std::string& provider) const;

    // General configuration
    void setValue(const std::string& key, const std::string& value);
    std::string getValue(const std::string& key) const;

    // Load/Save configuration
    bool loadFromFile(const std::string& filepath);
    bool saveToFile(const std::string& filepath) const;

    // Get config directory
    static std::string getConfigDir();

private:
    Config() = default;
    ~Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    std::unordered_map<std::string, std::string> apiKeys;
    std::unordered_map<std::string, std::string> settings;
};

} // namespace utils
} // namespace termix
