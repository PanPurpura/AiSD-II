#include <vector>
#include "Graf.h"
#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

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
    G->readFromFile("C:\\Users\\tomek\\Desktop\\algorytmy�wiczenia\\week3\\Graf.txt");
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
    g->showMatrix(g->getNumberOfVertices());

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
    g->showMatrix(g->getNumberOfVertices());

    cout<<"Testowanie checkEdge(): "<<endl;
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
    g->showMatrix(g->getNumberOfVertices());

    cout<<"Testowanie wczytywania z pliku na nowym obiekcie: "<<endl;
    Graf* g1 = new Graf();
    g1->readFromFile("plik.txt");
    g1->showMatrix(g1->getNumberOfVertices());

    cout<<"Liczba krawedzi dla g1: "<<g1->getNumberOfEdges()<<endl;
    cout<<"Stopien dla wezla o numerze 1: "<<g1->vertexDegree(1)<<endl;

}




