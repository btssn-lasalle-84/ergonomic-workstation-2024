#include "etape.h"

Etape::Etape() : numero(1), valide(false)
{
}

Etape::~Etape()
{
}

int Etape::getNumero() const
{
    return numero;
}
