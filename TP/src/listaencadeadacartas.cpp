#include "listaencadeadacartas.hpp"

TipoCelulaCartas::TipoCelulaCartas()
{
    item.SetChave(-1);
    prox = NULL;
};

ListaEncadeadaCartas::ListaEncadeadaCartas()
{
    tamanho = 0;
    primeiro = new TipoCelulaCartas();
    ultimo = primeiro;
}
ListaEncadeadaCartas::~ListaEncadeadaCartas()
{
    Limpa();
    delete primeiro;
}
int ListaEncadeadaCartas::GetTamanho()
{
    return tamanho;
}
TipoCelulaCartas *ListaEncadeadaCartas::Posiciona(int pos, bool antes = false)
{
    TipoCelulaCartas *p;
    int i;
    if ((pos > tamanho) || (pos <= 0))
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
carta ListaEncadeadaCartas::GetItem(int pos)
{
    TipoCelulaCartas *p;
    p = Posiciona(pos);
    return p->item;
}
void ListaEncadeadaCartas::InsereInicio(carta item)
{
    TipoCelulaCartas *nova;
    nova = new TipoCelulaCartas();
    nova->item = item;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;
    if (nova->prox == NULL)
        ultimo = nova;
}

void ListaEncadeadaCartas::InserePosicao(carta item, int pos)
{
    TipoCelulaCartas *p, *nova;
    p = Posiciona(pos, true); // posiciona na célula anterior
    nova = new TipoCelulaCartas();
    nova->item = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;
    if (nova->prox == NULL)
        ultimo = nova;
}
carta ListaEncadeadaCartas::RemovePosicao(int pos)
{
    carta aux;
    TipoCelulaCartas *p, *q;
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
void ListaEncadeadaCartas::Limpa()
{
    TipoCelulaCartas *p;
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