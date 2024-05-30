#include "bac.h"
#include <QDebug>

Bac::Bac(int idBac, QString typeDePiece, int nbPieces, QString nomImagePiece) :
    idBac(idBac), typeDePiece(typeDePiece), nbPieces(nbPieces), nomImagePiece(nomImagePiece)
{
    qDebug() << Q_FUNC_INFO << "idBac" << idBac << "typeDePiece" << typeDePiece << "nbPieces"
             << nbPieces << "nomImagePiece" << nomImagePiece;
}

Bac::~Bac()
{
    qDebug() << Q_FUNC_INFO;
}
