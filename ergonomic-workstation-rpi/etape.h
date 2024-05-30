#ifndef ETAPE_H
#define ETAPE_H

#include <QVector>

class Bac;

class Etape
{
  private:
    QString       nom;
    QString       nomImage;
    QVector<Bac*> bacs;
    int           numero;
    bool          valide;

  public:
    explicit Etape(int numero, QString nom, QString nomImage, QVector<Bac*> bacs);
    ~Etape();

    int     getNumero() const;
    QString getNom() const;
};

#endif // ETAPE_H
