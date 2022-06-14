#ifndef CARTA_H
#define CARTA_H

#include <string>
#include <iostream>

using namespace std;

typedef int TipoChave;

class carta
{
public:
    carta();
    carta(int _numero, char _naipe);
    void setCarta(int _numero, char _naipe);
    void SetChave(int chave);
    int GetChave();
    int getNumeroCarta();
    char getNaipeCarta();

private:
    int number;
    char naipe;
    TipoChave chave;
};

#endif