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

void test1()
{
    Graf* G = new Graf();    
    G->createVertices(10);
    G->addEdge(1, 2);
    G->addEdge(2, 3);
    G->addEdge(1, 5);
    std::cout << G->vertexDegree(1)<<"\n";
    std::cout << G->vertexDegree(8) << "\n";
    G->printNeighbourIndices(1);
    G->printNeighbourIndices(1);
    std::cout << G->checkEdge(1, 2)<<"\n";
    G->removeEdge(1, 2);
    G->printNeighbourIndices(1);
    std::cout << G->checkEdge(1, 2) << "\n\n\n\n\n";   
}

void test2()
{
    Graf* G = new Graf();
    G->readFromFile("C:\\Users\\tomek\\Desktop\\algorytmy�wiczenia\\week3\\Graf1.txt");
    G->printNeighbourIndices(1);
    std::cout << G->getNumberOfEdges()<<endl;
}

int main()
{
    test1();
    test2();  

    cout<<endl<<endl;

    Graf* g = new Graf();
    g->createVertices(10);
    g->showLists();

    cout<<"Testowanie dodawania: "<<endl;
    g->addEdge(1,2);
    g->addEdge(2,1);
    g->addEdge(8,7);
    g->addEdge(7,8);
    g->addEdge(3,2);
    g->addEdge(4,1);
    g->addEdge(9,0);
    g->addEdge(0,9);
    g->addEdge(1,6);
    g->addEdge(6,4);
    g->addEdge(5,8);
    g->addEdge(0,4);
    g->addEdge(4,0);
    g->addEdge(3,4);
    g->addEdge(1,5);
    g->showLists();

    cout<<"Testowanie checEdge(): "<<endl;
    cout<<g->checkEdge(3,2)<<"  "<<g->checkEdge(0,4)<<"  "<<g->checkEdge(2,1)<<"  "<<g->checkEdge(4,5)<<endl;

    cout<<"Testowanie obliczania stopnia: "<<endl;
    cout<<g->vertexDegree(9)<<"  "<<g->vertexDegree(0)<<"  "<<g->vertexDegree(6)<<"  "<<g->vertexDegree(12)<<endl;

    cout<<"Lista sasiadow: "<<endl;
    vector<int> v = g->getNeighbourIndices(1);
    for(int i = 0; i < v.size(); i++)
    {
        cout<<v[i]<<", ";
    }

    cout<<endl;
    cout<<"Wyswietlanie sasiadow: "<<endl;
    g->printNeighbourIndices(7);
    g->printNeighbourIndices(3);
     g->printNeighbourIndices(12);

    cout<<"Liczba wszystkich krawedzi: "<<endl;
    cout<<g->getNumberOfEdges()<<endl;

    cout<<"Testowanie usuwania krawedzi: "<<endl;
    g->removeEdge(4,1);
    g->removeEdge(1,5);
    g->removeEdge(0,9);
    g->showLists();

    cout<<"Testowanie wczytywania z pliku na nowym obiekcie: "<<endl;
    Graf* g1 = new Graf();
    g1->readFromFile("plik.txt");
    g1->showLists();

    cout<<"Liczba krawedzi dla g1: "<<g1->getNumberOfEdges()<<endl;
    cout<<"Stopien dla wezla o numerze 1: "<<g1->vertexDegree(1)<<endl;


}




