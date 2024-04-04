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
IHM::IHM(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;
    setWindowTitle(QString(NOM_APPLICATION) + QString(" 2024 v") + QString(VERSION_APPLICATION));
    QVBoxLayout*    layoutPrincipal = new QVBoxLayout(this);
    QStackedWidget* stackedWidget   = new QStackedWidget;
    creerFenetreMenu();
    creerFenetreStatistique();
    creerFenetreProcessus();
    layoutPrincipal->addWidget(stackedWidget);

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
    delete fenetreMenu;
    delete fenetreStatistique;
    delete fenetreProcessus;
    delete stackedWidget;
    qDebug() << Q_FUNC_INFO;
}

void IHM::creerFenetreMenu()
{
    QVBoxLayout* layoutMenu = new QVBoxLayout;
    fenetreMenu             = new QWidget;
    boutonStatistique       = new QPushButton("Statistique", this);
    boutonDemarrer          = new QPushButton("Commencer un processus d'assemblage", this);
    titre                   = new QLabel(this);
    version                 = new QLabel(this);
    titre->setText("Ergonomic Workstation");
    version->setText("v 0.1");
    connect(boutonDemarrer, SIGNAL(clicked()), this, SLOT(mettreFenetreProcessus()));
    connect(boutonStatistique, SIGNAL(clicked()), this, SLOT(mettreFenetreStatistique()));
    stackedWidget->addWidget(fenetreMenu);
    layoutMenu->addWidget(boutonStatistique);
    layoutMenu->addWidget(boutonDemarrer);
    layoutMenu->addWidget(titre);
    layoutMenu->addWidget(version);
}

void IHM::creerFenetreStatistique()
{
    QWidget* fenetreStatistique = new QWidget;
    stackedWidget->addWidget(fenetreStatistique);
}

void IHM::creerFenetreProcessus()
{
    QWidget* fenetreProcessus = new QWidget;
    stackedWidget->addWidget(fenetreProcessus);
}

void IHM::mettreFenetreMenu()
{
    stackedWidget->setCurrentWidget(fenetreMenu);
}

void IHM::mettreFenetreStatistique()
{
    stackedWidget->setCurrentWidget(fenetreStatistique);
}

void IHM::mettreFenetreProcessus()
{
    stackedWidget->setCurrentWidget(fenetreProcessus);
}
