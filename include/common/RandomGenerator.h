#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <type_traits>
#include "utils/Logger.h"

namespace Utils {

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
    std::vector<T> generate_vector(size_t size, T minVal = 1, T maxVal = 100);

private:
    // Private constructor so nobody can "new" it
    RandomGenerator() : rd(), gen(rd()) {}

    std::random_device rd;
    std::mt19937 gen;
};

} // namespace Utils

// ─────────────────────────────────────────────
//  Convenience macros — use these everywhere
// ─────────────────────────────────────────────
#define Random_Vector(T, sz, min, max) Utils::RandomGenerator::getInstance().generate_vector<T>(sz, min, max)
