#include <sstream>
#include <strUtils.hpp>

namespace strUtils {
  std::vector<std::string> split(std::string &str, const char separator) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while(std::getline(iss, token, separator)) tokens.push_back(token);
    return tokens;
  }
}
