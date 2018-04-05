#include <iostream>
using namespace std;
#include <fstream>
#include "txttoken.h"


ClTxtToken::ClTxtToken()
{
    *id='\0';
    *place='\0';
    *stock='\0';
    tokenChild= NULL;
}


int ClTxtToken::getToken(ifstream &datei)
{

    int zaehler;
    enum txtZustand txtZustand = zId;
    char zeichen;

    char puffer[100];

    for (zaehler=0;;)
    {
        datei.get(zeichen);
        if (datei.eof())
        {
            if (*id == '\0' && tokenChild == NULL)
                return 0;;
            if (txtZustand==zStock){
                puffer[zaehler]='\0';
                strcpy(stock,puffer);
            }
            return 1;
        }
        switch(zeichen)
        {
        case ' ':
            if (txtZustand == zId)
            {
                if (zaehler!=0)
                {
                    puffer[zaehler]='\0';
                    strcpy(id,puffer);
                    zaehler=0;
                    txtZustand = zPlace;
                }
            }
            else if (txtZustand == zPlace)
            {
                if (zaehler!=0)
                {
                    puffer[zaehler]='\0';
                    strcpy(place,puffer);
                    zaehler=0;
                    txtZustand = zStock;
                }
            }
            else
            {
                cout << "Fehler im Txt-Dokument.\n" << endl;
                return  0;
            }
            break;
        case '\n':
            if (txtZustand==zStock)
            {
                puffer[zaehler]='\0';
                strcpy(stock,puffer);
                txtZustand = zNoise;

                tokenChild = new ClTxtToken;
                tokenChild->getToken(datei);
            }
            else
            {
                cout << "Fehler im Txt-Dokument (an der Stelle Stock).\n" << endl;
                return  0;
            }
            break;
        default:
            puffer[zaehler]=zeichen;
            zaehler++;
            break;
        }
    }
}


void ClTxtToken::druckeToken()
{
    cout <<  getId() << " " << getPlace() << " " <<  getStock() << endl;

    if (tokenChild!=NULL)
        tokenChild->druckeToken();
}
