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
    ~Bac();
    int     getIdBac() const;
    QString getTypeDePiece() const;
    int     getNbPieces() const;
    QString getNomImagePiece() const;
};

#endif // BAC_H
