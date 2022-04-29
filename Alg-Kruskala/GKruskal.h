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

class GKruskal : public Graf
{
protected:
        priority_queue<edge, vector<edge>, compare_> p_queue; 
        vector<edge> edgeInMST;
        vector<int> struk_rozlaczna;
public:
        void Kruskal();
        void initialize_sr();
        bool check_cyclicity(int a, int b);
        void add_edges();
        int sum_of_w();
};