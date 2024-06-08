#ifndef ETAPE_H
#define ETAPE_H

#include <QVector>

class Bac;

class Etape
{
  private:
    int           numero;
    QString       nom;
    QString       nomImage;
    QVector<Bac*> bacs;
    bool          valide;

  public:
    explicit Etape(int numero, QString nom, QString nomImage, QVector<Bac*> bacs);
    ~Etape();

    int           getNumero() const;
    QString       getNom() const;
    QString       getNomImage() const;
    Bac*          getBac(int numeroBac) const;
    int           getNbBacs() const;
    QVector<Bac*> getBacs() const;
};

#endif // ETAPE_H
