#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include "edge.h"
#include "Graf.h"

using namespace std;

struct compare_
{
    bool operator ()(const edge & e1, const edge & e2)
    {
        if(e1.waga > e2.waga) return true;
        if(e1.waga < e2.waga) return false;

        return false;
    }
};

class GPrime : public Graf
{
protected:
        vector<int> visited;
        priority_queue<edge, vector<edge>, compare_> p_queue;
        vector<edge> edgesInMST;
public:
        void add_edges(int start_ver);
        void Prime();
        bool check_if(edge temp);
        void show(int start_ver);

};
