#include <iostream>
#include "Plecak.h"
#include <math.h>
#include <iomanip>

using namespace std;

plecak::plecak(int masa_, int lP_)
{
    masa = masa_;
    lP = lP_;

    matrix = new int * [lP+1];

    for(int i = 0; i < lP+1; i++)
    {
        matrix[i] = new int [masa+1];
    }

    cena = new int [lP];
    waga = new int [lP];
}

plecak::~plecak()
{
    for(int i = 0; i < lP+1; i++)
    {
        delete [] matrix[i];
    }

    delete [] matrix;

    delete [] waga;
    delete [] cena;
}

void plecak::save(string path)
{

    ofstream plik(path, ios_base::app);

    for(int i = 0; i < lP+1; i++)
    {
        //cout.width(5);
        //cout<<right;
        for(int j = 0; j < masa+1; j++)
        {
            plik<<setw(3)<<right<<matrix[i][j]<<" ";
        }
        plik<<endl;
    }

    plik.close();
}

void plecak::set_()
{
        for(int j = 0; j < masa+1; j++)
        {
            matrix[0][j] = 0;
        }
}

bool plecak::readFromFile(string path)
{
    ifstream plik;
    plik.open(path);

    if(!plik.good())
    {
        cout<<"Wystapil blad podczas otwierania pliku"<<endl;
        return false;
    }

    int i = 0;

    while(!plik.eof())
    {
        int Wi, Ci;
        plik >> Wi >> Ci;
        waga[i] = Wi;
        cena[i] = Ci; 
        i++;
    }

    for(i = 0; i < lP+1; i++)
    {
        for(int j = 0; j < masa+1; j++)
        {
            if(i == 0 || j == 0)
            {
                matrix[i][j] = 0;
            }
            else if(waga[i-1] <= j)
            {
                matrix[i][j] = max(cena[i - 1] + matrix[i - 1][j - waga[i - 1]], matrix[i - 1][j]);
            }
            else
            {
                matrix[i][j] = matrix[i - 1][j];
            }
        }
    }

    save("dane.txt");
    plik.close();

    ofstream plik1;
    plik1.open("dane.txt", ios_base::app);

    plik1<<endl<<endl;
    while(lP != 0)
    {
        if (matrix[lP][masa] != matrix[lP - 1][masa])
        {
            plik1<<"Package "<<lP<<" with Weight = "<<waga[lP-1]<<" and Value = "<<cena[lP-1]<<endl;

            masa = masa - waga[lP - 1];
        }
          
        lP = lP - 1;
    }
   
    return true;
}

