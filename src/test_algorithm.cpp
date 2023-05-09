#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "filesystem"
#include "data_handler/data_handler.hpp"
#include "test/performance_tests.hpp"
using namespace std;

const string CWD = "/builds/courses/dit638/students/2023-group-11/src";

//THESE TESTS SHOW THE ACCURACY OF THE ALGO
TEST_CASE("Test Algorithm Accuracy - File 1") {

    // string filePath = "/data/Data1_SteeringAngle.csv";
    double accuracy = 0.0;

    /** Potential code for checking whether a file exists **/
    string video_data = filesystem::current_path().string() + "/data/Data1_SteeringAngle.csv";
    filesystem::path data_path{video_data};
    cout << (filesystem::exists(data_path) ? "The specified path for the video's data exists." : "File for the video's data does not exist.") << endl;
    /** ------------------------------------------------- **/

    /** Potential code for checking if algorithm's produced values exists **/
    string algo_data = filesystem::current_path().string() + "/algorithm_output/Output1_SteeringAngle.csv";
    filesystem::path algo_path{algo_data};
    cout << (filesystem::exists(algo_path) ? "The specified path for the algorithm's data exists." : "File for the algorithm's data does not exist.") << endl;
    /** ------------------------------------------------- **/

    if(filesystem::exists(data_path) && filesystem::exists(algo_path)) {
        vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(video_data);
        //string newPath = "/algorithm_output/Output1_SteeringAngle.csv";

        vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(algo_data);
        accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    }
    REQUIRE(accuracy >= 40);
}

TEST_CASE("Test Algorithm Accuracy - File 2") {
    string filePath = "/data/Data2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    double accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    REQUIRE(accuracy >= 40);
}

TEST_CASE("Test Algorithm Accuracy - File 3") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output3_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    double accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    REQUIRE(accuracy >= 40);
}


TEST_CASE("Test Algorithm Accuracy - File 4") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output4_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    double accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    REQUIRE(accuracy >= 40);
}

TEST_CASE("Test Algorithm Accuracy - File 5") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output5_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    double accuracy = performance_tests::algorithm_accuracy(dataValue, outputContent);
    REQUIRE(accuracy >= 40);
}


//THESE ARE TESTS FOR TIME TAKEN COMPARED TO DATA
TEST_CASE("Test Algorithm Time - File 1") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}

TEST_CASE("Test Algorithm Time - File 2") {
    string filePath = "/data/Data2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}

TEST_CASE("Test Algorithm Time - File 3") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output3_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}

TEST_CASE("Test Algorithm Time - File 4") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output4_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}

TEST_CASE("Test Algorithm Time - File 5") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output5_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    pair<int, int> accuracy = performance_tests::algorithm_performance_time(dataValue, outputContent);
    REQUIRE(accuracy.first == accuracy.second);
}


//THESE TESTS CHECKS TO SEE IF SECOND HAS 10 FRAMES
TEST_CASE("Test Algorithm Frame per Second - File 1") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}

TEST_CASE("Test Algorithm Frame per Second - File 2") {
    string filePath = "/data/Data2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output2_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}

TEST_CASE("Test Algorithm Frame per Second - File 3") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output3_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}


TEST_CASE("Test Algorithm Frame per Second - File 4") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output4_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}

TEST_CASE("Test Algorithm Frame per Second - File 5") {
    string filePath = "/data/Data1_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> dataValue = data_handler::read_csv_file(CWD + filePath);

    string newPath = "/algorithm_output/Output5_SteeringAngle.csv";
    vector<pair<unsigned long long int, double>> outputContent = data_handler::read_csv_file(CWD + newPath);

    double accuracy = performance_tests::algorithm_performance_frame(dataValue, outputContent);
    REQUIRE(accuracy >= 85);
}
