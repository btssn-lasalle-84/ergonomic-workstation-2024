#ifndef ETAPE_H
#define ETAPE_H

#include <QVector>

class Bac;

class Etape
{
  private:
    QVector<Bac*> bacs;
    int           numero;
    bool          valide;

  public:
    explicit Etape();
    ~Etape();
};

#endif // ETAPE_H
