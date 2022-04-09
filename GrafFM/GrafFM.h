#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "edge.h"

using namespace std;

class GrafFM : public Graf
{
    double **tabFM;

public:
    void initialize();
    void set_w();
    void GrafFM_alg();
    bool check_cyclicity();
    void show_ways(string path);
    void free();
};
