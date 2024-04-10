#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHM
 * @author Gabain AVRIL
 * @version 0.1
 */

#include <QtWidgets>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM_APPLICATION "ErgonomicWorkstation"

/**
 * @def VERSION_APPLICATION
 * @brief La version de l'application
 */
#define VERSION_APPLICATION "0.1"

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

class ProcessusAssemblage;

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
    ProcessusAssemblage* processusAssemblage;             //!< association
    QString              cheminRacineProcessusAssemblage; // test
    // Les ressources IHM
    QStackedWidget* fenetres;
    QWidget*        fenetreMenu;
    QWidget*        fenetreStatistique;
    QWidget*        fenetreProcessus;
    QPushButton*    boutonDemarrer;
    QPushButton*    boutonStatistique;
    QPushButton*    boutonRetourMenu1; // Depuis Processus
    QPushButton*    boutonRetourMenu2; // Depuis Statistique
    QLabel*         titre;
    QLabel*         version;
    QScrollArea*    fenetreScrollStatistique;
    QScrollArea*    fenetreScrollProcessus;

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

    void creerFenetres();
    void creerFenetreMenu();
    void creerFenetreProcessus();
    void creerFenetreStatistique();
    void afficherFenetrePrincipale();
    void creerConnexionsBoutonsNavigation();

  private slots:
    void afficherFenetreMenu();
    void afficherFenetreStatistique();
    void afficherFenetreProcessus();
};

#endif // IHM_H
