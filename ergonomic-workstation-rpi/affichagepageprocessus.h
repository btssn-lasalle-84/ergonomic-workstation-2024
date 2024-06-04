#ifndef AFFICHAGEPAGEPROCESSUS_H
#define AFFICHAGEPAGEPROCESSUS_H

#include <QtWidgets>
#include <QVector>

#define NB_BACS_MAX 6

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
    QStackedWidget* fenetres;
    QWidget*        page;
    QLabel*         numerotationEtapes;
    QLabel*         nomProcessus;
    QLabel*         chronometre;
    QLabel*         nomOperation;
    // @todo transformer le QLabel en QTextBrowser pour commentairesOperation
    QTextBrowser*         commentairesOperation;
    QLabel*               photoOperation;
    QVector<QLabel*>      bacs;
    QVector<QPushButton*> boutonsPageProcessus;
    QPushButton*          boutonEtapeSuivante;
    QPushButton*          boutonAbandon;
    int                   choixBouton;
    QString               cheminRacineProcessusAssemblage;

    /**
     * @enum ActionPageProcessus
     * @brief Définit les actions des boutons sélectionnables dans cette fenêtre
     *
     */
    enum ActionPageProcessus
    {
        // @todo définir les actions des boutons sélectionnables dans cette fenêtre
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
    void etapeSuivante();
    // déclenchés par l'encodeur du module EC
    void avancerChoix();
    void reculerChoix();
    void validerChoix();

  signals:
    void abandon(QString nomProcessus);
};

#endif // AFFICHAGEPAGEPROCESSUS_H
