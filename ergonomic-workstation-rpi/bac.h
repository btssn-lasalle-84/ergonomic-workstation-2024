#ifndef BAC_H
#define BAC_H

#include <QWidget>

class Bac : public QWidget
{
    Q_OBJECT
private:
    explicit Bac(QWidget *parent = nullptr);
    QString typeDePiece;
    int idBac;
public:
    Bac::Bac();

signals:

};

#endif // BAC_H
