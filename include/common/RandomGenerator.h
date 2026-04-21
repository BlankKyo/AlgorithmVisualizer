#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <type_traits>
#include "utils/Logger.h"

namespace Utils {

static const char* TAG = "RandomGenerator";

class RandomGenerator {
public:
    // Delete copy constructor and assignment to ensure it stays a singleton
    RandomGenerator(const RandomGenerator&) = delete;
    RandomGenerator& operator=(const RandomGenerator&) = delete;

    // The Access Point
    static RandomGenerator& getInstance() {
        static RandomGenerator instance; 
        return instance;
    }

    // Template for generating vectors of integers
    template<typename T = int>
    std::vector<T> generate_vector(size_t size, T minVal = 1, T maxVal = 100) {
        if constexpr (!std::is_integral<T>::value) {
            LOG_ERROR(TAG, "T must be an integral type.");
            return {};
        }
        std::vector<T> vec(size);
        std::uniform_int_distribution<T> dis(minVal, maxVal);

        for (auto& item : vec) {
            item = dis(gen);
        }
        LOG_INFO(TAG, "Generated vector of size " + std::to_string(size) + 
                         " with values in range [" + std::to_string(minVal) + ", " + std::to_string(maxVal) + "]");
        return vec;
    }

private:
    // Private constructor so nobody can "new" it
    RandomGenerator() : rd(), gen(rd()) {}

    std::random_device rd;
    std::mt19937 gen;
};

} // namespace Utils