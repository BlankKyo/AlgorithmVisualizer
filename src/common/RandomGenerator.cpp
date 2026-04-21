// src/common/RandomGenerator.cpp
#include "common/RandomGenerator.h"



namespace Utils {

static const char* TAG = "RandomGenerator";

/********************
 *  Template method for generating vectors of integers
 *  Usage: auto vec = RandomGenerator::getInstance().generate_vector<int>(10, 1, 100);
 ********************/
template<typename T>
std::vector<T> RandomGenerator::generate_vector(size_t size, T minVal, T maxVal) {
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


// This forces the compiler to create the template versions of the function
template std::vector<int> RandomGenerator::generate_vector<int>(size_t, int, int);
template std::vector<long> RandomGenerator::generate_vector<long>(size_t, long, long);
template std::vector<short> RandomGenerator::generate_vector<short>(size_t, short, short);

}
