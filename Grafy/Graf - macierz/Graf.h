#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
//#include "edge.h"

class Graf
{
    //od razu musimy zadeklarowa� maksymaln� ilo�� wierzcho�k�w - tutaj 100;
    static const int SIZE = 10000;
    int matrix[SIZE][SIZE];
    int numberOfVertices;

public:
    Graf();
    void createVertices(int ile);    
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);    
    void removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    int vertexDegree(int idx); 
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    bool readFromFile(std::string path); 
    void showMatrix(int numOfVer);
    bool check(std::vector<std::pair<int,int>> v, std::pair<int, int> p);
    int getNumberOfVertices();

private:
    void clear();
};

