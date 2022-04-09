#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Graf.h"
#include "edge.h"
#include <queue>

using namespace std;

class g_acyclic : public Graf
{

    queue<int> qOfVer;
    vector<int> sorted;
    vector<int> counted_edges;

public:
    void count_edges();
    bool check_acyclity();
    vector<int> topology_sort();
    void vec_initialize(int size);
};