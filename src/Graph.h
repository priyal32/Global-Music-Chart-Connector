#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>
#include <algorithm>
#include "HT.h"
using namespace std;

class Graph
{
private:
    map<string, vector<pair<string, int>>> graph;
    // country              country, rank
    void AddEdges(map<string, HT>& table);
    void AddEdges(map<string, unordered_set<string>>& stlTable);
    bool IsEdge(string country1, string country2);
    bool CompareHTSize(HT& a, HT& b);
    int GetEdgeRank(HT& currTable, HT& compTable);
    int GetEdgeRank(unordered_set<string>& currTable, unordered_set<string>& compTable);

    bool FindCountry(string country);
    vector<pair<string, int>> GetAdj(string country);

public:
    Graph(map<string, HT>& table);
    Graph(map<string, unordered_set<string>>& stlTable);
    void PrintCountries();
    void PrintConnections(string country, bool top5);
    void CheckIfRelated(string country1, string country2);
};