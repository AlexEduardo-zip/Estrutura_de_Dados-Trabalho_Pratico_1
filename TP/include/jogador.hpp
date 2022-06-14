#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include <iostream>

using namespace std;

typedef int TipoChave; // TipoChave é um inteiro

class jogador
{
public:
    jogador();
    jogador(string _nome, int _dinheiro, int _chave);
    string getNome();
    void alteraSaldo(int valorAlteracao);
    int getSaldo();
    void setAposta(int aposta);
    int getAposta();
    void SetChave(TipoChave c);
    TipoChave GetChave();
    void setClassificacao(int i);
    int getClassificacao();
    void setMaiorCarta(int numero);
    int getMaiorCarta();
    void setSegundaMaiorCarta(int numero);
    int getSegundaMaiorCarta();
    void setVaiJogar(bool posORno);
    bool getVaijogar();
    void Imprime();
    int saldo;

private:
    bool vaiJogar = 0;
    int maiorCartaNumero;
    int maiorSegundaCartaNumero;
    char maiorCartaNaipe;
    int classificacao;
    TipoChave chave;
    string nome;
    int aposta;
};

#endif