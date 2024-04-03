#ifndef OPERATEUR_H
#define OPERATEUR_H

#include <QWidget>

class Operateur : public QWidget
{
    Q_OBJECT
private:
    int id;
    QString nom;
    QString prenom;
public:
    explicit Operateur(QWidget *parent = nullptr);

signals:

};

#endif // OPERATEUR_H
