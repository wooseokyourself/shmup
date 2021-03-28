#include "base/core/Utility.hpp"

float getRadian (const float degree) {
    return degree * 3.141592653589793f / 180.0f;
}

double randomRealNumber (const double min, const double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return (double)dis(gen);
}

int randomIntegerNumber (const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return (int)dis(gen);
}