#include "performance_tests.hpp"

#define ERROR_MARGINE 0.05
#define MAX_CSV_SIZE 1000
#define ERROR_THIRTY_PERCENT 0.3

using namespace std;

double performance_tests::algorithm_accuracy(const vector<pair<unsigned long long int, double>>& dataSteering, const std::vector<std::pair<unsigned long long int, double>>& outputContent) {
    double percentageAccuracy;
    double totalCorrect = 0;
    double total;
    int timestampCheckOutputIndex = 0;

    try {
        for(int i = 0; i < outputContent.size(); i++) {

            if(dataSteering.size() > outputContent.size()) {
                throw runtime_error("The performance of the two did not match.");
            }

            double errorMarg = dataSteering[i].second * ERROR_THIRTY_PERCENT;

            if(dataSteering[i].second == 0) {
                if(ERROR_MARGINE >= outputContent[timestampCheckOutputIndex].second && ERROR_MARGINE <= outputContent[timestampCheckOutputIndex].second) {
                    totalCorrect++;
                }
            }else if((dataSteering[i].second + errorMarg) >= outputContent[timestampCheckOutputIndex].second && (dataSteering[i].second - errorMarg) <= outputContent[timestampCheckOutputIndex].second) {
                totalCorrect++;
            }
            while(((outputContent[timestampCheckOutputIndex].first) <= dataSteering[i].first) && ((outputContent[timestampCheckOutputIndex + 1].first) > dataSteering[i].first))
                timestampCheckOutputIndex++;
            total = i + 1;
        }

    }catch (exception& e) {
        cout << e.what() << endl;
        return -1;
    }

    percentageAccuracy = (totalCorrect/total) * 100;

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

    for(int i = 0; i < outputContent.size(); i ++) {
        long double secondOutput = ((long double)outputContent[i].first)/1000000;
        int secondData = dataSteering[i].first/1000000;

        if(secondOutput < (secondData + 1) && secondOutput >= secondData) {
            framesCounter++;
            if(framesCounter == 10) {
                framesCounter = 0;
                secondsWithFrames++;
            }


        }else {
            framesCounter = 0;
            secondsTot++;
        }
    }
    return (secondsWithFrames/secondsTot)*100;
}