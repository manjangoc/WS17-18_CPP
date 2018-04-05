#include <iostream>
using namespace std;
#include <fstream>
#include "txttoken.h"
#include "token.h"


class XYZ
{
public:
    XYZ();
    int laden();

    //schreiben
    void konvertieren();

private:
    ClXmlToken *xmlToken;
    ClTxtToken *txtToken;

    void einsetzen(ostream *ausgabeDatei,zustand *zustand, int indent, ClXmlToken pufferXml);
};
