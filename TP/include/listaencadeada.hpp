#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H

#include <string>
#include <iostream>
#include "jogador.hpp"

using namespace std;

class TipoCelula
{
public:
    TipoCelula();

private:
    jogador item;
    TipoCelula *prox;
    friend class ListaEncadeada;
};

class ListaEncadeada
{
public:
    ListaEncadeada();
    ~ListaEncadeada();
    int GetTamanho() { return tamanho; };
    bool Vazia() { return tamanho == 0; };
    jogador GetItem(int pos);
    void InsereFinal(jogador item);
    void InserePosicao(jogador item, int pos);
    jogador RemovePosicao(int pos);
    void Limpa();

private:
    int tamanho;
    TipoCelula *primeiro;
    TipoCelula *ultimo;
    TipoCelula *Posiciona(int pos, bool antes);
};

#endif