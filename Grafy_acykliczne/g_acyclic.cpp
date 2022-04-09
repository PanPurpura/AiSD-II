#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Graf.h"
#include "edge.h"
#include "g_acyclic.h"

using namespace std;

void g_acyclic::vec_initialize(int size)
{
    for(int i = 0; i < size; i++)
    {
        counted_edges.push_back(0);
    }
}


bool g_acyclic::check_acyclity()
{
    if(sorted.size() == vertexList.size())
        return true;

    return false;
}

void g_acyclic::count_edges()
{
    vec_initialize(vertexList.size());

    for(int i = 0; i < vertexList.size(); i++)
    {
        for(int j = 0; j < vertexList[i].size(); j++)
        {
            counted_edges[vertexList[i][j].vertex_Index2]++;
        }
    }
}

vector<int> g_acyclic::topology_sort()
{
    for(int i = 0; i < counted_edges.size(); i++)
    {
        if(counted_edges[i] == 0)
        {
            qOfVer.push(i);
        }
    }

    while(!qOfVer.empty())
    {
        int elem = qOfVer.front();
        qOfVer.pop();

        sorted.push_back(elem);
        vector<int> neighbours = getNeighbourIndices(elem);

        for(int i = 0; i < neighbours.size(); i++)
        {
            counted_edges[neighbours[i]]--;

            if(counted_edges[neighbours[i]] == 0)
            {
                qOfVer.push(neighbours[i]);
            }
        }
    }

    if(!check_acyclity())
    {
        cout<<"Graf jest cykliczny!"<<endl;
        sorted.clear();
        counted_edges.clear();
    }

    return sorted;
}

int main()
{
    g_acyclic *g = new g_acyclic();
    g->readFromFile("Graf1.txt");
    g->count_edges();

    vector<int> res = g->topology_sort();

    for(int i = 0; i < res.size(); i++)
    {
        cout<<res[i]<<", ";
    }
    cout<<endl;

    res.clear();

    g_acyclic *g1 = new g_acyclic();

    g1->readFromFile("Graf2.txt");
    g1->count_edges();

    res = g1->topology_sort();

    for(int i = 0; i < res.size(); i++)
    {
        cout<<res[i]<<", ";
    }
    cout<<endl;


    return 0;
}