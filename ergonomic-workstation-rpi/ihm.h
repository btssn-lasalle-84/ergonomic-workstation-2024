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
class IHM : public QMainWindow
{
    Q_OBJECT

  public:
    IHM(QWidget* parent = nullptr);
    ~IHM();

  private:
    Ui::IHM*             ui; //!< association vers la GUI
    ProcessusAssemblage* processusAssemblage;
};

#endif // IHM_H
