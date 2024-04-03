#ifndef POSTETRAVAIL_H
#define POSTETRAVAIL_H

#include <QWidget>

class PosteTravail : public QWidget
{
    Q_OBJECT
private:
    ProcessusAssemblage* processusAssemblage;
    Operateur* operateur;
public:

    explicit PosteTravail(QWidget *parent = nullptr);

signals:

};

#endif // POSTETRAVAIL_H
