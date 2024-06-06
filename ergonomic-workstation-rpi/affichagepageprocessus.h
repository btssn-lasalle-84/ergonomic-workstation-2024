#ifndef AFFICHAGEPAGEPROCESSUS_H
#define AFFICHAGEPAGEPROCESSUS_H

#include <QtWidgets>
#include <QVector>

#define NB_BACS_MAX       8
#define REPERTOIRE_IMAGES "images/"

#define HAUTEUR_PHOTO_OPERATION 400
#define LARGEUR_IMAGE_OPERATION 400
#define HAUTEUR_IMAGE_COMPOSANT 50
#define LARGEUR_IMAGE_COMPOSANT 50

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
    int                   choixBoutonsPageProcessus;
    QVector<QVBoxLayout*> layoutsBacs;
    QVector<QFrame*>      encadrementsBacs;
    QVector<QLabel*>      numerosBacs;
    QVector<QLabel*>      piecesBacs;
    QVector<QLabel*>      nbPiecesBacs;
    QVector<QLabel*>      imagesBacs;

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
    void creerConnexionEncodeur();
    void creerDeconnexionEncodeur();
    void creerBacs();
    void cacherBacs();

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
