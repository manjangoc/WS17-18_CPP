#include <iostream>
using namespace std;
#include <fstream>
#include "xyz.h"


int main()
{
    char befehl[64], noise[1];
    XYZ xyz;

    for (;;)
        {
        cout << "Was wollen sie tun:" << endl <<
                " Konvertieren (k)" << endl <<
                " Suchen (s)" << endl <<
                " Zeigen (z)" << endl <<
                " Exportieren (e)" << endl <<
                " Programm beenden (x)" << endl;
        cin.getline(befehl,64,'\n');
        switch(befehl[0])
           {
        case 'k':
            if(xyz.laden()>0)
                xyz.konvertieren();
           cin.getline(noise,64,'\n');
           break;
        case 'x':
           return 0;
        default:
           cout << befehl << " ist kein gültiger Befehl." << endl;
           break;
           }
        }
}
