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

int Etape::getNbBacs() const
{
    return bacs.size();
}

QString Etape::getNomImage() const
{
    return nomImage;
}

// int Etape::getBacs() const
//{
//    return bacs.idBac;
//}
