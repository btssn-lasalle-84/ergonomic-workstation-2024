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

    int     getNumero() const;
    QString getNom() const;
    // @todo ajouter l'accesseur get pour l'attribut nomImage
    // @todo ajouter l'accesseur get pour l'attribut bacs
    int getNbBacs() const;
};

#endif // ETAPE_H
