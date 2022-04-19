#include <fstream>
#include <sstream>
#include <chrono>
#include "Graph.h"

void PrintMenu()
{
    cout << "Please select a number from the menu below:" << endl;
    cout << "0. Exit" << endl;
    cout << "1. See list of all countries" << endl;
    cout << "2. Enter 1 country, see 5 most related countries" << endl;
    cout << "3. Enter 1 country, see all related countries" << endl;
    cout << "4. Enter 2 countries, see if related" << endl;
}

void readFileHT(ifstream &file, map<string, HT>& table, map<string, unordered_set<string>>& stlTable, bool useHT)
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

    while (getline(file, line))
    {
        // Parsing
        istringstream in(line);
        in >> a;
        if (a != '\"')
        {
            getline(in, _title, ',');
            string s(1, a);
            _title = s + _title;
        }
        else
        {
            getline(in, _title, '"');
            getline(in, temp, ',');
        }

        getline(in, _rank, ',');
        getline(in, _date, ',');

        in >> a;
        if (a != '\"')
        {
            getline(in, _artist, ',');
            string s(1, a);
            _artist = s + _artist;
        }
        else
        {
            getline(in, _artist, '"');
            getline(in, temp, ',');
        }

        getline(in, _region, ',');
        if(_region == "Global")
            continue;
        titleArtist = _title  + " " + _artist;

        if (useHT)
        {
            if (table.find(_region) != table.end()) //region already exists in tabl
                table[_region].Insert(titleArtist);
            else
            {
                HT newHT;
                newHT.Insert(titleArtist);
                table[_region] = newHT; //add hash table
            }
        }
        else //use unordered set
        {
            if (stlTable.find(_region) != stlTable.end())
                stlTable[_region].insert(titleArtist); //insert to stl unordered set
            else
            {
                unordered_set<string> uoSet;
                uoSet.insert(titleArtist);
                stlTable[_region] = uoSet;
            }
        }
    }
    file.close();
}

void WorkWithUser(Graph& graph)
{
    cout << "Welcome to Global Chart Connections!" << endl;
    string option;
    while (option != "0")
    {
        PrintMenu();
        cin >> option;
        string temp;
        getline(cin, temp); //to clear new line
        if (option == "0")
        {
            cout << "Program terminated. Goodbye!" << endl;
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
            cout << "Invalid input! Please enter an integer from 0 to 4." << endl;
        cout << endl;
    }
}

int main()
{
    ifstream file("Charts");
    cout << "Enter 1 to use our hash table, or 2 to use STL unordered set:";
    int choice;
    cin >> choice;
    cout << "Loading data..." << endl << endl;
    map<string, HT> table;
    map<string, unordered_set<string>> stlTable;
    if (choice == 1)
    {
        /* chrono usage for execution time taken from
          https://www.geeksforgeeks.org/measure-execution-time-function-cpp/ */
        auto start = chrono::high_resolution_clock::now();
        readFileHT(file, table, stlTable, true);
        Graph graph(table);

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
        cout << "Time taken to insert data into HashTables and create Graph:" << duration.count() << " milliseconds" << endl << endl;

        WorkWithUser(graph);
    }
    else if (choice == 2)
    {
        auto start = chrono::high_resolution_clock::now();
        readFileHT(file, table, stlTable, false);
        Graph graph(stlTable);

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
        cout << "Time taken to insert data into HashTable:" << duration.count() << " milliseconds" << endl << endl;

        WorkWithUser(graph);
    }
    else
        cout << "Invalid selection. Please try again and select enter either 1 or 2. Goodbye!" << endl;


}