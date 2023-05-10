#include "data_handler.hpp"

#define MAX_CSV_SIZE 1000
#define CSV_VALUE_COLUMN 6
#define CSV_TIMESTAMP_SEC_COLUMN 4
#define CSV_TIMESTAMP_MILISEC_COLUMN 5
#define CSV_VALUE_OUTPUT_COLUMN 2
#define CSV_TIMESTAMP_OUTPUT_COLUMN 1


using namespace std;
vector<pair<unsigned long long int, double>> data_handler::read_csv_file(const string& path) {
    vector<pair< unsigned long long int, double>> time_angleList;
    vector<vector<string>> content;
    vector<string> row;
    string line, word;
    int dataIndex = 0;

    cout << "<< " << __LINE__ << " <<" << endl;
    fstream file;
    file.open(path, fstream::in);
    cout << "<< " << __LINE__ << " <<" << endl;
    
    try {
        if(file.is_open()) {
                cout << "<< " << __LINE__ << " <<" << endl;
                while(getline(file, line)) {
                row.clear();
                stringstream str(line);

                while(getline(str, word, ';'))
                    cout << "<< " << __LINE__ << " << Dataindex: " << dataIndex << endl;
                    row.push_back(word);
                    content.push_back(row);
                    dataIndex++;
            }
        } else
            throw runtime_error("Could not open the .csv file" );

        string isData = path.substr(2, 4);
        cout << "<< " << __LINE__ << " << " << isData << endl;
        unsigned long long int timestamp;
        double gsr = 0;

        for(int i = 0; i < content.size(); i++) {
            try {
                if(isData == "data") {
                    cout << "<< " << __LINE__ << " <<" << endl;
                    cout << "<< " << row.size() << "<<" content.size() << " <<" << endl;
                    cout << "<< " << CSV_TIMESTAMP_SEC_COLUMN << " <<" << CSV_TIMESTAMP_MILISEC_COLUMN << " <<" << CSV_VALUE_COLUMN << " <<" << endl;
                    // if((stod(content[i][CSV_VALUE_COLUMN]) < (second + 0.5) && stod(content[i][CSV_VALUE_COLUMN]) > (second - 0.5)) || i == 0) {
                        timestamp = stoll(content[i][CSV_TIMESTAMP_SEC_COLUMN])*1000000 + (stoll(content[i][CSV_TIMESTAMP_MILISEC_COLUMN]));
                        gsr =  stod(content[i][CSV_VALUE_COLUMN]);
                    //}
                } else {
                    timestamp = stoll(content[i][CSV_TIMESTAMP_OUTPUT_COLUMN]);
                    cout << "<< " << __LINE__ << " << Frame read..." << endl;
                    gsr =  stod(content[i][CSV_VALUE_OUTPUT_COLUMN]);
                    cout << timestamp << ";" << gsr << endl;
                }

                time_angleList.emplace_back(timestamp, gsr);

            }catch(exception& e) {
                throw runtime_error(strcat((char*)"Could not convert read values to decimals: ", e.what()));
            }
        }
    } catch(exception& e) {
        cout << e.what() << endl;
        time_angleList[0].first = -1;
        time_angleList[0].second = -1;
        return time_angleList;
    }
    return time_angleList;
}

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

bool data_handler::write_csv_file(const string& path, const vector<pair<unsigned long long int, double>>& dataOut) {

    try {
        fstream fout;

        fout.open(path, ios::out | ios::trunc);
        if (fout.fail()) {
            throw runtime_error("Could not create file");
        }

        for (int i = 0; i < dataOut.size(); i++) {
            fout << "group_11;"
                 << (dataOut[i].first) << ";"
                 << dataOut[i].second
                 << "\n";
        }

    } catch (exception& e) {
        cout << "Error writing file: " << e.what() << endl;
        return false;
    }

    return true;
}