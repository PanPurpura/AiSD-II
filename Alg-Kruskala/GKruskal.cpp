#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "edge.h"
#include "Graf.h"
#include "GKruskal.h"
#include <queue>
#include <math.h>


void GKruskal::initialize_sr()
{
    for(int i = 0; i < numOfVer; i++)
    {
        struk_rozlaczna.push_back(i);
    }
}

bool GKruskal::check_cyclicity(int a, int b)
{
    if(struk_rozlaczna[a] == struk_rozlaczna[b])
        return true;
    else
        return false;
}

void GKruskal::add_edges()
{
    for(int i = 0; i < vertexList.size(); i++)
    {
        for(int j = 0; j < vertexList[i].size(); j++)
        {
            p_queue.push(vertexList[i][j]);
        }
    }
}

void GKruskal::Kruskal()
{
    while(!p_queue.empty())
    {
        edge temp = p_queue.top();
        p_queue.pop();

        if((check_cyclicity(temp.vertex_Index1, temp.vertex_Index2)) == true)
            continue;
        else
        {
            int min_ = min(struk_rozlaczna[temp.vertex_Index1], struk_rozlaczna[temp.vertex_Index2]);
            int max_ = max(struk_rozlaczna[temp.vertex_Index1], struk_rozlaczna[temp.vertex_Index2]);

            for(int i = 0; i < struk_rozlaczna.size(); i++)
            {
                if(struk_rozlaczna[i]==max_)
                    struk_rozlaczna[i] = min_;
            }

            edgeInMST.push_back(temp);
        }
    }
    
}

int GKruskal::sum_of_w()
{
    int sum = 0;
    for(int i = 0; i < edgeInMST.size(); i++)
    {
        sum += edgeInMST[i].waga;
    }

    return sum;
}


int main()
{
    GKruskal *g = new GKruskal();
    g->readFromFile("GrafMST_JawneKrawedzie1.txt");
    g->add_edges();
    g->initialize_sr();  
    g->Kruskal();

    cout<<"Suma krawedzi w MST (Kruskal): "<<g->sum_of_w()<<endl;
}