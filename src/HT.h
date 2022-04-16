#pragma once
#include <set>
#include <string>
using namespace std;

class HT {
private:
    int size;
    int capacity;
    float LF = 0.75;
    set<string>* arr;

public:
    HT();
    void Insert(string val); //val is title+artist
    void CheckResize();
    bool Has(string val);
    int GetSize();
    int GetCap();
    set<string>* GetArr();
};


