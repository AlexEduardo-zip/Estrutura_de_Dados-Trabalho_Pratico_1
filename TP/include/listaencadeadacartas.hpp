#ifndef LISTAENCADEDACARTAS_H
#define LISTAENCADEDACARTAS_H

#include <string>
#include <iostream>
#include "carta.hpp"

using namespace std;

class TipoCelulaCartas
{
public:
    TipoCelulaCartas();

private:
    carta item;
    TipoCelulaCartas *prox;
    friend class ListaEncadeadaCartas;
};

class ListaEncadeadaCartas
{
public:
    ListaEncadeadaCartas();
    ~ListaEncadeadaCartas();
    int GetTamanho();
    carta GetItem(int pos);
    void InsereInicio(carta item);
    void InserePosicao(carta item, int pos);
    carta RemovePosicao(int pos);
    void Limpa();

private:
    int tamanho;
    TipoCelulaCartas *primeiro;
    TipoCelulaCartas *ultimo;
    TipoCelulaCartas *Posiciona(int pos, bool antes);
};

#endif