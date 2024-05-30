#include "etape.h"

Etape::Etape(int numero, QString nom, QString nomImage, QVector<Bac*> bacs) :
    numero(numero), nom(""), nomImage(""), bacs(bacs), valide(false)
{
}

Etape::~Etape()
{
}

int Etape::getNumero() const
{
    return numero;
}

QString Etape::getNom() const
{
    return nom;
}
