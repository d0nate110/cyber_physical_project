#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "data_handler/data_handler.hpp"
#include "test/performance_tests.hpp"
using namespace std;


//THESE TESTS SHOW THE ACCURACY OF THE ALGO
TEST_CASE("Test Algorithm Accuracy - File 1") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    REQUIRE(accuracy >= 40);
}

TEST_CASE("Test Algorithm Accuracy - File 2") {
    string filePath = "../data/Data2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    REQUIRE(accuracy >= 40);
}

TEST_CASE("Test Algorithm Accuracy - File 3") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output3_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    REQUIRE(accuracy >= 40);
}


TEST_CASE("Test Algorithm Accuracy - File 4") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output4_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    REQUIRE(accuracy >= 40);
}

TEST_CASE("Test Algorithm Accuracy - File 5") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output5_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    REQUIRE(accuracy >= 40);
}


//THESE ARE TESTS FOR TIME TAKEN COMPARED TO DATA
TEST_CASE("Test Algorithm Time - File 1") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}

TEST_CASE("Test Algorithm Time - File 2") {
    string filePath = "../data/Data2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}

TEST_CASE("Test Algorithm Time - File 3") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output3_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}

TEST_CASE("Test Algorithm Time - File 4") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output4_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}

TEST_CASE("Test Algorithm Time - File 5") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output5_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}


//THESE TESTS CHECKS TO SEE IF SECOND HAS 10 FRAMES
TEST_CASE("Test Algorithm Frame per Second - File 1") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}

TEST_CASE("Test Algorithm Frame per Second - File 2") {
    string filePath = "../data/Data2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}

TEST_CASE("Test Algorithm Frame per Second - File 3") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output3_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}


TEST_CASE("Test Algorithm Frame per Second - File 4") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output4_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}

TEST_CASE("Test Algorithm Frame per Second - File 5") {
    string filePath = "../data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(filePath);

    string newPath = "../algorithm_output/Output5_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}