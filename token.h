#include "att.h"

class ClXmlToken
{
public:
    ClXmlToken();
    char *name() { return tokenName; }
    ClXmlToken *child() { return tokenChild; }
    ClXmlToken *sibling() { return tokenSibling; }
    char *inhalt() { return tokenInhalt; }

    void druckeToken(int ebene);

    int getToken(ifstream &datei);

    ClattToken att;

private:
    void cleanToken();
    void druckeTokenEbene(int ebene);
    int fillToken(int mode);


    char tokenName[64];
    //Verarbeite Abarbeiten
    ClXmlToken *tokenChild;

    ClXmlToken *tokenParent;

    ClXmlToken *tokenSibling;
    char *tokenInhalt;

    //+ attribute
    // + txt_token
} ;

enum zustand { istStartTag, istEndTag } ;
