#ifndef AFFICHAGEPAGEPROCESSUS_H
#define AFFICHAGEPAGEPROCESSUS_H

#include <QtWidgets>

class AffichagePageProcessus : public QWidget
{
    Q_OBJECT
  private:
    QLabel*      nomModule;
    QPushButton* boutonAbandon;

  public:
    explicit AffichagePageProcessus(QWidget* parent = nullptr);

  public slots:
    void afficher();

  signals:
};

#endif // AFFICHAGEPAGEPROCESSUS_H
