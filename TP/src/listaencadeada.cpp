#include "listaencadeada.hpp"

TipoCelula::TipoCelula()
{
    item.SetChave(-1);
    prox = NULL;
};

ListaEncadeada::ListaEncadeada()
{
    tamanho = 0;
    primeiro = new TipoCelula();
    ultimo = primeiro;
}
ListaEncadeada::~ListaEncadeada()
{
    Limpa();
    delete primeiro;
}
TipoCelula *ListaEncadeada::Posiciona(int pos, bool antes = false)
{
    TipoCelula *p;
    int i;
    if ((pos > tamanho) || (pos < 0))
        throw "ERRO: Posicao Invalida!";
    // Posiciona na célula anterior a desejada
    p = primeiro;
    for (i = 1; i < pos; i++)
    {
        p = p->prox;
    }
    // vai para a próxima
    // se antes for false
    if (!antes)
        p = p->prox;
    return p;
}
jogador ListaEncadeada::GetItem(int pos)
{
    TipoCelula *p;
    p = Posiciona(pos);
    return p->item;
}
void ListaEncadeada::InsereFinal(jogador item)
{
    TipoCelula *nova;
    nova = new TipoCelula();
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;
}
void ListaEncadeada::InserePosicao(jogador item, int pos)
{
    TipoCelula *p, *nova;
    p = Posiciona(pos, true); // posiciona na célula anterior
    nova = new TipoCelula();
    nova->item = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;
    if (nova->prox == NULL)
        ultimo = nova;
}
jogador ListaEncadeada::RemovePosicao(int pos)
{
    ;
    jogador aux;
    TipoCelula *p, *q;
    if (tamanho == 0)
        throw "ERRO: Lista vazia!";
    // posiciona p na celula anterior à pos
    p = Posiciona(pos, true);
    q = p->prox;
    p->prox = q->prox;
    tamanho--;
    aux = q->item;
    delete q;
    if (p->prox == NULL)
        ultimo = p;
    return aux;
}
void ListaEncadeada::Limpa()
{
    TipoCelula *p;
    p = primeiro->prox;
    while (p != NULL)
    {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
};