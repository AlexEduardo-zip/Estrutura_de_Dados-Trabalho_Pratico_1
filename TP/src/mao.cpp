#include "mao.hpp"

mao::mao()
{
}
mao::mao(carta cartaImaginaria)
{
}
void mao::insereCard(carta cartaAtual) // Insere as cartas Ordenadas
{
    if (cards.GetTamanho() == 0)
    {
        cards.InsereInicio(cartaAtual);
        cards.InserePosicao(cartaAtual, 1);
    }
    else
    {
        int posicaoInsere = 1;
        carta cartaAux = cards.GetItem(posicaoInsere);
        while (((cartaAtual.getNumeroCarta()) > (cartaAux.getNumeroCarta())) & (posicaoInsere != (cards.GetTamanho())))
        {
            posicaoInsere++;
            cartaAux = cards.GetItem(posicaoInsere);
        }
        cards.InserePosicao(cartaAtual, posicaoInsere);
    }
}

int mao::classificacao()
{
    int numeroCartas[5] = {cards.GetItem(1).getNumeroCarta(),
                           cards.GetItem(2).getNumeroCarta(),
                           cards.GetItem(3).getNumeroCarta(), // Atribui os valores das cartas em um vetor estatico
                           cards.GetItem(4).getNumeroCarta(), // afim de facilitar a leitura e evitar a chamada do GetItem.
                           cards.GetItem(5).getNumeroCarta()};

    // testa se as cartas possuem o mesmo naipe
    int ehMesmoNaipe = 1;
    for (int i = 2; i < 6; i++)
    {
        char naipe = cards.GetItem(1).getNaipeCarta();
        if (naipe != cards.GetItem(i).getNaipeCarta())
            ehMesmoNaipe = 0;
    }
    // testa se as cartas formam uma sequencia
    int ehsequencia = 1;
    for (int i = 1; i < 5; i++)
    {
        if (((numeroCartas[0] + (i)) - numeroCartas[i]) != 0)
            ehsequencia = 0;
    }
    if (ehMesmoNaipe)
    {
        // Primeiro Teste
        // 10 ao As do mesmo naipe
        int ehRSF = 1;
        for (int i = 0; i < 5; i++)
        {
            int vetorRSF[5] = {1, 10, 11, 12, 13};
            if (numeroCartas[i] != vetorRSF[i])
                ehRSF = 0;
        }
        if (ehRSF)
        {
            nomeClassificacao = "RSF";
            maiorCarta = numeroCartas[4];
            maiorSegundaCarta = numeroCartas[3];
            return 10;
        }
        // 2 Teste
        // São 5 cartas seguidas do mesmo naipe que não seja do 10 até ao Ás.
        if (ehsequencia)
        {
            nomeClassificacao = "SF";
            maiorCarta = numeroCartas[4];
            maiorSegundaCarta = numeroCartas[3];
            return 9;
        }
    }

    if (!ehsequencia) // Se não é uma sequencia toda vez que encontrar o As, o transforma na Maior Carta
    {
        while (numeroCartas[0] == 1)
        {
            for (int j = 0; j < 4; j++)
            {
                numeroCartas[j] = numeroCartas[j + 1];
            };
            numeroCartas[4] = 14;
        };
    }

    // 3 Teste
    // São 4 cartas de numeros iguais
    if (numeroCartas[2] == numeroCartas[1])
    {
        if (numeroCartas[2] == numeroCartas[3])
        {
            if (numeroCartas[2] == numeroCartas[0] || numeroCartas[2] == numeroCartas[4])
            {
                maiorCarta = numeroCartas[2];
                if (numeroCartas[2] == numeroCartas[0])
                    maiorSegundaCarta = numeroCartas[4];
                else
                    maiorSegundaCarta = numeroCartas[0];
                nomeClassificacao = "FK";
                return 8;
            };
        };
    };

    // Teste 4
    // Uma tripla e um par
    if (numeroCartas[0] == numeroCartas[1])
    {
        if (numeroCartas[1] == numeroCartas[2])
        {
            if (numeroCartas[3] == numeroCartas[4])
            {
                maiorCarta = numeroCartas[0];
                maiorSegundaCarta = numeroCartas[4];
                nomeClassificacao = "FH";
                return 7;
            }
        }
        else if ((numeroCartas[2] == numeroCartas[3]) & (numeroCartas[2] == numeroCartas[4]))
        {
            maiorCarta = numeroCartas[2];
            maiorSegundaCarta = numeroCartas[0];
            nomeClassificacao = "FH";
            return 7;
        }
    };

    // Teste 5
    // Mesmo naipe sem ordem
    if (ehMesmoNaipe)
    {
        maiorCarta = numeroCartas[4];
        maiorSegundaCarta = numeroCartas[3];
        nomeClassificacao = "F";
        return 6;
    }
    // Teste 4
    //  São 5 cartas seguidas sem importar o naipe.
    if (ehsequencia)
    {
        maiorCarta = numeroCartas[4];
        maiorSegundaCarta = numeroCartas[3];
        nomeClassificacao = "S";
        return 5;
    }

    // Teste 3
    // São 3 cartas iguais mais duas cartas diferentes.
    if ((numeroCartas[2] == numeroCartas[1]) || (numeroCartas[2] == numeroCartas[3]))
    {
        if ((numeroCartas[2] == numeroCartas[1]) & (numeroCartas[2] == numeroCartas[3]))
        {
            maiorCarta = numeroCartas[3];
            maiorSegundaCarta = numeroCartas[4];
            nomeClassificacao = "TK";
            return 4;
        }
        else if ((numeroCartas[2] == numeroCartas[0]) || (numeroCartas[2] == numeroCartas[4]))
        {
            maiorCarta = numeroCartas[2];
            if (numeroCartas[2] == numeroCartas[0])
                maiorSegundaCarta = numeroCartas[4];
            else
                maiorSegundaCarta = numeroCartas[1];
            nomeClassificacao = "TK";
            return 4;
        }
    };

    // Teste 2
    // São 2 pares de cartas
    if (cards.GetItem(2).getNumeroCarta() == cards.GetItem(1).getNumeroCarta() || cards.GetItem(2).getNumeroCarta() == cards.GetItem(3).getNumeroCarta())
    {
        if (cards.GetItem(4).getNumeroCarta() == cards.GetItem(3).getNumeroCarta() || cards.GetItem(4).getNumeroCarta() == cards.GetItem(5).getNumeroCarta())
        {
            maiorCarta = numeroCartas[4];
            maiorSegundaCarta = numeroCartas[2];
            nomeClassificacao = "TP";
            return 3;
        }
        else
        {
            // Teste 1
            // É 1 par de cartas
            maiorCarta = numeroCartas[1];
            maiorSegundaCarta = numeroCartas[4];
            nomeClassificacao = "OP";
            return 2;
        }
    }
    if (cards.GetItem(4).getNumeroCarta() == cards.GetItem(3).getNumeroCarta() || cards.GetItem(4).getNumeroCarta() == cards.GetItem(5).getNumeroCarta())
    {
        // Teste 1
        // É 1 par de cartas
        maiorCarta = numeroCartas[3];
        if (numeroCartas[3] == numeroCartas[4])
            maiorSegundaCarta = numeroCartas[2];
        else
            maiorSegundaCarta = numeroCartas[4];
        nomeClassificacao = "OP";
        return 2;
    }
    maiorCarta = numeroCartas[4];
    maiorSegundaCarta = numeroCartas[3];
    nomeClassificacao = "HC";
    return 1;
}