#include<fstream>
#include<sstream>
#include<map>
#include<string>
#include<vector>
#include<iomanip>
#include<iostream>
using namespace std;

int main(){
    
    ofstream myFile("newFile1.csv");
    ifstream file("charts.csv");
    if (!file.is_open()) {
        cout << "File not opened!";
    }
   
    string line;
    //title,rank,date,artist,url,region,chart,trend,streams

    string _title;
    string _rank;
    string _date;
    string _artist;
    string _url;
    string _region;
    string _chart;
    string _trend;
    string _streams;

    string temp;

        int r;

    int j = 0;
    string currDate;
    string title = "";
    bool firstDate = true;
    bool working = false;

    char a;
//title,rank,date,artist,url,region,chart,trend,streams
    while (getline(file, line)) {
        
        istringstream in(line);
        in >> a;
        if(a != '\"'){
            getline(in, _title, ',');
            string s(1,a);
            _title = s + _title;

        }
        else{
            getline(in, _title, '"');
            getline(in, temp, ',');


        }

        getline(in, _rank, ',');
        getline(in, _date, ',');
        if(_date.substr(0,4) != "2017"){
            continue;
        }
        
        
        in >> a;
        if(a != '\"'){
            getline(in, _artist, ',');
             string s(1,a);
            _artist = s + _artist;
        }
        else{
            getline(in, _artist, '"');
            getline(in, temp, ',');

        }

        getline(in, _url, ',');
        getline(in, _region, ',');
        getline(in, _chart, ',');
        getline(in, _trend, ',');
        getline(in, _streams, ',');


        myFile << "\"" << _title << "\"" << "," << _rank << "," << _date << "," << "\"" << _artist << "\"" << "," << _region << endl;
        
       /* if(j == 130000)
            break;
        j++;*/

    }
}