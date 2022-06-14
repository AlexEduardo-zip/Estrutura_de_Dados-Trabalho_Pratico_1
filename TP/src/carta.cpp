#include "carta.hpp"

carta::carta()
{
    number = -1;
    naipe = 'N';
    chave = 1;
}
carta::carta(int _numero, char _naipe)
{
    number = _numero;
    naipe = _naipe;
}
void carta::setCarta(int _numero, char _naipe)
{
    number = _numero;
    naipe = _naipe;
}
void carta::SetChave(int _chave)
{
    chave = _chave;
}
int carta::GetChave()
{
    return chave;
}
int carta::getNumeroCarta()
{
    return number;
}
char carta::getNaipeCarta()
{
    return naipe;
}