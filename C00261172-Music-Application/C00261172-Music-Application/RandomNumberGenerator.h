#pragma once
#include <random>
class RandomNumberGenerator
{
public:
    static RandomNumberGenerator getInstance() {
        return RandomNumberGenerator::instance;
    }
    int getNumberFromRange(int min, int max) {
        std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);
        return distribution(this->randomNumberGenerator);
    }
private:
    static RandomNumberGenerator instance;
    RandomNumberGenerator() {
        std::random_device dev;
        this->randomNumberGenerator = std::mt19937{ dev() };
    }
    std::mt19937 randomNumberGenerator;
};

