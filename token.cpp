#include <iostream>
using namespace std;
#include <fstream>
#include "token.h"

ClXmlToken::ClXmlToken()
{
    *tokenName='\0';
    tokenChild=NULL;

    tokenParent=NULL;

    tokenSibling=NULL;
    tokenInhalt=new char[1];
    *tokenInhalt='\0';
}


int  ClXmlToken::getToken(ifstream &datei)
{
    int zaehler;
    enum zustand zustand;
    char zeichen;

    char puffer[100];
    ClXmlToken *child;

    cleanToken();

    for (zaehler=0;;)
    {
        datei.get(zeichen);
        if (datei.eof())
        {
            if (*tokenName == '\0' && tokenChild == NULL && tokenInhalt == NULL)
                return fillToken(0);
            return fillToken(1);
        }
        switch(zeichen)
        {
        case '<':
            datei.get(zeichen);
            if (zeichen=='/')
            {
                zustand = istEndTag;
                if (zaehler!=0)
                {
                    puffer[zaehler]='\0';
                    tokenInhalt = new char[zaehler+1];
                    strcpy(tokenInhalt,puffer);
                }
            }
            else
            {
                datei.putback(zeichen);
                if (*tokenName!='\0')
                {
                    datei.putback('<');
                    if (tokenChild==NULL)
                    {
                        tokenChild=new ClXmlToken;
                        if (tokenChild->getToken(datei)==0)
                            return fillToken(0);
                    }
                    else
                    {
                        for (child=tokenChild;;child=child->tokenSibling)
                        {
                            if (child->tokenSibling==NULL)
                            {
                                child->tokenSibling=new ClXmlToken;
                                if (child->tokenSibling->getToken(datei)==0)
                                    return fillToken(0);
                                break;
                            }
                        }
                    }
                }
                else zustand=istStartTag;
            }
            zaehler=0;
            break;

        case '>':
            puffer[zaehler]='\0';
            if (zustand==istEndTag)
            {
                if (strcmp(tokenName,puffer))
                {
                    return fillToken(0);
                }
                return fillToken(1);
            }
            if (zustand==istStartTag)
            {
                att.getAttList(puffer);
                strcpy(tokenName,puffer);
            }

            zaehler=0;
            break;

        case '\n':
            break;
        default:
            puffer[zaehler]=zeichen;
            zaehler++;
            break;
        }
    }
}


int ClXmlToken::fillToken(
        int mode)
{
    if (*tokenName=='\0')
        strcpy(tokenName,"Unbekanntes Element");
    if (tokenInhalt==NULL)
    {
        tokenInhalt=new char[1];
        *tokenInhalt='\0';
    }
    return mode;
}

void ClXmlToken::cleanToken(void)
{
    *tokenName='\0';
    if (tokenChild!=NULL)
    {
        delete tokenChild;
        tokenChild=NULL;
    }
    if (tokenInhalt!=NULL)
    {
        delete tokenInhalt;
        tokenInhalt=NULL;
    }
}

void ClXmlToken::druckeTokenEbene(
        int ebene)
{
    while (ebene > 0)
    {
        ebene = ebene - 1;
    }
}
