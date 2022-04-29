#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include "edge.h"
#include "Graf.h"
#include "GPrime.h"

using namespace std;

void GPrime::add_edges(int start_ver)
{
    visited.push_back(start_ver);

    for(int i = 0; i < vertexList[start_ver].size(); i++)
    {
        p_queue.push(vertexList[start_ver][i]);
    }
}

bool GPrime::check_if(edge temp)
{
    for(int i = 0; i < visited.size(); i++)
    {
        if(temp.vertex_Index2 == visited[i])
            return true;
    }

    return false;
}

void GPrime::Prime()
{
    while(visited.size() < numOfVer)
    {
        edge temp = p_queue.top();
        p_queue.pop();

        if(check_if(temp) == true)
        {
                continue;
        }
        else
        {
            visited.push_back(temp.vertex_Index2);         
            edgesInMST.push_back(temp);
            
            for(int i = 0; i < vertexList[temp.vertex_Index2].size(); i++)
            {
                p_queue.push(vertexList[temp.vertex_Index2][i]);
            }
        }
    }
}

void GPrime::show(int start_ver)
{
    int sum = 0;

    cout<<"Kolejność wierzchołków dodawanych do listy odwiedzonych (startując z wierzchołka o indeksie "<<start_ver<<") w algorytmie Prima:"<<endl;
    for(int i = 0; i < visited.size(); i++)
    {
        cout<<visited[i]<<", ";
    }
    cout<<endl;

    for(int i = 0; i < edgesInMST.size(); i++)
    {
        sum += edgesInMST[i].waga;
    }

    cout<<"Suma wag krawedzi MST: "<<sum<<endl;;
    
}

int main()
{
    GPrime *g = new GPrime();
    g->readFromFile("GrafPrzyklad.txt");
    g->add_edges(4);
    g->Prime();
    g->show(4);

    cout<<endl<<endl;

    GPrime *g1 = new GPrime();
    g1->readFromFile("GrafPrzyklad.txt");
    g1->add_edges(11);
    g1->Prime();
    g1->show(11);

    cout<<endl<<endl;

    GPrime *g2 = new GPrime();
    g2->readFromFile("GrafMST_JawneKrawedzie2.txt");
    g2->add_edges(4);
    g2->Prime();
    g2->show(4);
}

