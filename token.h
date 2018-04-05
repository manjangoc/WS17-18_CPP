class ClattToken {
private:
int anzahlAtt;
char *attName[10];
char *attValue[10];
public:
int getAttList(char *eingabe);
char *zeigeAttName(int id) {return attName[id];}
char *zeigeAttWert(int id) {return attValue[id];}
int zahlAtt() {return anzahlAtt;}
};
class ClToken {
private:
void cleanToken();
void druckeTokenEbene(int ebene);
int fillToken(int mode);
char tokenName[64];
   ClToken *tokenChild;
   ClToken *tokenSibling;
char *tokenInhalt;
public:
ClToken();
char *name() { return tokenName; }
   ClToken *child() { return tokenChild; }
char *inhalt() { return tokenInhalt; }
void druckeToken(int ebene);
int getToken(ifstream &datei);
   ClattToken att;
};
enum zustand {istStartTag, istEndTag, zwischenTags, inNamen, erwarteAttributWert, verarbeiteAttributWert, erwarteAttributNamen};
