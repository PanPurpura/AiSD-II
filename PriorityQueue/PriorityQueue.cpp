#include <bits/stdc++.h>
#include "KolejkaPriorytetowa.h"

int KolejkaPriorytetowa::leftCH(int index)
{
    return (2*index) - 1;
}

int KolejkaPriorytetowa::rightCH(int index)
{
    return ((2*index) + 1) - 1;
}

int KolejkaPriorytetowa::parent(int index)
{
   return floor((double)index/2.0) - 1;
}

void KolejkaPriorytetowa::goUp(int index)
{
    int p = parent(index+1);
    int temp = vec[p];
    vec[p] = vec[index];
    vec[index] = temp;
    
}

void KolejkaPriorytetowa::insert(int x)
{
    if(vec.size() == 0)
        vec.push_back(x);
    else if(isInHeap(x) == false)
    {
        vec.push_back(x);
        int index = vec.size() - 1;
        int p = parent(index+1);
        while(vec[index] > vec[p] && index > 0)
        {
            goUp(index);
            index = p;
            p = parent(index+1);
        }
    }
    else
        cout<<endl<<"Nie wolno duplikowac elementow! Taki element jest juz w kolejce"<<endl;

}

int KolejkaPriorytetowa::RemoveRootElem()
{
    if(vec.size() == 0)
    {
        cout<<endl<<"Kolejka jest pusta"<<endl;
        return -1;
    }
    else
    {
        vector<int>::iterator it = vec.end()-1;
        int last = vec.size() - 1;
        int index = 0;
        int returned = vec[index];
        vec[index] = vec[last];
        vec.erase(it);

        

        int leftChild = leftCH(index+1);
        int rightChild = rightCH(index+1);

        while(vec[leftChild] > vec[index] || vec[rightChild] > vec[index])
        {
            if(vec[leftChild] > vec[rightChild])
            {
                goUp(leftChild);
                index = leftChild;

                leftChild = leftCH(index+1);
                rightChild = rightCH(index+1);

                if((leftChild < 0) || (leftChild > (vec.size() -1)) == true)
                    break;
                else if((rightChild < 0) || (rightChild > (vec.size() -1)) == true)
                    break;
            }
            else
            {
                goUp(rightChild);
                index = rightChild;

                leftChild = leftCH(index+1);
                rightChild = rightCH(index+1);
                if((leftChild < 0) || (leftChild > (vec.size() -1)) == true)
                    break;
                else if((rightChild < 0) || (rightChild > (vec.size() -1)) == true)
                    break;
            }
        }

        return returned;
    }
    
}

int KolejkaPriorytetowa::getRootElem()
{
    return vec[0];
}

void KolejkaPriorytetowa::print()
{
    cout<<endl<<"Kolejne indeksy vectora: "<<endl;

    for(int i = 0; i < vec.size(); i++)
        cout<<vec[i]<<"  ";
}

bool KolejkaPriorytetowa::isInHeap(int x)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == x)
            return true;
    }

    return false;
}

int main()
{
    KolejkaPriorytetowa prq;

    cout<<"Testowanie dodawania: "<<endl;

    prq.insert(50);
    prq.insert(30);
    prq.insert(20);
    prq.insert(15);
    prq.insert(10);
    prq.insert(8);
    prq.insert(16);

    prq.print();

    cout<<endl<<"Root element: "<<prq.getRootElem();

    prq.insert(60);

    prq.print();
    cout<<endl<<"Root element: "<<prq.getRootElem();

    prq.insert(40);

    prq.print();
    cout<<endl<<"Root element: "<<prq.getRootElem();

    prq.insert(55);
    
    prq.print();
    cout<<endl<<"Root element: "<<prq.getRootElem();
    
    cout<<endl<<endl<<"Testowanie usuwania: "<<endl<<endl;

    cout<<endl<<"Element usuwany: "<<prq.RemoveRootElem();
    prq.print();
    cout<<endl<<"Root element: "<<prq.getRootElem();

    cout<<endl<<"Element usuwany: "<<prq.RemoveRootElem();
    prq.print();
    cout<<endl<<"Root element: "<<prq.getRootElem();

    cout<<endl<<"Element usuwany: "<<prq.RemoveRootElem();
    prq.print();
    cout<<endl<<"Root element: "<<prq.getRootElem();

    cout<<endl<<"Element usuwany: "<<prq.RemoveRootElem();
    prq.print();
    cout<<endl<<"Root element: "<<prq.getRootElem();
    
}

