#include "HT.h"

HT::HT()
{
    size = 0;
    capacity = 100;
    arr = new set<string>[capacity];
}

void HT::Insert(string val)
{
    int index = val.length() % capacity;
    if (arr[index].empty())
    {
        //no set at this index yet
        set<string> newSet;
        newSet.insert(val);
        arr[index] = newSet;
    }
    else
    {
        arr[index].insert(val);
    }
    size++;
    CheckResize();
}

void HT::CheckResize()
{
    float currLF = (float)size / capacity;
    if (currLF >= LF)
    {
        //need to resize
        set<string>* temp = arr;
        capacity = capacity * 2;
        size = 0;
        arr = new set<string>[capacity];
        for (int i = 0; i < capacity/2; i++)
        {
            set<string>& currSet = temp[i];
            for (auto it = currSet.begin(); it != currSet.end(); it++)
            {
                Insert(*it);
            }
        }
        delete[] temp;
    }
}

bool HT::Has(string val)
{
    int key = val.length() % capacity;
    if (arr[key].empty())
        return false;
    else
    {
        if (arr[key].count(val) == 1)
        {
            //set containts val
            return true;
        }
    }
    return false;
}

int HT::GetSize()
{
    return size;
}

int HT::GetCap()
{
    return capacity;
}

set<string>* HT::GetArr()
{
    return arr;
}