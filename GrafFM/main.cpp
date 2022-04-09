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

int main()
{
    GrafFM *g = new GrafFM();
   // GrafFM *g1 = new GrafFM();

    g->readFromFile("Graf21.txt");
    //g1->readFromFile("Graf2.txt");

    g->initialize();
    g->set_w();
    g->GrafFM_alg();
    if(g->check_cyclicity() == true)
        cout<<"Graf ma cykle ktorych suma wag jest ujemna!"<<endl<<endl;
    else
        g->show_ways("Wynik21.txt");

    /*g1->initialize();
    g1->set_w();
    g1->GrafFM_alg();
    if(g1->check_cyclicity() == true)
        cout<<"Graf ma cykle ktorych suma wag jest ujemna!"<<endl<<endl;
    else
        g1->show_ways("Wynik2.txt");*/

    g->free();
    //g1->free();

    return 0;
}
