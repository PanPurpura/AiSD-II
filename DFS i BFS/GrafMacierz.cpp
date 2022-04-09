#include <vector>
#include "Graf.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <queue>

using namespace std;

vector<int> visited;

Graf::Graf()
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            matrix[i][j] = -1;
        }
    }

    numberOfVertices = 0;
}

void Graf::createVertices(int ile)
{
    numberOfVertices = ile;

    for(int i = 0; i < ile; i++)
    {
        for(int j = 0; j < ile; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void Graf::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if(i_Vertex_Index_1 > (numberOfVertices-1) || i_Vertex_Index_2 > (numberOfVertices-1))
    {
        cout<<"Nie dodano krawedzi "<<i_Vertex_Index_1<<" "<<i_Vertex_Index_2<<" poniewaz:"<<endl;
        cout<<"Stworzono jedynie "<<numberOfVertices<<" wezlow!"<<endl;
        cout<<"Oznacza to ze mozna dodawac krawedzie pomiedzy wezlami o numerach <0;"<<numberOfVertices-1<<">"<<endl;
        cout<<"Aby utworzyc wiecej wezlow uzyj funkcji createVertices. UWAGA! Ponowne uzycie tej funkcji wykasuje juz istniejace krawedzie!"<<endl;
    }
    else
        matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 1;
}

void Graf::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if(checkEdge(i_Vertex_Index_1, i_Vertex_Index_2) == true)
        matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 0;
    else
        cout<<"Taka krawedz nie istnieje!"<<endl;
}

bool Graf::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if(matrix[i_Vertex_Index_1][i_Vertex_Index_2] == 1)
        return true;
    else
        return false;
}

int Graf::vertexDegree(int idx)
{
    if(idx > (numberOfVertices-1))
    {
        cout<<"W argumentach podano wezel ktory nie istnieje!"<<endl;
        return -1;
    }

    int degree = 0;

    for(int i = 0; i < numberOfVertices; i++)
    {
        if(matrix[idx][i] == 1)
            degree++;
    }

    return degree;
}

std::vector<int> Graf::getNeighbourIndices(int idx)
{
    std::vector<int> neighbours;

    if(idx > (numberOfVertices-1))
    {
        cout<<"W argumentach podano wezel ktory nie istnieje!"<<endl;
        return neighbours;
    }

    for(int i = 0; i < numberOfVertices; i++)
    {
        if(matrix[idx][i] == 1)
            neighbours.push_back(i);
    }

    return neighbours;
}

void Graf::printNeighbourIndices(int idx)
{
    if(idx > (numberOfVertices-1))
    {
        cout<<"W argumentach podano wezel ktory nie istnieje!"<<endl;
        return;
    }

    for(int i = 0; i < numberOfVertices; i++)
    {
        if(matrix[idx][i] == 1)
            std::cout<<i<<", ";
    }
    cout<<endl;
}

int Graf::getNumberOfEdges()
{
    int numberOfEdges = 0;
    vector<pair<int, int>> v;

    for(int i = 0; i < numberOfVertices; i++)
    {
        for(int j = 0; j < numberOfVertices; j++)
        {
            if(matrix[i][j] == 1)
            {
                pair<int,int> p(i, j);
                if(check(v, p) == false)
                {
                    numberOfEdges++;
                    v.push_back(p);
                    pair<int,int> p1(j, i);
                    v.push_back(p1);
                }
                else
                    continue;
            }
        }
    }

    return numberOfEdges;
}

bool Graf::check(vector<pair<int,int>> v, pair<int,int> p)
{
    for(int i = 0; i < v.size(); i++)
    {
        if((v[i].first == p.first) && (v[i].second == p.second))
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

void Graf::showMatrix(int numOfVer)
{
    for(int i  = 0; i < numOfVer; i++)
    {
        for(int j = 0; j < numOfVer; j++)
        {
            cout<<matrix[i][j]<<"\t";
        }
        cout<<endl;
    }
}

int Graf::getNumberOfVertices()
{
    return numberOfVertices;
}

bool Graf::search_in_vector(vector<int> v, int x)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i] == x)
            return true;
    }

    return false;
}

vector<int> Graf::DFS(int starting_ver)
{
    visited.push_back(starting_ver);

    vector<int> neighbours = getNeighbourIndices(starting_ver);

    for(int i = 0; i < neighbours.size(); i++)
    {
        if(search_in_vector(visited, neighbours[i]) == false)
        {
            DFS(neighbours[i]);
        }
    }

    return visited;
}

vector<int> Graf::BFS(int starting_ver)
{
    vector<int> results;
    results.push_back(starting_ver);
    queue<int> q;

    q.push(starting_ver);

    while(q.empty() == false)
    {
        int first = q.front();
        q.pop();

        vector<int> v = getNeighbourIndices(first);

        for(int i = 0; i < v.size(); i++)
        {
            if(search_in_vector(results, v[i]) == false)
            {
                q.push(v[i]);
                results.push_back(v[i]);
            }
        }
    }
    return results;
}


int main()
{
    Graf *g = new Graf();

    g->readFromFile("graf.txt");

    vector<int> v = g->DFS(2);

    for(int i = 0; i < v.size(); i++)
    {
        cout<<v[i]<<", ";
    }
    cout<<endl<<endl;

    visited.clear();

    v = g->BFS(2);

    for(int i = 0; i < v.size(); i++)
    {
        cout<<v[i]<<", ";
    }
    cout<<endl;
}




