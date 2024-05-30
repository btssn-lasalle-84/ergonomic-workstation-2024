#include "etape.h"

Etape::Etape(int numero, QVector<Bac*> bacs) : numero(numero), bacs(bacs), valide(false)
{
}

Etape::~Etape()
{
}

int Etape::getNumero() const
{
    return numero;
}
