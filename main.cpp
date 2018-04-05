#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "token.h"
int main()
{
char *elemente1[1] = {"kurs"};
char *elemente2[1] = {"person"};
char *elemente3[2] = {"vorname","famname"};
char dateiname[100];
ifstream eingabe;
ClToken *token;
ClTagset *tagset, *child;
tagset=new ClTagset(1,elemente1);
tagset->addTagset(1,0,elemente2);
child=tagset->getChild(0);
child->addTagset(2,0,elemente3);
cout << "Aus welcher Datei soll gelesen werden?" << endl;
cin >> dateiname;
eingabe.open(dateiname);
token=new ClToken;
if (token->getToken(eingabe,tagset)!=0) token->druckeToken(1);
eingabe.close();
}
