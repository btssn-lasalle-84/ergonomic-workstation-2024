#ifndef BAC_H
#define BAC_H

#include <QString>

class Bac
{
  private:
    int     idBac;
    QString typeDePiece;
    int     nbPieces;
    QString nomImagePiece;

  public:
    Bac(int idBac, QString typeDePiece, int nbPieces, QString nomImagePiece);
};

#endif // BAC_H
