#pragma once

#include <string>
#include <memory>
#include <functional>

namespace termix {
namespace api {

class ApiClient {
public:
    virtual ~ApiClient() = default;

    // Callback type for API responses
    using ResponseCallback = std::function<void(const std::string& response, bool success)>;

    // Virtual method for making API calls
    virtual void makeRequest(
        const std::string& endpoint,
        const std::string& requestData,
        const std::string& apiKey,
        ResponseCallback callback
    ) = 0;

    // Virtual method for chat completion
    virtual void chatCompletion(
        const std::string& prompt,
        const std::string& apiKey,
        ResponseCallback callback,
        const std::string& model = "gpt-4"
    ) = 0;

    // Factory method to create specific API clients
    static std::unique_ptr<ApiClient> create(const std::string& clientType);
};

} // namespace api
} // namespace termix
