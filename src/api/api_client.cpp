#include "api_client.h"
#include "openai_client.h"
#include <stdexcept>

namespace termix {
namespace api {

std::unique_ptr<ApiClient> ApiClient::create(const std::string& clientType) {
    if (clientType == "openai") {
        return std::make_unique<OpenAIClient>();
    }
    // Add more client types here as they are implemented
    
    throw std::runtime_error("Unknown API client type: " + clientType);
}

} // namespace api
} // namespace termix
