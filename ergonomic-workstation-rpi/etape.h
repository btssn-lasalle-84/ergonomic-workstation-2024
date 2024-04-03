#ifndef ETAPE_H
#define ETAPE_H

#include <QWidget>

class Etape : public QWidget
{
    Q_OBJECT
private :
    Bac* bac;
    int numero;
    bool valide;
public:
    explicit Etape(QWidget *parent = nullptr);
    Etape::Etape();

signals:

};

#endif // ETAPE_H
