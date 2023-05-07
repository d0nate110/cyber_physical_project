#ifndef PERFORMANCE_TESTS_HPP
#define PERFORMANCE_TESTS_HPP


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>
#include <stdexcept>
#include <cstring>
#include <utility>
#include <iomanip>

class performance_tests {
public:
    static double algorithm_accuracy(const std::vector<std::pair<unsigned long long int, double>>&, const std::vector<std::pair<unsigned long long int, double>>&);
    static std::pair<int, int> algorithm_performance_time(const std::vector<std::pair<unsigned long long int, double>>&, const std::vector<std::pair<unsigned long long int, double>>&);
    static double algorithm_performance_frame(const std::vector<std::pair<unsigned long long int, double>>&, const std::vector<std::pair<unsigned long long int, double>>&);
};

#endif //PERFORMANCE_TESTS_HPP