#include "performance_tests.hpp"
#include "../data_handler/data_handler.hpp"

#define ERROR_MARGINE 0.05
#define MAX_CSV_SIZE 1000
#define ERROR_THIRTY_PERCENT 0.3

using namespace std;

double performance_tests::algorithm_accuracy(const string& errorPath, const vector<pair<unsigned long long int, double>>& dataSteering, const std::vector<std::pair<unsigned long long int, double>>& outputContent) {
    double percentageAccuracy;
    double totalCorrect = 0;
    int timestampCheckOutputIndex = 0;

    vector<std::pair<unsigned long long int, double>> dataErrors;
    vector<std::pair<unsigned long long int, double>> outErrors;
    vector<int> outIndex;
    vector<int> dataIndex;

    try {
        for(int i = 0; i < outputContent.size(); i++) {

            while(outputContent[timestampCheckOutputIndex].first < dataSteering[i].first) {
                timestampCheckOutputIndex++;
            }

            double errorMarg = dataSteering[i].second * ERROR_THIRTY_PERCENT;

            if((dataSteering[i].second == 0) && ((dataSteering[i].second + ERROR_MARGINE  >= outputContent[timestampCheckOutputIndex].second) && ((dataSteering[i].second - ERROR_MARGINE) <= outputContent[timestampCheckOutputIndex].second))) {
                totalCorrect++;

            }else if(((dataSteering[i].second + errorMarg) > 0) && ((dataSteering[i].second + errorMarg) >= outputContent[timestampCheckOutputIndex].second) && ((dataSteering[i].second - errorMarg) <= outputContent[timestampCheckOutputIndex].second)) {
                totalCorrect++;
            }else if(((dataSteering[i].second + errorMarg) < 0) && ((dataSteering[i].second + errorMarg) <= outputContent[timestampCheckOutputIndex].second) && ((dataSteering[i].second - errorMarg) >= outputContent[timestampCheckOutputIndex].second)) {
                totalCorrect++;
            }else {
                outIndex.push_back(timestampCheckOutputIndex);
                dataIndex.push_back(i);
                dataErrors.emplace_back(dataSteering[i].first, dataSteering[i].second);
                outErrors.emplace_back(outputContent[timestampCheckOutputIndex].first, outputContent[timestampCheckOutputIndex].second);
            }
        }


       data_handler::write_csv_file(errorPath, dataIndex, outIndex, dataErrors, outErrors);

    }catch (exception& e) {
        cout << e.what() << endl;
        return -1;
    }

    percentageAccuracy = (totalCorrect/dataSteering.size()) * 100;

    return percentageAccuracy;
}

pair<int, int> performance_tests::algorithm_performance_time(const vector<pair<unsigned long long int, double>>& dataSteering, const std::vector<std::pair<unsigned long long int, double>>& outputContent){
    pair<int, int> performances;

    int outputSecondsFirst = outputContent[0].first/1000000;
    int outputSecondsLast = outputContent[outputContent.size() - 1].first/1000000;

    int dataSecondsFirst = dataSteering[0].first/1000000;
    int dataSecondsLast = dataSteering[dataSteering.size() - 1].first/1000000;

    int dataTime =  outputSecondsLast - outputSecondsFirst;
    int outputTime =  dataSecondsLast - dataSecondsFirst;


    performances = make_pair(dataTime, outputTime);

    return performances;
}

double performance_tests::algorithm_performance_frame(const vector<pair<unsigned long long int, double>>& dataSteering, const std::vector<std::pair<unsigned long long int, double>>& outputContent){
    int framesCounter = 0;
    double secondsWithFrames = 0;
    double secondsTot = 0;
    int secondData = dataSteering[0].first/1000000;

    for(int i = 0; i < outputContent.size(); i ++) {
        long double secondOutput = ((long double)outputContent[i].first)/1000000;

        if(!(secondOutput < (secondData + 1) && secondOutput >= secondData)) {
            framesCounter = 0;
            secondsTot++;
            secondData++;
        }

        if(secondOutput < (secondData + 1) && secondOutput >= secondData) {
            framesCounter++;
            if(framesCounter == 10) {
                framesCounter = 0;
                secondsWithFrames++;
            }

        }
    }
    return (secondsWithFrames/secondsTot)*100;
}