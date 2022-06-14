#include <iostream>
#include <fstream>
#include <string>

#include "jogador.hpp"
#include "listaencadeada.hpp"
#include "carta.hpp"
#include "listaencadeadacartas.hpp"
#include "mao.hpp"

using namespace std;

void Insercao(ListaEncadeada *Listajogadores, int tamanho) // Função de ordenação por inserção
{
    int i, j;
    jogador aux;
    for (i = 2; i < (Listajogadores->GetTamanho() + 1); i++)
    {
        aux = Listajogadores->GetItem(i);
        j = i - 1;
        while ((j >= 1) && (aux.getSaldo() < Listajogadores->GetItem(j).getSaldo()))
        {
            Listajogadores->InserePosicao(Listajogadores->GetItem(j), (j + 1));
            Listajogadores->RemovePosicao(j + 2);
            j--;
        }
        Listajogadores->InserePosicao(aux, (j + 1));
        Listajogadores->RemovePosicao(j + 2);
    }
};
void OrdenaAlfabetica(ListaEncadeada *Listajogadores, int tamanho)
{
    int i, j;
    jogador aux;
    for (i = 2; i < (Listajogadores->GetTamanho() + 1); i++)
    {
        aux = Listajogadores->GetItem(i);
        j = i - 1;
        while ((j >= 1) && (aux.getNome() < Listajogadores->GetItem(j).getNome()))
        {
            Listajogadores->InserePosicao(Listajogadores->GetItem(j), (j + 1));
            Listajogadores->RemovePosicao(j + 2);
            j--;
        }
        Listajogadores->InserePosicao(aux, (j + 1));
        Listajogadores->RemovePosicao(j + 2);
    }
};
int main()
{
    int Rodadas, dinheiroInicial, Jogadas, quantidadeJogadores, Pingo, Aposta, Pote;
    string nomeJogador, classificacaoNome;

    ifstream entrada; // abertura do arquivo de entrada
    entrada.open("entrada.txt");

    ofstream saida; // abertura do arquivo de saida
    saida.open("saida.txt");

    entrada >> Rodadas >> dinheiroInicial; // Atribuição das variaveis a partir do arquivo de entrada

    // Criar lista de jogadores
    ListaEncadeada Listajogadores;
    entrada >> quantidadeJogadores >> Pingo; // atribui quantidade de jogadores e pingo
    Pote = (Pingo * quantidadeJogadores);    // Soma ao pote o valor do pingo de todos os jogadores
    int classificacaoAtual = 0;
    mao maoVencedora;
    for (int i = 1; i < (1 + quantidadeJogadores); i++) // Realiza a primeira rodada
    {
        entrada >> nomeJogador; // lê jogador

        jogador jogadorAtual(nomeJogador, dinheiroInicial, i); // Inicializa o jogador

        entrada >> Aposta; // Lê valor da aposta
        jogadorAtual.setAposta(Aposta);

        mao maoAtual;               // Inicializa a mão do jogador atual
        for (int j = 0; j < 5; j++) // Lê cartas
        {
            int numeroCartaAtual;
            char naipeCartaAtual;
            entrada >> numeroCartaAtual;
            entrada >> naipeCartaAtual;
            carta CartaAtual(numeroCartaAtual, naipeCartaAtual);
            maoAtual.insereCard(CartaAtual); // Insere ordenado
        };
        jogadorAtual.setClassificacao(maoAtual.classificacao());  // Define a classificação da jogada
        if (jogadorAtual.getClassificacao() > classificacaoAtual) // Define a classificação vencedora
        {
            classificacaoAtual = jogadorAtual.getClassificacao();
            maoVencedora.nomeClassificacao = maoAtual.nomeClassificacao;
        }
        jogadorAtual.setMaiorCarta(maoAtual.maiorCarta);
        jogadorAtual.setSegundaMaiorCarta(maoAtual.maiorSegundaCarta);
        Listajogadores.InsereFinal(jogadorAtual); // Insere o jogador na Lista
    };
    OrdenaAlfabetica(&Listajogadores, Listajogadores.GetTamanho()); // Ordena Lista de jogadores em ordem alfabetica
    int vencedores = 0;
    for (int i = 1; i < (1 + quantidadeJogadores); i++)
    {
        jogador jogadorAuxiliar = Listajogadores.GetItem(i);

        jogadorAuxiliar.alteraSaldo(-(Listajogadores.GetItem(i).getAposta())); // Subtrai valor da aposta;
        jogadorAuxiliar.alteraSaldo(-(Pingo));
        Pote += Listajogadores.GetItem(i).getAposta(); // Atribui ao pote o valor da aposta

        if (Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) // Compare mãos dos jogadores da rodada e define vencedores;
        {
            vencedores += 1;
        }
        Listajogadores.InserePosicao(jogadorAuxiliar, i);
        Listajogadores.RemovePosicao(i + 1);
    };

    if (vencedores > 1) // Se mais de um jogador tiver a mesma classificação de jogada
    {
        vencedores = 1;
        jogador vencedor;
        int maiorCartaAux = 0;
        for (int i = 1; i < (1 + quantidadeJogadores); i++) // Definir quem tem a maior carta
        {
            if ((Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) & (Listajogadores.GetItem(i).getMaiorCarta() > maiorCartaAux))
            {
                maiorCartaAux = Listajogadores.GetItem(i).getMaiorCarta();
                vencedor = Listajogadores.GetItem(i);
            }
        }
        for (int i = 1; i < (1 + quantidadeJogadores); i++) // Verfica se 2 ou mais tem a mesma maior carta
        {
            if ((Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) & (Listajogadores.GetItem(i).getMaiorCarta() == maiorCartaAux) & (Listajogadores.GetItem(i).getNome() != vencedor.getNome()))
            {
                vencedores++;
                maiorCartaAux = Listajogadores.GetItem(i).getSegundaMaiorCarta();
                vencedor = Listajogadores.GetItem(i);
            }
        }
        if (vencedores > 1) // Se empatar na maior carta dos jogadores
        {
            vencedores = 1;
            maiorCartaAux = 0;
            for (int i = 1; i < (1 + quantidadeJogadores); i++) // Definir quem tem a segunda maior carta
            {
                if ((Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) & (Listajogadores.GetItem(i).getSegundaMaiorCarta() > maiorCartaAux))
                {
                    maiorCartaAux = Listajogadores.GetItem(i).getSegundaMaiorCarta();
                    vencedor = Listajogadores.GetItem(i);
                }
            }
            for (int i = 1; i < (1 + quantidadeJogadores); i++) // Verfica se 2 ou mais tem a mesma maior carta
            {
                if ((Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) & (Listajogadores.GetItem(i).getSegundaMaiorCarta() == maiorCartaAux) & (Listajogadores.GetItem(i).getNome() != vencedor.getNome()))
                {
                    vencedores++;
                    maiorCartaAux = Listajogadores.GetItem(i).getSegundaMaiorCarta();
                    vencedor = Listajogadores.GetItem(i);
                }
            }
            if (vencedores > 1) // Empatou na segunda maior carta tambem!
            {
                Pote = Pote / vencedores;
                saida << vencedores << " " << Pote << " " << maoVencedora.nomeClassificacao << endl;
                for (int i = 1; i < (1 + quantidadeJogadores); i++)
                {
                    if (Listajogadores.GetItem(i).getSegundaMaiorCarta() == maiorCartaAux)
                    {
                        jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                        jogadorAuxiliar.alteraSaldo(Pote);
                        Listajogadores.InserePosicao(jogadorAuxiliar, i);
                        Listajogadores.RemovePosicao(i + 1);
                        saida << Listajogadores.GetItem(i).getNome() << endl;
                    }
                }
            }
            else // Se um jogador tiver a segunda carta maior
            {
                for (int i = 1; i < (1 + quantidadeJogadores); i++)
                {
                    if (Listajogadores.GetItem(i).getSegundaMaiorCarta() == maiorCartaAux)
                    {
                        jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                        jogadorAuxiliar.alteraSaldo(Pote);                                                  // Soma valor recebido do(s) vencedor(res);
                        saida << vencedores << " " << Pote << " " << maoVencedora.nomeClassificacao << endl // Retorna numero de vencedores, valor recebido e jogada;
                              << Listajogadores.GetItem(i).getNome() << endl;                               // Retorna nome do vencedor
                        Listajogadores.InserePosicao(jogadorAuxiliar, i);
                        Listajogadores.RemovePosicao(i + 1);

                        break;
                    }
                }
            }
        }
        else // Se um jogador tiver a maior carta
        {
            for (int i = 1; i < (1 + quantidadeJogadores); i++)
            {
                if (Listajogadores.GetItem(i).getMaiorCarta() == maiorCartaAux)
                {
                    jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                    jogadorAuxiliar.alteraSaldo(Pote);                                                  // Soma valor recebido do(s) vencedor(res);
                    saida << vencedores << " " << Pote << " " << maoVencedora.nomeClassificacao << endl // Retorna numero de vencedores, valor recebido e jogada;
                          << Listajogadores.GetItem(i).getNome() << endl;                               // Retorna nome do vencedor
                    std::cout << endl;
                    Listajogadores.InserePosicao(jogadorAuxiliar, i);
                    Listajogadores.RemovePosicao(i + 1);
                    break;
                }
            }
        }
    }
    else // Se somente 1 jogador tiver a classificação de jogada vencedora
    {
        for (int i = 1; i < (1 + quantidadeJogadores); i++)
        {
            if (Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual)
            {
                jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                jogadorAuxiliar.alteraSaldo(Pote);                                                  // Soma valor recebido do(s) vencedor(res);
                saida << vencedores << " " << Pote << " " << maoVencedora.nomeClassificacao << endl // Retorna numero de vencedores, valor recebido e jogada;
                      << Listajogadores.GetItem(i).getNome() << endl;
                Listajogadores.InserePosicao(jogadorAuxiliar, i);
                Listajogadores.RemovePosicao(i + 1);
                // Retorna nome do vencedor
                break;
            };
        };
    };

    for (int i = 1; i < Rodadas; i++) // Para o numero de rodadas a partir da segunda faça:
    {
        classificacaoAtual = 0;
        for (int i = 1; i < (1 + quantidadeJogadores); i++) // Limpa lixo das rodadas anteriores
        {
            jogador jogadorAuxiliar = Listajogadores.GetItem(i);
            jogadorAuxiliar.setClassificacao(0);
            jogadorAuxiliar.setVaiJogar(false);
            jogadorAuxiliar.setAposta(0);
            jogadorAuxiliar.setMaiorCarta(-1);
            jogadorAuxiliar.setSegundaMaiorCarta(-1);
            Listajogadores.InserePosicao(jogadorAuxiliar, i);
            Listajogadores.RemovePosicao(i + 1);
        }
        entrada >> Jogadas >> Pingo;
        Pote = (Pingo * quantidadeJogadores);
        bool invalida = false;
        for (int k = 0; k < Jogadas; k++)
        {
            entrada >> nomeJogador;
            for (int i = 1; i < (1 + quantidadeJogadores); i++)
            {

                if (Listajogadores.GetItem(i).getNome() == nomeJogador) // Encontra jogadores da rodada
                {
                    entrada >> Aposta;
                    if (Aposta < 50 || Aposta % 50 != 0) // Verfica se a aposta é valida
                        invalida = true;
                    jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                    jogadorAuxiliar.setAposta(Aposta);

                    mao maoAtual;
                    for (int j = 0; j < 5; j++) // Le cartas
                    {
                        int numeroCartaAtual;
                        char naipeCartaAtual;
                        entrada >> numeroCartaAtual;
                        entrada >> naipeCartaAtual;
                        carta CartaAtual(numeroCartaAtual, naipeCartaAtual);
                        maoAtual.insereCard(CartaAtual);
                    };
                    jogadorAuxiliar.setClassificacao(maoAtual.classificacao());
                    if (jogadorAuxiliar.getClassificacao() > classificacaoAtual)
                    {
                        classificacaoAtual = jogadorAuxiliar.getClassificacao();
                        maoVencedora.nomeClassificacao = maoAtual.nomeClassificacao;
                    }
                    jogadorAuxiliar.setMaiorCarta(maoAtual.maiorCarta);
                    jogadorAuxiliar.setSegundaMaiorCarta(maoAtual.maiorSegundaCarta);
                    jogadorAuxiliar.setVaiJogar(true);
                    Listajogadores.InserePosicao(jogadorAuxiliar, i);
                    Listajogadores.RemovePosicao(i + 1);
                    break;
                };
            };
        };

        if (Pingo < 50 || Pingo % 50 != 0) // Verifica se o valor do pingo é valido
            invalida = true;
        for (int i = 1; i < (1 + quantidadeJogadores); i++)
        {
            if (Listajogadores.GetItem(i).getSaldo() < (Pingo + Listajogadores.GetItem(i).getAposta())) // Verifica se os jogadores possuem dinheiro para o pingo e as apostas
            {
                invalida = true;
                break;
            }
        }
        vencedores = 0;
        if (!invalida) // Se a rodada nao for invalida
        {
            for (int i = 1; i < (1 + quantidadeJogadores); i++)
            {
                if (Listajogadores.GetItem(i).getVaijogar()) // Para os jogadores que participam da rodada
                {
                    if (Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) // Encontra jogadores com a maior classificação da rodada
                        vencedores += 1;
                    jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                    jogadorAuxiliar.alteraSaldo(-(Listajogadores.GetItem(i).getAposta())); // Altera valor do saldo
                    jogadorAuxiliar.alteraSaldo(-(Pingo));
                    Pote += Listajogadores.GetItem(i).getAposta(); // Soma aposta no Pote
                    Listajogadores.InserePosicao(jogadorAuxiliar, i);
                    Listajogadores.RemovePosicao(i + 1);
                }
                else
                {
                    jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                    jogadorAuxiliar.alteraSaldo(-(Pingo)); // Subtrai valor do pingo dos jogadores fora da rodada;
                    Listajogadores.InserePosicao(jogadorAuxiliar, i);
                    Listajogadores.RemovePosicao(i + 1);
                };
            };
            if (vencedores > 1) // Se mais de um jogador tiver a mesma classificação de jogada
            {
                vencedores = 1;
                jogador vencedor;
                int maiorCartaAux = 0;
                for (int i = 1; i < (1 + quantidadeJogadores); i++) // Definir quem tem a maior carta
                {
                    if ((Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) & (Listajogadores.GetItem(i).getMaiorCarta() > maiorCartaAux))
                    {
                        maiorCartaAux = Listajogadores.GetItem(i).getMaiorCarta();
                        vencedor = Listajogadores.GetItem(i);
                    }
                }
                for (int i = 1; i < (1 + quantidadeJogadores); i++) // Verfica se 2 ou mais tem a mesma maior carta
                {
                    if ((Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) & (Listajogadores.GetItem(i).getMaiorCarta() == maiorCartaAux) & (Listajogadores.GetItem(i).getNome() != vencedor.getNome()))
                    {
                        vencedores++;
                        maiorCartaAux = Listajogadores.GetItem(i).getSegundaMaiorCarta();
                        vencedor = Listajogadores.GetItem(i);
                    }
                }
                if (vencedores > 1) // Se empatar na maior carta dos jogadores
                {
                    vencedores = 1;
                    maiorCartaAux = 0;
                    for (int i = 1; i < (1 + quantidadeJogadores); i++) // Definir quem tem a maior carta
                    {
                        if ((Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) & (Listajogadores.GetItem(i).getSegundaMaiorCarta() > maiorCartaAux))
                        {
                            maiorCartaAux = Listajogadores.GetItem(i).getSegundaMaiorCarta();
                            vencedor = Listajogadores.GetItem(i);
                        }
                    }
                    for (int i = 1; i < (1 + quantidadeJogadores); i++) // Verfica se 2 ou mais tem a mesma maior carta
                    {
                        if ((Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual) & (Listajogadores.GetItem(i).getSegundaMaiorCarta() == maiorCartaAux) & (Listajogadores.GetItem(i).getNome() != vencedor.getNome()))
                        {
                            vencedores++;
                            maiorCartaAux = Listajogadores.GetItem(i).getSegundaMaiorCarta();
                            vencedor = Listajogadores.GetItem(i);
                        }
                    }
                    if (vencedores > 1) // Empatou na segunda maior carta tambem!
                    {
                        Pote = Pote / vencedores;
                        saida << vencedores << " " << Pote << " " << maoVencedora.nomeClassificacao << endl;
                        for (int i = 1; i < (1 + quantidadeJogadores); i++)
                        {
                            if (Listajogadores.GetItem(i).getSegundaMaiorCarta() == maiorCartaAux)
                            {
                                jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                                jogadorAuxiliar.alteraSaldo(Pote);
                                Listajogadores.InserePosicao(jogadorAuxiliar, i);
                                Listajogadores.RemovePosicao(i + 1);
                                saida << Listajogadores.GetItem(i).getNome() << endl;
                            }
                        }
                    }
                    else // Se um jogador tiver a segunda carta maior
                    {
                        for (int i = 1; i < (1 + quantidadeJogadores); i++)
                        {
                            if (Listajogadores.GetItem(i).getSegundaMaiorCarta() == maiorCartaAux)
                            {
                                jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                                jogadorAuxiliar.alteraSaldo(Pote);                                                  // Soma valor recebido do(s) vencedor(res);
                                saida << vencedores << " " << Pote << " " << maoVencedora.nomeClassificacao << endl // Retorna numero de vencedores, valor recebido e jogada;
                                      << Listajogadores.GetItem(i).getNome() << endl;                               // Retorna nome do vencedor
                                Listajogadores.InserePosicao(jogadorAuxiliar, i);
                                Listajogadores.RemovePosicao(i + 1);
                                break;
                            }
                        }
                    }
                }
                else if (vencedores == 1) // Se um tiver a carta maior
                {
                    for (int i = 1; i < (1 + quantidadeJogadores); i++)
                    {
                        if (Listajogadores.GetItem(i).getMaiorCarta() == maiorCartaAux)
                        {
                            jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                            jogadorAuxiliar.alteraSaldo(Pote);                                                  // Soma valor recebido do(s) vencedor(res);
                            saida << vencedores << " " << Pote << " " << maoVencedora.nomeClassificacao << endl // Retorna numero de vencedores, valor recebido e jogada;
                                  << Listajogadores.GetItem(i).getNome() << endl;                               // Retorna nome do vencedor
                            Listajogadores.InserePosicao(jogadorAuxiliar, i);
                            Listajogadores.RemovePosicao(i + 1);
                            break;
                        }
                    }
                }
            }
            else if (vencedores == 1) // Se somente 1 tiver a classificação de jogada vencedora
            {
                for (int i = 1; i < (1 + quantidadeJogadores); i++)
                {
                    if (Listajogadores.GetItem(i).getClassificacao() == classificacaoAtual)
                    {
                        jogador jogadorAuxiliar = Listajogadores.GetItem(i);
                        jogadorAuxiliar.alteraSaldo(Pote);                                                  // Soma valor recebido do(s) vencedor(res);
                        saida << vencedores << " " << Pote << " " << maoVencedora.nomeClassificacao << endl // Retorna numero de vencedores, valor recebido e jogada;
                              << Listajogadores.GetItem(i).getNome() << endl;                               // Retorna nome do vencedor
                        Listajogadores.InserePosicao(jogadorAuxiliar, i);
                        Listajogadores.RemovePosicao(i + 1);
                        break;
                    };
                };
            };
        }
        else // Retorna jogada invalida;
        {
            saida << vencedores << " " << 0 << " "
                  << "I" << endl;
        };
    };
    saida << "####" << endl;

    // Ordena em ordem crescente pelo valor do saldo Final
    Insercao(&Listajogadores, Listajogadores.GetTamanho());

    for (int i = quantidadeJogadores; i > 0; i--) // Imprime em ordem decrescente
    {
        saida << Listajogadores.GetItem(i).getNome() << " " << Listajogadores.GetItem(i).getSaldo() << endl; // Retorna nome dos jogadores e saldo final;
    }

    entrada.close(); // fechamento do arquivo de entrada
    saida.close();   // fechamento do arquivo de saida

    return 0;
};