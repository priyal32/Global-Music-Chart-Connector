#include "Graph.h"

Graph::Graph(map<string, unordered_set<string>>& stlTable)
{
    //add all countries to graph so we don't have to check it later
    for (auto it = stlTable.begin(); it != stlTable.end(); it++)
    {
        vector<pair<string, int>> vec;
        string country = it->first;
        graph[country] = vec;
    }
    AddEdges(stlTable);
}

Graph::Graph(map<string, HT>& table)
{
    //add all countries to graph so we don't have to check it later
    for (auto it = table.begin(); it != table.end(); it++)
    {
        vector<pair<string, int>> vec;
        string country = it->first;
        graph[country] = vec;
    }
    AddEdges(table);
}

void Graph::AddEdges(map<string, unordered_set<string>>& stlTable)
{
    for (auto it = stlTable.begin(); it != stlTable.end(); it++)
    {
        string currCountry = it->first;
        unordered_set<string>& currTable = it->second;

        for (auto nextIt = stlTable.begin(); nextIt != stlTable.end(); nextIt++)
        {
            //iterate thru rest of table for comparisons to make edges
            if (nextIt->first == currCountry)
                continue; //don't compare it to self
            else
            {
                string currComp = nextIt->first;
                if (!IsEdge(currCountry, currComp)) //if edge doesn't already exist
                {
                    unordered_set<string> currCompTable = nextIt->second;
                    int rank = 0;
                    if (currTable.size() > currCompTable.size())//returns true if currTable is smaller or equal to currComp
                    {
                        rank = GetEdgeRank(currTable, currCompTable); //call this on smaller table to make faster
                    } else {
                        rank = GetEdgeRank(currCompTable, currTable);
                    }

                    if (rank != 0) //add edge to both vertices since undirected
                    {
                        graph[currCountry].push_back({currComp, rank});
                        graph[currComp].push_back({currCountry, rank});
                    }
                }
            }

        }
    }
}

void Graph::AddEdges(map<string, HT>& table)
{
    for (auto it = table.begin(); it != table.end(); it++)
    {
        string currCountry = it->first;
        HT& currTable = it->second;

        for (auto nextIt = table.begin(); nextIt != table.end(); nextIt++)
        {
            //iterate thru rest of table for comparisons to make edges
            if (nextIt->first == currCountry)
                continue; //don't compare it to self
            else
            {
                string currComp = nextIt->first;
                if (!IsEdge(currCountry, currComp)) //if edge doesn't already exist
                {
                    HT &currCompHT = nextIt->second;
                    int rank = 0;
                    if (CompareHTSize(currTable, currCompHT))//returns true if currTable is smaller or equal to currComp
                    {
                        rank = GetEdgeRank(currTable, currCompHT); //call this on smaller table to make faster
                    } else {
                        rank = GetEdgeRank(currCompHT, currTable);
                    }

                    if (rank != 0) //add edge to both vertices since undirected
                    {
                        graph[currCountry].push_back({currComp, rank});
                        graph[currComp].push_back({currCountry, rank});
                    }
                }
            }

        }
    }
}

int Graph::GetEdgeRank(HT &currTable, HT &compTable)
{
    int rank = 0;
    set<string>* currSet = currTable.GetArr();
    for (int i = 0; i < currTable.GetCap(); i++)
    {
        if (currSet[i].empty())
        {
            continue;
        }
        else
        {
            for (auto songIt = currSet[i].begin(); songIt != currSet[i].end(); songIt++)
            {
                //iterate thru currTable's set at index i, see if song exists in other table
                if (compTable.Has(*songIt)) //see if curr song is in other table
                    rank++;
            }
        }
    }
    return rank;
}

int Graph::GetEdgeRank(unordered_set<string>& currTable, unordered_set<string>& compTable)
{
    int rank = 0;
    for (auto it = currTable.begin(); it != currTable.end(); it++)
    {
        string currSong = *it;
        if (compTable.count(currSong) != 0)
        {
            //song exists in compTable
            rank++;
        }

    }
    return rank;
}

bool Graph::IsEdge(string country1, string country2) {
    for (int i = 0; i < graph[country1].size(); i++)
    {
        //edge is made for both countries when made, so we don't need to check both
        if (graph[country1][i].first == country2)
            return true;
    }
    return false;
}

bool Graph::CompareHTSize(HT& a, HT& b) //true if a < b
{
    //used to pick smaller table to fully iterate thru since sizes can be very different
    if (a.GetSize() <= b.GetSize())
        return true;
    return false;
}

void Graph::PrintCountries()
{
    for (auto it = graph.begin(); it != graph.end(); it++)
    {
        cout << it->first << endl;
    }
}

bool Graph::FindCountry(string country)
{
    if (graph.find(country) == graph.end())
    {
        return false;
    }
    return true;
}

vector<pair<string, int>> Graph::GetAdj(string country)
{
    vector<pair<string, int>> vec = graph[country];
    /* modified sort algorithm is courtesy of Evan Teran on stack overflow
     * https://stackoverflow.com/questions/279854/how-do-i-sort-a-vector-of-pairs-based-on-the-second-element-of-the-pair */
    sort(vec.begin(), vec.end(), [](auto& left, auto& right)
    {
        return left.second > right.second;
    });
    return vec;
}

void Graph::PrintConnections(string country, bool top5)
{
    if (FindCountry(country))
    {
        vector<pair<string, int>> vec = GetAdj(country);
        for (int i = 0; i < vec.size(); i++)
        {
            cout << vec[i].first << " has " << vec[i].second << " songs in common" << endl;
            if (top5 && i == 4)
                break; //will only print first 5
        }
    }
    else
    {
        cout << "Invalid input :( Please check input and ensure correct spelling." << endl;
        cout << "Use option 4 to check if country exists in dataset." << endl;
    }
}

void Graph::CheckIfRelated(string country1, string country2)
{
    if (FindCountry(country1) && FindCountry(country2))
    {
        bool connected = false;
        for (int i = 0; i < graph[country1].size(); i++)
        {
            if (graph[country1][i].first.compare(country2) == 0)
            {
                cout << country1 << " and " << country2 << " share " << graph[country1][i].second << " songs!" << endl;
                connected = true;
                break;
            }
        }

        if (!connected)
        {
            cout << country1 << " and " << country2 << " do not share any songs :(" << endl;
        }

    }
    else
    {
        cout << "Invalid input :( Please check input and ensure correct spelling." << endl;
        cout << "Use option 4 to check if BOTH countries exists in dataset." << endl;
    }
}