#include <fstream>
#include <sstream>
#include "Graph.h"

map<string, HT> readFile(ifstream &file)
{
    string line;
    string temp;
    string _title;
    string _date;
    string _artist;
    string _region;
    string _rank;
    string titleArtist;
    char a;

    map<string, HT>  table;

    while (getline(file, line)) {

        // Parsing
        istringstream in(line);

        in >> a;
        if (a != '\"') {
            getline(in, _title, ',');
            string s(1, a);
            _title = s + _title;

        } else {
            getline(in, _title, '"');
            getline(in, temp, ',');
        }

        getline(in, _rank, ',');
        getline(in, _date, ',');

        in >> a;
        if (a != '\"') {
            getline(in, _artist, ',');
            string s(1, a);
            _artist = s + _artist;
        } else {
            getline(in, _artist, '"');
            getline(in, temp, ',');
        }

        getline(in, _region, ',');
        if(_region == "Global"){
            continue;
        }

        titleArtist = _title  + " " + _artist;

        if (table.find(_region) != table.end()) //region already exists in table
        {
            table[_region].Insert(titleArtist);
        }
        else {
            HT newHT;
            newHT.Insert(titleArtist);
            table[_region] = newHT; //add hash table
        }
    }

    file.close();
    return table;
}

int main()
{
    cout << "Loading data..." << endl << endl;
    ifstream file("Charts");
    map<string, HT> table = readFile(file);
    Graph graph(table);

    cout << "Welcome to Global Chart Connections!" << endl;
    //main menu
    string option;
    while (option != "0")
    {

        cout << "Please select a number from the menu below:" << endl;
        cout << "0. Exit" << endl;
        cout << "1. See list of all countries" << endl;
        cout << "2. Enter 1 country, see 5 most related countries" << endl;
        cout << "3. Enter 1 country, see all related countries" << endl;
        cout << "4. Enter 2 countries, see if related" << endl;

        cin >> option;
        string temp;
        getline(cin, temp); //to clear new line
        if (option == "0")
        {
            break;
        }
        else if (option == "1")
        {
            graph.PrintCountries();
        }
        else if (option == "2")
        {
            cout << "Enter a valid country name (no extra spaces at end):";
            string country;
            getline(cin, country);
            graph.PrintConnections(country, true);
        }
        else if (option == "3")
        {
            cout << "Enter a valid country name (no extra spaces at end):";
            string country;
            getline(cin, country);
            graph.PrintConnections(country, false);
        }
        else if (option == "4")
        {
            cout << "Enter first country:";
            string country1;
            getline(cin, country1);
            cout << "Enter second country:";
            string country2;
            getline(cin, country2);
            graph.CheckIfRelated(country1, country2);
        }
        else
        {
            cout << "Invalid input! Please enter an integer from 0 to 4." << endl;
        }
        cout << endl;
    }
}