#ifndef AFFICHAGEPAGEPROCESSUS_H
#define AFFICHAGEPAGEPROCESSUS_H

#include <QtWidgets>

class AffichagePageProcessus : public QWidget
{
    Q_OBJECT
  private:
    QWidget*        premiereFenetre;
    QLabel*         nomModule;
    QLabel*         operations;
    QLabel*         photoExpliquative;
    QPushButton*    boutonAbandon;
    QStackedWidget* etapes;
    int             numeroEtape;
    int             numeroEtapeTotal;

    //@TODO mettre un chronomètre
    //@TODO rendre des labels clickable pour changer d'étape

  public:
    explicit AffichagePageProcessus(QWidget* parent = nullptr);
    ~AffichagePageProcessus();
  public slots:
    void afficher();

  signals:
};

#endif // AFFICHAGEPAGEPROCESSUS_H
