#pragma once

#include "api_client.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

namespace termix {
namespace api {

class OpenAIClient : public ApiClient {
public:
    OpenAIClient();
    ~OpenAIClient();

    void makeRequest(
        const std::string& endpoint,
        const std::string& requestData,
        const std::string& apiKey,
        ResponseCallback callback
    ) override;

    // OpenAI specific methods
    void chatCompletion(
        const std::string& prompt,
        const std::string& apiKey,
        ResponseCallback callback,
        const std::string& model = "gpt-4"
    );

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
    CURL* curl;
};

} // namespace api
} // namespace termix
