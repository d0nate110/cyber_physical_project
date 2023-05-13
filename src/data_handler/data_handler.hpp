#ifndef DATA_HANDLER
#define DATA_HANDLER
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

class data_handler {
public:
    static std::vector<std::pair<unsigned long long int, double>> read_csv_file(const std::string&);
    static std::string* read_csv_file(char* path);
    static bool write_csv_file(const std::string&, std::string[]);
    static bool write_csv_file(const std::string&,const std::vector<std::pair<unsigned long long int, double>>&);
};
#endif