#include "jogador.hpp"

jogador::jogador()
{
    chave = 0;
    nome = "sem nome ainda";
    saldo = -1;
    vaiJogar = 0;
    maiorCartaNumero = -1;
    maiorSegundaCartaNumero = -1;
    classificacao = -1;
    aposta = 0;
}

jogador::jogador(string _nome, int _dinheiro, int _chave)
{
    nome = _nome;
    saldo = _dinheiro;
    chave = _chave;
    vaiJogar = 0;
    maiorCartaNumero = -1;
    maiorSegundaCartaNumero = -1;
    classificacao = -1;
    aposta = 0;
}
void jogador::SetChave(TipoChave c)
{
    chave = c;
}
TipoChave jogador::GetChave()
{
    return chave;
}
void jogador::Imprime()
{
    std::cout << "NOME: " << nome << endl;
    std::cout << "SALDO: " << saldo << endl;
    std::cout << "MAIOR CARTA: " << maiorCartaNumero << endl;
    std::cout << "VALOR DA APOSTA: " << aposta << endl;
}
void jogador::alteraSaldo(int valorAlterado)
{
    this->saldo = saldo + valorAlterado;
}
string jogador::getNome()
{
    return nome;
}
int jogador::getSaldo()
{
    return saldo;
}
void jogador::setAposta(int _aposta)
{
    aposta = _aposta;
}
int jogador::getAposta()
{
    return aposta;
}
void jogador::setClassificacao(int _classificacao)
{
    classificacao = _classificacao;
}
int jogador::getClassificacao()
{
    return classificacao;
}
void jogador::setMaiorCarta(int numero)
{
    maiorCartaNumero = numero;
}
int jogador::getMaiorCarta()
{
    return maiorCartaNumero;
}
void jogador::setSegundaMaiorCarta(int numero)
{
    maiorSegundaCartaNumero = numero;
}
int jogador::getSegundaMaiorCarta()
{
    return maiorSegundaCartaNumero;
}
void jogador::setVaiJogar(bool posORno)
{
    vaiJogar = posORno;
}
bool jogador::getVaijogar()
{
    return vaiJogar;
};