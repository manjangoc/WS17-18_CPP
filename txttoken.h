class ClTxtToken
{
public:

    char *getId() { return id; }
    char *getPlace() { return place; }
    char *getStock() { return stock; }

    ClTxtToken *child() { return tokenChild; }

    ClTxtToken();
    int getToken(ifstream &datei);
    void druckeToken();


private:

    char id[64];
    char place[64];
    char stock[64];

    ClTxtToken *tokenChild;
};

enum txtZustand { zId, zPlace, zStock, zNoise } ;
