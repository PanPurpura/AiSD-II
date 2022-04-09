#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "edge.h"
#include "Graf.h"
#include "GrafFM.h"
#include <limits>

using namespace std;

void GrafFM::initialize()
{
    tabFM = new double *[numOfVer];
    double inf = std::numeric_limits<double>::infinity();
    for(int i = 0; i < numOfVer; i++)
    {
        tabFM[i] = new double [numOfVer];
        for(int j = 0; j < numOfVer; j++)
        {
            if(i == j)
                tabFM[i][j] = 0.0;
            else
                tabFM[i][j] = inf;
        }
    }
}

void GrafFM::set_w()
{
    for(unsigned int i = 0; i < vertexList.size(); i++)
    {
        for(unsigned int j = 0; j < vertexList[i].size(); j++)
        {
            tabFM[vertexList[i][j].vertex_Index1][vertexList[i][j].vertex_Index2] = vertexList[i][j].waga;
        }
    }
}

void GrafFM::GrafFM_alg()
{
    for(int k = 0; k < numOfVer; k++)
    {
        for(int i = 0; i < numOfVer; i++)
        {
            for(int j = 0; j < numOfVer; j++)
            {
                if(tabFM[i][j] > tabFM[i][k] + tabFM[k][j])
                    tabFM[i][j] = tabFM[i][k] + tabFM[k][j];
            }
        }
    }
}

bool GrafFM::check_cyclicity()
{
    for(int i = 0; i < numOfVer; i++)
    {
        if(tabFM[i][i] < 0)
            return true;
    }
    return false;
}

void GrafFM::show_ways(string path)
{
    ofstream plik(path, ios_base::app);

    for(int i = 0; i < numOfVer; i++)
    {
        for(int j = 0; j < numOfVer; j++)
        {
            plik<<tabFM[i][j]<<", ";
        }
        plik<<endl;
    }
    plik<<endl<<endl<<endl<<endl;

    for(int i = 0; i < numOfVer; i++)
    {
        plik<<"Koszt dotarcia z wierzcholka "<<i<<" do wierzcholka:"<<endl;
        for(int j = 0; j < numOfVer; j++)
        {
            plik<<j<<" wynosi "<<tabFM[i][j]<<endl;
        }
        plik<<endl;
    }
    plik.close();
    
}

void GrafFM::free()
{
    for(int i = 0; i < numOfVer; i++)
    {
        delete [] tabFM[i];
    }
    delete [] tabFM;
    tabFM = NULL;
}
