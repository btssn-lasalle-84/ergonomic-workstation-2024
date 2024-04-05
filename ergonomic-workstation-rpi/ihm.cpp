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
    QWidget(parent), ui(new Ui::IHM), stackedWidget(new QStackedWidget),
    processusAssemblage(new ProcessusAssemblage(this))
{
    setWindowTitle(QString(NOM_APPLICATION) + QString(" 2024 v") + QString(VERSION_APPLICATION));
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    creerFenetreMenu();
    creerFenetreStatistique();
    creerFenetreProcessus();
    layoutPrincipal->addWidget(stackedWidget);
    qDebug() << Q_FUNC_INFO;
#ifdef PLEIN_ECRAN_RASPBERRY
    showFullScreen();
#endif
}

IHM::~IHM()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

void IHM::creerFenetreMenu()
{
    QVBoxLayout* layoutMenu = new QVBoxLayout;
    fenetreMenu             = new QWidget;
    boutonStatistique       = new QPushButton("Statistique", fenetreMenu);
    boutonDemarrer          = new QPushButton("Commencer un processus d'assemblage", fenetreMenu);
    titre                   = new QLabel(fenetreMenu);
    version                 = new QLabel(fenetreMenu);
    titre->setText("Ergonomic Workstation");
    version->setText("v 0.1");
    stackedWidget->addWidget(fenetreMenu);
    layoutMenu->addWidget(titre);
    layoutMenu->addWidget(version);
    layoutMenu->addWidget(boutonDemarrer);
    layoutMenu->addWidget(boutonStatistique);
    connect(boutonDemarrer, SIGNAL(clicked()), this, SLOT(mettreFenetreProcessus()));
    connect(boutonStatistique, SIGNAL(clicked()), this, SLOT(mettreFenetreStatistique()));
    fenetreMenu->setLayout(layoutMenu);
}

void IHM::creerFenetreStatistique()
{
    QVBoxLayout* layoutStatistique = new QVBoxLayout;
    fenetreStatistique             = new QWidget;
    boutonMenu                     = new QPushButton("Menu", fenetreStatistique);
    fenetreScrollStatistique       = new QScrollArea(fenetreStatistique);
    stackedWidget->addWidget(fenetreStatistique);
    layoutStatistique->addWidget(fenetreScrollStatistique);
    layoutStatistique->addWidget(boutonMenu);
    connect(boutonMenu, SIGNAL(clicked()), this, SLOT(mettreFenetreMenu()));
    fenetreStatistique->setLayout(layoutStatistique);
}

void IHM::creerFenetreProcessus()
{
    QVBoxLayout* layoutProcessus = new QVBoxLayout;
    fenetreProcessus             = new QWidget;
    boutonMenu                   = new QPushButton("Menu", fenetreProcessus);
    fenetreScrollProcessus       = new QScrollArea(fenetreProcessus);
    stackedWidget->addWidget(fenetreProcessus);
    layoutProcessus->addWidget(fenetreScrollProcessus);
    layoutProcessus->addWidget(boutonMenu);
    connect(boutonMenu, SIGNAL(clicked()), this, SLOT(mettreFenetreMenu()));
    fenetreProcessus->setLayout(layoutProcessus);
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
