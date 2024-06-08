#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHM
 * @author Gabain AVRIL
 * @version 1.0
 */

#include <QtWidgets>
#include <QVector>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM_APPLICATION "ErgonomicWorkstation"

/**
 * @def VERSION_APPLICATION
 * @brief La version de l'application
 */
#define VERSION_APPLICATION "1.0"

/**
 * @def PLEIN_ECRAN_RASPBERRY
 * @brief Pour le mode plein écran sur la Raspberry Pi
 */
//#define PLEIN_ECRAN_RASPBERRY

/**
 * @def CHEMIN_SERVEUR_NFS
 * @brief Pour définir le chemin vers le partage NFS
 */
#define CHEMIN_SERVEUR_NFS "."

/**
 * @def RACINE_PROCESSUS_ASSEMBLAGE
 * @brief Pour définir la racine des processus d'assemblage
 */
#define RACINE_PROCESSUS_ASSEMBLAGE "/processus-assemblage"

class Etape;
class ProcessusAssemblage;
class AffichagePageProcessus;
class DialogueModule;

/**
 * @class IHM
 * @brief Déclaration de la classe IHM
 * @details Cette classe gère l'affichage de l'application sur l'écran de la Raspberry Pi
 */
class IHM : public QWidget
{
    Q_OBJECT

  public:
    IHM(QWidget* parent = nullptr);
    ~IHM();

  private:
    ProcessusAssemblage* processusAssemblage; //!< association
    DialogueModule*      dialogueModule;
    QString              cheminRacineProcessusAssemblage;
    int choixBoutonsFenetreMenu; //!< le numéro de boutons sélectionnables par l'encodeur dans la
                                 //!< fenêtre Menu
    int choixBoutonsFenetreStatistique; //!< le numéro de boutons sélectionnables par l'encodeur
                                        //!< dans la fenêtre Statistique
    int choixBoutonsFenetreProcessus; //!< le numéro de boutons sélectionnables par l'encodeur dans
                                      //!< la fenêtre Processus
    AffichagePageProcessus* pageProcessus;
    // Les ressources IHM
    QStackedWidget* fenetres;
    QWidget*        fenetreMenu;
    QWidget*        fenetreStatistique;
    QWidget*        fenetreProcessus;
    QVector<QPushButton*>
      boutonsFenetreMenu; //!< les boutons sélectionnables par l'encodeur dans la fenêtre Menu
    QVector<QPushButton*> boutonsFenetreStatistique;
    QVector<QPushButton*> boutonsFenetreProcessus;
    QPushButton*          boutonRetourMenu1; // Depuis Processus
    QPushButton*          boutonRetourMenu2; // Depuis Statistique
    QLabel*               titre;
    QLabel*               version;
    QLabel*               connexionPosteDeTravail;
    QStringList           listeProcessusAssemblage;
    QComboBox             toto;
    /**
     * @enum Fenetre
     * @brief Définit les différentes fenêtres de l'IHM
     *
     */
    enum Fenetre
    {
        Menu = 0,
        Statistique,
        Processus,
        NbFenetres
    };
    /**
     * @enum ActionFenetreMenu
     * @brief Définit les actions des boutons sélectionnables dans la fenêtre Menu
     *
     */
    enum ActionFenetreMenu
    {
        ActionDemarrer = 0,
        ActionStatistique,
        NbActionsFenetreMenu
    };

    enum ActionFenetreStatistique
    {
        ActionFSMenu = 0,
        NbActionsFenetreStatistique
    };

    enum ActionFenetreProcessus
    {
        ActionFPMenu = 0,
        ActionProcessus
    };

    void creerFenetres();
    void creerFenetreMenu();
    void creerFenetreProcessus();
    void creerFenetreStatistique();
    void afficherFenetrePrincipale();
    void creerConnexionsBoutonsNavigation();
    void creerConnexionEncodeurMenu();
    void creerDeconnexionEncodeurMenu();
    void creerConnexionsGUI();
    void initialiserDialogueModule();

  private slots:
    void afficherFenetreMenu();
    void afficherFenetreStatistique();
    void afficherFenetreProcessus();
    void chargerProcessusAssemblage(int numeroProcessus);
    void abandonnerProcessusAssemblage(QString nomProcessus);
    void terminerProcessusAssemblage(QString QString);
  public slots:
    void afficherConnexionPosteDeTravail();
    void afficherDeconnexionPosteDeTravail();
    void afficherErreurOuverturePosteDeTravail();
    void afficherErreurDialoguePosteDeTravail();
    // déclenchés par l'encodeur du module EC
    void avancerChoix();
    void reculerChoix();
    void validerChoix();

  signals:
};

#endif // IHM_H
