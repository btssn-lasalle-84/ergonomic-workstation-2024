#include "etape.h"
#include <QDebug>

Etape::Etape(int numero, QString nom, QString nomImage, QVector<Bac*> bacs) :
    numero(numero), nom(nom), nomImage(nomImage), bacs(bacs), valide(false)
{
    qDebug() << Q_FUNC_INFO << "numero" << numero << "nom" << nom << "nomImage" << nomImage;
}

Etape::~Etape()
{
    qDebug() << Q_FUNC_INFO;
}

int Etape::getNumero() const
{
    return numero;
}

QString Etape::getNom() const
{
    return nom;
}

QString Etape::getNomImage() const
{
    return nomImage;
}

Bac* Etape::getBac(int numeroBac) const
{
    if(numeroBac >= 0 && numeroBac < bacs.size())
    {
        return bacs[numeroBac];
    }
}

int Etape::getNbBacs() const
{
    return bacs.size();
}

QVector<Bac*> Etape::getBacs() const
{
    return bacs;
}
