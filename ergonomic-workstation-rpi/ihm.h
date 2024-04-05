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

namespace Ui
{
class IHM;
}

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
    void creerFenetreMenu();
    void creerFenetreStatistique();
    void creerFenetreProcessus();

  private:
    Ui::IHM*             ui; //!< association vers la GUI
    ProcessusAssemblage* processusAssemblage;
    QPushButton*         boutonStatistique;
    QPushButton*         boutonDemarrer;
    QLabel*              titre;
    QLabel*              version;
    QStackedWidget*      stackedWidget;
    QWidget*             fenetreMenu;
    QWidget*             fenetreStatistique;
    QWidget*             fenetreProcessus;
    QPushButton*         boutonMenu;
    QScrollArea*         fenetreScrollStatistique;
    QScrollArea*         fenetreScrollProcessus;

  private slots:
    void mettreFenetreMenu();
    void mettreFenetreStatistique();
    void mettreFenetreProcessus();
};

#endif // IHM_H
