#include "openai_client.h"
#include <spdlog/spdlog.h>

namespace termix {
namespace api {

OpenAIClient::OpenAIClient() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }
}

OpenAIClient::~OpenAIClient() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

size_t OpenAIClient::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void OpenAIClient::makeRequest(
    const std::string& endpoint,
    const std::string& requestData,
    const std::string& apiKey,
    ResponseCallback callback
) {
    if (!curl) {
        callback("CURL not initialized", false);
        return;
    }

    std::string readBuffer;
    struct curl_slist* headers = nullptr;
    
    // Set headers
    headers = curl_slist_append(headers, "Content-Type: application/json");
    std::string authHeader = "Authorization: Bearer " + apiKey;
    headers = curl_slist_append(headers, authHeader.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestData.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK) {
        std::string error = "curl_easy_perform() failed: " + std::string(curl_easy_strerror(res));
        spdlog::error(error);
        callback(error, false);
        return;
    }

    callback(readBuffer, true);
}

void OpenAIClient::chatCompletion(
    const std::string& prompt,
    const std::string& apiKey,
    ResponseCallback callback,
    const std::string& model
) {
    nlohmann::json requestJson = {
        {"model", model},
        {"messages", {
            {
                {"role", "user"},
                {"content", prompt}
            }
        }}
    };

    makeRequest(
        "https://api.openai.com/v1/chat/completions",
        requestJson.dump(),
        apiKey,
        callback
    );
}

} // namespace api
} // namespace termix
