#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "xyz.h"

XYZ::XYZ()
{
    xmlToken=NULL;
    txtToken=NULL;
}

//laden der Datein
int XYZ::laden(){

        char dateiname[100];
    ifstream eingabe;

        cout << "\n" << "XML-Dateiname:" << endl;
        cin >> dateiname;
        eingabe.open(dateiname);

    if (!eingabe)
    {
        cout << "Ungültige Datei.\n";
        return 0;
    }
    xmlToken = new ClXmlToken;
    if (xmlToken->getToken(eingabe)!=0){
        cout << "XML erfolgreich geladen. \n" << endl;
    }
    eingabe.close();

        cout << "TXT-Dateiname:" << endl;
        cin >> dateiname;
        eingabe.open(dateiname);

    if (!eingabe)
    {
        cout << "Ungültige Datei.\n";
        return 0;
    }
    txtToken = new ClTxtToken;
    if (txtToken->getToken(eingabe)!=0){
        cout << "TXT erfolgreich geladen. \n" << endl;
    }
    return 1;
}

//konvertieren der Datei
void XYZ::konvertieren()
{
        char zieldatei[64] , noise[10];

        cout << "Bitte geben Sie den Namen der gewünschten XML-Ausgabedatei ein:" << endl;
        cin.getline(noise,64,'\n');
        cin.getline(zieldatei,64,'\n');

    ofstream ausgabeDatei;
        ausgabeDatei.open(zieldatei);


    if (!ausgabeDatei)
    {
        cout << "\nFehlerhafte Ausgabedatei!\n";
        return;
    }
    if (ausgabeDatei.tellp() != 0)
        ausgabeDatei.put('\n');

    zustand zustand=istStartTag;
    einsetzen(&ausgabeDatei, &zustand, 0, *xmlToken);

    ausgabeDatei.close();

    cout << "Erfolgreich Konvertiert. Die neue Datei befindet sich im Build-Ordner unter dem angegebenen Namen. \n";

}

//Erstellen von tags
void XYZ::einsetzen(ostream *ausgabeDatei, zustand *zustand, int indent, ClXmlToken pufferXml)
{

    char idPuffer[64];

//Starttag
    ausgabeDatei->put('<');
//Name
    for (int j=0;;j++)
    {
        if (pufferXml.name()[j] == '\0')
            break;
        ausgabeDatei->put(pufferXml.name()[j]);
    }

//Attribute
    if (pufferXml.att.zahlAtt() > 0)
    {

        for (int i=0;i<pufferXml.att.zahlAtt();i++)
        {

            // == xml:id
            if (!strcmp(pufferXml.att.zeigeAttName(i), "xml:id")){
                strcpy(idPuffer,pufferXml.att.zeigeAttWert(i));

                ausgabeDatei->put(' ');
                for (int j=4;;j++)
                {
                    if (pufferXml.att.zeigeAttName(i)[j] == '\0')
                        break;
                    ausgabeDatei->put(pufferXml.att.zeigeAttName(i)[j]);
                }
            }
            // != xml:id
            else{
                ausgabeDatei->put(' ');
                for (int j=0;;j++)
                {
                    if (pufferXml.att.zeigeAttName(i)[j] == '\0')
                        break;
                    ausgabeDatei->put(pufferXml.att.zeigeAttName(i)[j]);
                }
            }

            ausgabeDatei->put('=');
            for (int j=0;;j++)
            {
                if (pufferXml.att.zeigeAttWert(i)[j] == '\0')
                    break;
                ausgabeDatei->put(pufferXml.att.zeigeAttWert(i)[j]);
            }
        }
    }
    ausgabeDatei->put('>');


    //Meta-Tag für Produkt
    if (!strcmp(pufferXml.name(), "infos"))
    {
        ausgabeDatei->put('\n');
        indent += 4;
        for(int i=0, indentA = indent; i<indentA ;i++)
            ausgabeDatei->put(' ');
        ausgabeDatei->put('<');
        ausgabeDatei->put('m');
        ausgabeDatei->put('e');
        ausgabeDatei->put('t');
        ausgabeDatei->put('a');
        ausgabeDatei->put('>');
    }


    //Inhalt wird geladen
    if (!strcmp(pufferXml.name(), "infos"))
        pufferXml.inhalt()[0]= '\0';

        for (int j=0;;j++)
        {
            if (pufferXml.inhalt()[j] == '\0')
                break;
            ausgabeDatei->put(pufferXml.inhalt()[j]);
        }

    //Inhalt wird geschlossen
    if (pufferXml.inhalt()[0] != '\0'){
        ausgabeDatei->put('<');
        ausgabeDatei->put('/');
        for (int j=0;;j++)
        {
            if (pufferXml.name()[j] == '\0')
                break;
            ausgabeDatei->put(pufferXml.name()[j]);
        }
        ausgabeDatei->put('>');
    }


    //Kinder
    if (pufferXml.child()){
        ausgabeDatei->put('\n');
        for(int i=0, indentA = indent+4; i<indentA ;i++){
            ausgabeDatei->put(' ');
        }
        indent += 4;
        einsetzen(ausgabeDatei, zustand, indent, *pufferXml.child());
    }


    if (!strcmp(pufferXml.name(), "infos"))
    {

        //Meta-Tag schließen
        ausgabeDatei->put('\n');
        indent -= 4;
        for(int i=0, indentA = indent; i<indentA ;i++)
            ausgabeDatei->put(' ');
        ausgabeDatei->put('<');
        ausgabeDatei->put('/');
        ausgabeDatei->put('m');
        ausgabeDatei->put('e');
        ausgabeDatei->put('t');
        ausgabeDatei->put('a');
        ausgabeDatei->put('>');
        ausgabeDatei->put('\n');

        //Stock-Tag
        for(int i=0, indentA = indent; i<indentA ;i++)
            ausgabeDatei->put(' ');
        ausgabeDatei->put('<');
        ausgabeDatei->put('s');
        ausgabeDatei->put('t');
        ausgabeDatei->put('o');
        ausgabeDatei->put('c');
        ausgabeDatei->put('k');
        ausgabeDatei->put('>');
        ausgabeDatei->put('\n');
        indent += 4;


        ClTxtToken *pufferTxtToken;
        pufferTxtToken = txtToken;
        //Stock checken
        for(;;)
        {
            if (!strcmp(idPuffer, pufferTxtToken->getId()))
            {
                for(int i=0, indentA = indent; i<indentA ;i++)
                    ausgabeDatei->put(' ');
                ausgabeDatei->put('<');
                ausgabeDatei->put('p');
                ausgabeDatei->put('a');
                ausgabeDatei->put('c');
                ausgabeDatei->put('k');
                ausgabeDatei->put('a');
                ausgabeDatei->put('g');
                ausgabeDatei->put('e');
                ausgabeDatei->put(' ');
                ausgabeDatei->put('p');
                ausgabeDatei->put('l');
                ausgabeDatei->put('a');
                ausgabeDatei->put('c');
                ausgabeDatei->put('e');
                ausgabeDatei->put('=');
                ausgabeDatei->put('"');
                // Place
                for (int j=0;;j++)
                    {
                        if (pufferTxtToken->getPlace()[j] == '\0')
                            break;
                        ausgabeDatei->put(pufferTxtToken->getPlace()[j]);
                    }
                ausgabeDatei->put('"');
                ausgabeDatei->put('>');

                // package place="A1">233</package>
                // Value
                for (int j=0;;j++)
                    {
                        if (pufferTxtToken->getStock()[j] == '\0')
                            break;
                        ausgabeDatei->put(pufferTxtToken->getStock()[j]);
                    }
                ausgabeDatei->put('<');
                ausgabeDatei->put('/');
                ausgabeDatei->put('p');
                ausgabeDatei->put('a');
                ausgabeDatei->put('c');
                ausgabeDatei->put('k');
                ausgabeDatei->put('a');
                ausgabeDatei->put('g');
                ausgabeDatei->put('e');
                ausgabeDatei->put('>');
                ausgabeDatei->put('\n');
            }

            if(!pufferTxtToken->child()){
                break;
            }
            else
                pufferTxtToken = pufferTxtToken->child();

        }

        //Stock schließen
        indent -= 4;
        for(int i=0, indentA = indent; i<indentA ;i++)
            ausgabeDatei->put(' ');
        ausgabeDatei->put('<');
        ausgabeDatei->put('/');
        ausgabeDatei->put('s');
        ausgabeDatei->put('t');
        ausgabeDatei->put('o');
        ausgabeDatei->put('c');
        ausgabeDatei->put('k');
        ausgabeDatei->put('>');
        ausgabeDatei->put('\n');

        //Produkt schließen
        indent -= 4;
        for(int i=0, indentA = indent; i<indentA ;i++)
            ausgabeDatei->put(' ');
        ausgabeDatei->put('<');
        ausgabeDatei->put('/');
        for (int j=0;;j++)
        {
            if (pufferXml.name()[j] == '\0')
                break;
            ausgabeDatei->put(pufferXml.name()[j]);
        }
        ausgabeDatei->put('>');
    }

    //Geschwister
    if (pufferXml.sibling()){
        ausgabeDatei->put('\n');
        for(int i=0, indentA = indent; i<indentA ;i++){
            ausgabeDatei->put(' ');
        }
        einsetzen(ausgabeDatei, zustand, indent, *pufferXml.sibling());
    }

    if (!strcmp(pufferXml.name(), "Mediathek"))
    {
        ausgabeDatei->put('\n');
        ausgabeDatei->put('<');
        ausgabeDatei->put('/');
        ausgabeDatei->put('M');
        ausgabeDatei->put('e');
        ausgabeDatei->put('d');
        ausgabeDatei->put('i');
        ausgabeDatei->put('a');
        ausgabeDatei->put('t');
        ausgabeDatei->put('h');
        ausgabeDatei->put('e');
        ausgabeDatei->put('k');
        ausgabeDatei->put('>');

    }
}
