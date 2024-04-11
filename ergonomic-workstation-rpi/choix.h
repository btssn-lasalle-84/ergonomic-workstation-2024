#ifndef CHOIX_H
#define CHOIX_H

#include <QtWidgets>

class Choix : public QLabel
{
    Q_OBJECT

  private:
    QString nom;
    int     numero;
    QString couleur;

  public:
    Choix(QString nom, int numero = 0, QWidget* parent = 0);

    void setCouleur(QString couleur);
    void setCouleur(int r, int g, int b);
    void setCouleur(QColor couleur);

    void mousePressEvent(QMouseEvent* event);

  private slots:

  signals:
    void clicked(int);
};

#endif
