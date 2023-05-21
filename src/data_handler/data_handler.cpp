#include "data_handler.hpp"

#define MAX_CSV_SIZE 1000
#define CSV_VALUE_COLUMN 6
#define CSV_TIMESTAMP_SEC_COLUMN 4
#define CSV_TIMESTAMP_MILISEC_COLUMN 5
#define CSV_VALUE_OUTPUT_COLUMN 2
#define CSV_TIMESTAMP_OUTPUT_COLUMN 1


using namespace std;
/**
 * Reads the frametimestamp and steering angle from a csv file
 * @param path the path belonging to the file which will be read
 * @return a list of pairs containing frametimestamp and steering angle
 */
vector<pair<unsigned long long int, double>> data_handler::read_csv_file(const string& path) {
    vector<pair< unsigned long long int, double>> time_angleList;
    vector<vector<string>> content;
    vector<string> row;
    string line, word;
    int dataIndex = 0;

    fstream file (path, ios::in);

    try {
        if(file.is_open()) {
            while(getline(file, line)) {
                row.clear();
                stringstream str(line);

                while(getline(str, word, ';'))
                    row.push_back(word);
                content.push_back(row);
                dataIndex++;
            }
        }else
            throw runtime_error("Could not open the .csv file" );


        string isData = path.substr(2, 4);
        unsigned long long int first;
        double second = 0;


            for(int i = 0; i < content.size(); i++) {

                try {
                    if(isData == "data") {

                        first = stoll(content[i][CSV_TIMESTAMP_SEC_COLUMN])*1000000 + (stoll(content[i][CSV_TIMESTAMP_MILISEC_COLUMN]));
                        second =  stod(content[i][CSV_VALUE_COLUMN]);


                    }else {

                        first = stoll(content[i][CSV_TIMESTAMP_OUTPUT_COLUMN]);
                        second =  stod(content[i][CSV_VALUE_OUTPUT_COLUMN]);
                    }
                    time_angleList.emplace_back(first, second);

                }catch(exception& e) {
                    throw runtime_error(strcat((char*)"Could not convert read values to decimals: ", e.what()));
                }

            }


    }catch(exception& e) {

        cout << e.what() << endl;
        time_angleList[0].first = -1;
        time_angleList[0].second = -1;
        return time_angleList;
    }
    return time_angleList;
}

/**
 * Method which reads a csv file that is any form. Supposed to be for allpurposes
 * @param path the path belonging to the file which will be read
 * @return a string containing everything from the csv file
 */
string* data_handler::read_csv_file(char* path) {
    string* outputContent = new string[MAX_CSV_SIZE];
    string line, word;
    int dataIndex = 0;


    fstream file (path, ios::in);
    try {

        if(file.is_open()) {
            getline(file, line);
                stringstream str(line);
                while(getline(str, word, ';')) {
                    *(outputContent + dataIndex) = word;
                    dataIndex++;
                }
        }else
            throw runtime_error("Could not open the .csv file" );

    }catch(exception& e) {
        cout << e.what() << endl;
        outputContent[0] = " ";
        return outputContent;
    }

    outputContent[dataIndex] = " ";
    return outputContent;
}
/**
 * Overwrites/writes a file with the given string. Supposed to be for allpurposes
 * @param path the path at which the file shall be located
 * @param data a large string containing everything to be printed
 * @return true if success, false if unsuccessful
 */
bool data_handler::write_csv_file(const string& path, string data[]) {

    try {
        fstream fout;

        fout.open(path, ios::out | ios::trunc);
        if (fout.fail()) {
            throw runtime_error("Could not create file");
        }

        for (int i = 0; i < data->size(); i++) {
            if (!(fout << data[i] << ";")) {
                throw runtime_error("Error writing to file");
            }
        }

    } catch (exception& e) {
        cout << "Error writing file: " << e.what() << endl;
        return false;
    }

    return true;
}

/**
 * Overwrites/writes a file with the framtimestamps and steering angles
 * @param path the path at which the file shall be located
 * @param dataOut the list of pairs containing frametimestamps and stering angle which shall be printed
 * @return true if success, false if unsuccessful
 */
bool data_handler::write_csv_file(const string& path, const vector<pair<unsigned long long int, double>>& dataOut) {

    try {
        fstream fout;

        fout.open(path, ios::out | ios::trunc);



        for (int i = 0; i < dataOut.size(); i++) {
            fout << "group_11;"
                 << (dataOut[i].first) << ";"
                 << dataOut[i].second
                 << "\n";
        }

        if (fout.fail()) {
            throw runtime_error("Could not create file");
        }

    } catch (exception& e) {
        cout << "Error writing file: " << e.what() << endl;
        return false;
    }

    return true;
}

/**
 * Overwrites/writes a file with information about certain frames that were previously found as inaccurate
 * @param path the path at which the file shall be located
 * @param indexData the list of frame numbers from given data where comparision failed
 * @param indexOut the list of frame numbers from outputted where comparision failed
 * @param dataOut list of pairs containing frametimestamp and steeringwheelangle that was given
 * @param algoOut list of pairs containing frametimestamp and steeringwheelangle that was outputted from our algorithm
 * @return true if success, false if unsuccessful
 */
bool data_handler::write_csv_file(const string& path, const vector<int>& indexData, const vector<int>& indexOut, const vector<pair<unsigned long long int, double>>& dataOut, const vector<pair<unsigned long long int, double>>& algoOut) {

    try {
        fstream fout;

        fout.open(path, ios::out | ios::trunc);


        for (int i = 0; i < dataOut.size(); i++) {
            fout << dataOut[i].first << "::"
                 << algoOut[i].first << "!!"
                 << dataOut[i].second << "::"
                 << algoOut[i].second << "!!"
                 << indexData[i] << "::"
                 << indexOut[i]
                 << "\n";
        }

        if (fout.fail()) {
            throw runtime_error("Could not create file");
        }

    } catch (exception& e) {
        cout << "Error writing file: " << e.what() << endl;
        return false;
    }

    return true;
}