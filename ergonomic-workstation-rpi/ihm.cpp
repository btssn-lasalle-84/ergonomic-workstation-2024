#include "ihm.h"
#include "ui_ihm.h"
#include "processusassemblage.h"
#include <QDebug>

/**
 * @file ihm.cpp
 *
 * @brief Définition de la classe IHM
 * @author Gabain AVRIL
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe IHM
 * @fn IHM::IHM
 * @param parent L'adresse de l'objet parent, si nullptr IHM sera la
 * fenêtre principale de l'application
 */
IHM::IHM(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHM), processusAssemblage(new ProcessusAssemblage(this))
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);
    setWindowTitle(QString(NOM_APPLICATION) + QString(" 2024 v") + QString(VERSION_APPLICATION));
#ifdef PLEIN_ECRAN_RASPBERRY
    showFullScreen();
// showMaximized();
#endif
}

/**
 * @brief Destructeur de la classe IHM
 * @fn IHM::IHM
 */
IHM::~IHM()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}
