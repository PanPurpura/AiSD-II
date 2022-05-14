#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class plecak
{
    private:
        int masa;
        int lP;

    public:
        int **matrix;
        int *cena;
        int *waga;
    public:
        plecak(int masa_, int lP_);
        ~plecak();
        void save(string path);
        void set_();
        bool readFromFile(string path);

};
