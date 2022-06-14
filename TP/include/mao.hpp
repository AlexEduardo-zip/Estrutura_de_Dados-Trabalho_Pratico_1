#ifndef MAO_H
#define MAO_H

#include <string>
#include <iostream>
#include "carta.hpp"
#include "listaencadeadacartas.hpp"

using namespace std;

class mao
{
public:
    mao();
    mao(carta cartaImaginaria);
    int classificacao();
    int maiorCarta = -1;
    int maiorSegundaCarta = -1;
    string nomeClassificacao = "NA";
    void insereCard(carta cartaAtual);

    ListaEncadeadaCartas cards;
};

#endif