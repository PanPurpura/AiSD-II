#include <iostream>
#include "Plecak.h"
#include <math.h>

using namespace std;

int main()
{
    plecak *p = new plecak(24, 12);

    p->set_();
    cout<<endl<<endl;

    p->readFromFile("plecakZadanieG3.txt");

    p->save("dane.txt");

    //p->analyse("plecak.txt");

    //p->show();
    p->~plecak();
    return 0;
}
