#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "edge.h"


class Graf
{
protected:
    std::vector<std::vector<edge>> vertexList;

public: 
    Graf();
    void createVertices(int ile);    
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);    
    bool removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    int vertexDegree(int idx); 
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    bool readFromFile(std::string path); 
    void showLists();
    bool checkEdgesPresence(std::vector<edge> ed, edge e1); //Sprawdza czy dana krawedz jest juz w zbiorze. Sluzy do liczenia krawedzi w grafie, zeby nie zliczac
                                        //dwukrotnie tej samej krawedzi w grafie nieskierowanym.
};

