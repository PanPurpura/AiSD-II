#pragma once
#include <vector>

using namespace std;


class KolejkaPriorytetowa
{
    private:
        vector<int> vec;
    public:
        void insert(int x);
        int RemoveRootElem();
        void print();   //opcjonalnie dla wy�wietlenia kolejnych element�w macierzy, w kt�rej trzymany jest kopiec.
        int getRootElem();
        int leftCH(int index);    //zwraca indeks lewego dziecka
        int rightCH(int index);  //zwraca indeks prawego dziecka
        int parent(int index);  //zwraca indeks rodzica
        void goUp(int index); //przesuniecie o 1 do gory
        bool isInHeap(int x);
    
};