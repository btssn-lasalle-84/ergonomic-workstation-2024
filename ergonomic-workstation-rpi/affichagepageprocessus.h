#ifndef AFFICHAGEPAGEPROCESSUS_H
#define AFFICHAGEPAGEPROCESSUS_H

#include <QtWidgets>
#include <QVector>

#define NB_BACS_MAX       6
#define REPERTOIRE_IMAGES "images/"

class ProcessusAssemblage;
class Etape;
class Bac;
class DialogueModule;

class AffichagePageProcessus : public QWidget
{
    Q_OBJECT
  private:
    ProcessusAssemblage* processusAssemblage;
    DialogueModule*      dialogueModule;
    Etape*               etape;
    int                  numeroEtapeCourante;
    int                  nbEtapes;
    // GUI
    QStackedWidget*       fenetres;
    QWidget*              page;
    QLabel*               numerotationEtapes;
    QLabel*               nomProcessus;
    QLabel*               chronometre;
    QLabel*               nomOperation;
    QTextBrowser*         commentairesOperation;
    QLabel*               photoOperation;
    QVector<QLabel*>      bacs;
    QVector<QPushButton*> boutonsPageProcessus;
    QPushButton*          boutonEtapeSuivante;
    QPushButton*          boutonAbandon;
    int                   choixBouton;

    /**
     * @enum ActionPageProcessus
     * @brief Définit les actions des boutons sélectionnables dans cette fenêtre
     *
     */
    enum ActionPageProcessus
    {
        ActionSuivant = 0,
        ActionAbandon,
        NbActionsPageProcessus
    };

    void creerConnexionsBoutonsNavigation();

  public:
    explicit AffichagePageProcessus(QStackedWidget*      fenetres,
                                    ProcessusAssemblage* processus,
                                    DialogueModule*      dialogueModule);
    ~AffichagePageProcessus();

  public slots:
    void afficher();
    void afficherEtape();
    void abandonner();
    // déclenchés par l'encodeur du module EC
    void avancerChoix();
    void reculerChoix();
    void validerChoix();

  signals:
    void abandon(QString nomProcessus);
    void fini(QString nomProcessus);
};

#endif // AFFICHAGEPAGEPROCESSUS_H
