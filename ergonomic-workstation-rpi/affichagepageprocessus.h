#ifndef AFFICHAGEPAGEPROCESSUS_H
#define AFFICHAGEPAGEPROCESSUS_H

#include <QtWidgets>
#include <QVector>

#define NB_BACS_MAX 6

class Etape;
class Choix;

class AffichagePageProcessus : public QWidget
{
    Q_OBJECT
  private:
    QStackedWidget*  fenetres;
    QWidget*         page;
    QLabel*          numerotationEtapes;
    QLabel*          nomProcessus;
    QLabel*          chronometre;
    QLabel*          nomOperation;
    QLabel*          commentairesOperation;
    QLabel*          photoOperation;
    QVector<QLabel*> bacs;
    Choix*           boutonEtapeSuivante;
    Choix*           boutonAbandon;
    Etape*           etape;
    int              nbEtapes;
    int              choixBouton;

    void creerConnexionsBoutonsNavigation();

  public:
    explicit AffichagePageProcessus(QStackedWidget* fenetres,
                                    QString         nomProcessus,
                                    int             nbEtapes,
                                    Etape*          etape);
    ~AffichagePageProcessus();

  public slots:
    void afficher();
    void abandonner();

  signals:
    void abandon(QString nomProcessus);
};

#endif // AFFICHAGEPAGEPROCESSUS_H
