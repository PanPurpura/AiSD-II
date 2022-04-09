#include "Graf.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "edge.h"

using namespace std;

Graf::Graf()
{
    vertexList.clear();
}

void Graf::createVertices(int ile)
{
    for(int i = 0; i < ile; i++)
    {
        vector<edge> edges;
        vertexList.push_back(edges);
    }
}

void Graf::showLists()
{
    for(int i = 0; i < vertexList.size(); i++)
    {
        cout<<i<<" --> ";
        for(int j = 0; j < vertexList[i].size(); j++)
        {
            
            cout<<vertexList[i][j].vertex_Index2<<", ";
        }
        cout<<endl;
    }
}

void Graf::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if(i_Vertex_Index_1 > (vertexList.size()-1) || i_Vertex_Index_2 > (vertexList.size()-1))
    {
        cout<<"Nie dodano krawedzi "<<i_Vertex_Index_1<<" "<<i_Vertex_Index_2<<" poniewaz:"<<endl;
        cout<<"Stworzono jedynie "<<vertexList.size()<<" wezlow!"<<endl;
        cout<<"Oznacza to ze mozna dodawac krawedzie pomiedzy wezlami o numerach <0;"<<vertexList.size()-1<<">"<<endl;
        cout<<"Aby utworzyc wiecej wezlow uzyj funkcji createVertices. UWAGA! Ponowne uzycie tej funkcji wykasuje juz istniejace krawedzie!"<<endl;
    }
    else
    {
        edge ed(i_Vertex_Index_1, i_Vertex_Index_2);

        vertexList[i_Vertex_Index_1].push_back(ed);
    }
}

bool Graf::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if(checkEdge(i_Vertex_Index_1, i_Vertex_Index_2) == true)
    {
        std::vector<edge>::iterator it;

        int i = 0;
        for(i; i < vertexList[i_Vertex_Index_1].size(); i++)
        {
            if((vertexList[i_Vertex_Index_1][i].vertex_Index1 == i_Vertex_Index_1) && 
                (vertexList[i_Vertex_Index_1][i].vertex_Index2 == i_Vertex_Index_2))
            {
                break;
            }
        }
        it = vertexList[i_Vertex_Index_1].begin() + i;
        vertexList[i_Vertex_Index_1].erase(it);

        return true;
    }
    else
    {
        cout<<"Taka krawedz nie istnieje!"<<endl;
        return false;
    }
    
}

bool Graf::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if(i_Vertex_Index_1 > (vertexList.size()-1) || i_Vertex_Index_2 > (vertexList.size()-1))
    {
        cout<<"W argumentach podano wezel ktory nie istnieje!"<<endl;
        return false;
    }

    for(int i = 0; i < vertexList[i_Vertex_Index_1].size(); i++)
    {
        if((vertexList[i_Vertex_Index_1][i].vertex_Index1 == i_Vertex_Index_1) && (vertexList[i_Vertex_Index_1][i].vertex_Index2 == i_Vertex_Index_2))
            return true;
    }

    return false;
}

int Graf::vertexDegree(int idx)
{
    if(idx > (vertexList.size()-1))
    {
        cout<<"W argumentach podano wezel ktory nie istnieje!"<<endl;
        return -1;
    }

    return vertexList[idx].size();
}

std::vector<int> Graf::getNeighbourIndices(int idx)
{
    vector<int> neighbours;

    if(idx > (vertexList.size()-1))
    {
        cout<<"W argumentach podano wezel ktory nie istnieje!"<<endl;
        return neighbours;
    }

    for(int i = 0; i < vertexList[idx].size(); i++)
    {
        neighbours.push_back(vertexList[idx][i].vertex_Index2);
    }

    return neighbours;
}

void Graf::printNeighbourIndices(int idx)
{
    if(idx > (vertexList.size()-1))
    {
        cout<<"W argumentach podano wezel ktory nie istnieje!"<<endl;
        return;
    }

    for(int i = 0; i < vertexList[idx].size(); i++)
    {
        cout<<vertexList[idx][i].vertex_Index2<<", ";
    }

    cout<<endl;
}

int Graf::getNumberOfEdges()
{
    int sum = 0;
    vector<edge> v;

    for(int i = 0; i < vertexList.size(); i++)
    {
        for(int j = 0; j < vertexList[i].size(); j++)
        {
            if(checkEdgesPresence(v, vertexList[i][j]) == false)
            {
                sum++;
                v.push_back(vertexList[i][j]);
                edge e1(vertexList[i][j].vertex_Index2, vertexList[i][j].vertex_Index1);
                v.push_back(e1);
            }
            else
                continue;                          
        }
    }

    return sum;
}

bool Graf::checkEdgesPresence(vector<edge> ed, edge e1)
{
    for(int i = 0; i < ed.size(); i++)
    {
        if((ed[i].vertex_Index1 == e1.vertex_Index1) && (ed[i].vertex_Index2 == e1.vertex_Index2))
            return true;
    }

    return false;
}

bool Graf::readFromFile(std::string path)
{
    int numberOfVer;
    ifstream plik;
    plik.open(path);

    if(!plik.good())
    {
        cout<<"Wystapil blad podczas otwierania pliku!"<<endl;
        return false;
    }

    plik >> numberOfVer;

    createVertices(numberOfVer);
    while(!plik.eof())
    {
        int l,k;
        plik >> l >> k;

        addEdge(l, k);
    }
    plik.close();

    return true;
    
} 




