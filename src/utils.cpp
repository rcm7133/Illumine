#include "utils.h"

namespace Utils {
    /**
     * Read a file in as a vector of chars
     * @param filename path to file as string
     * @return vector of chars representing the file contents
     */
    std::vector<char> ReadFile(const std::string& filename) {
        // Open the file at the end so we can figure out how many chars to allocate
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file " + filename);
        }
        // Allocate char buffer and read from beginning
        std::vector<char> buffer(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        file.close();
        return buffer;
    }
}