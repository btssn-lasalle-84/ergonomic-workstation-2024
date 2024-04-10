#include "ihm.h"
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
    QWidget(parent), processusAssemblage(new ProcessusAssemblage(this)),
    cheminRacineProcessusAssemblage(QString(CHEMIN_SERVEUR_NFS) +
                                    QString(RACINE_PROCESSUS_ASSEMBLAGE)),
    fenetres(nullptr)
{
    creerFenetres();
    creerConnexionsBoutonsNavigation();
    afficherFenetrePrincipale();
    qDebug() << Q_FUNC_INFO;
}

IHM::~IHM()
{
    qDebug() << Q_FUNC_INFO;
}

void IHM::creerFenetres()
{
    fenetres                     = new QStackedWidget(this);
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);

    creerFenetreMenu();
    creerFenetreStatistique();
    creerFenetreProcessus();

    layoutPrincipal->addWidget(fenetres);
}

void IHM::creerFenetreMenu()
{
    QVBoxLayout* layoutMenu        = new QVBoxLayout;
    QVBoxLayout* layoutBoutonsMenu = new QVBoxLayout;
    fenetreMenu                    = new QWidget;
    boutonStatistique              = new QPushButton("Statistiques", fenetreMenu);
    boutonDemarrer = new QPushButton("Commencer un processus d'assemblage", fenetreMenu);
    titre          = new QLabel(fenetreMenu);
    version        = new QLabel(fenetreMenu);
    titre->setText(NOM_APPLICATION);
    version->setText(QString("v ") + VERSION_APPLICATION);
    fenetres->addWidget(fenetreMenu);
    layoutMenu->addWidget(titre);
    layoutMenu->addWidget(version);
    layoutBoutonsMenu->addWidget(boutonDemarrer);
    layoutBoutonsMenu->addWidget(boutonStatistique);
    layoutMenu->addLayout(layoutBoutonsMenu);

    fenetreMenu->setLayout(layoutMenu);
}

void IHM::creerFenetreProcessus()
{
    QVBoxLayout* layoutProcessus = new QVBoxLayout;
    fenetreProcessus             = new QWidget;
    boutonRetourMenu1            = new QPushButton("Menu", fenetreProcessus);

    // Lister les processus d'assemblage
    // QDir racineProcessusAssemblage(QDir::currentPath() + RACINE_PROCESSUS_ASSEMBLAGE);
    QDir        racineProcessusAssemblage(cheminRacineProcessusAssemblage);
    QStringList listeProcessusAssemblage;
    qDebug() << Q_FUNC_INFO << "cheminRacineProcessusAssemblage" << cheminRacineProcessusAssemblage;
    foreach(QFileInfo element, racineProcessusAssemblage.entryInfoList())
    {
        if(element.isDir())
        {
            if(element.fileName() != "." && element.fileName() != "..")
            {
                qDebug() << Q_FUNC_INFO << "absoluteFilePath" << element.absoluteFilePath();
                qDebug() << Q_FUNC_INFO << "filePath" << element.filePath();
                qDebug() << Q_FUNC_INFO << "fileName" << element.fileName();
                listeProcessusAssemblage << element.fileName();
            }
        }
    }
    qDebug() << Q_FUNC_INFO << "listeProcessusAssemblage" << listeProcessusAssemblage;

    // @todo à remplacer par un système de QLabel
    fenetreScrollProcessus = new QScrollArea(fenetreProcessus);
    fenetres->addWidget(fenetreProcessus);

    layoutProcessus->addWidget(fenetreScrollProcessus);
    layoutProcessus->addWidget(boutonRetourMenu1);
    fenetreProcessus->setLayout(layoutProcessus);
}

void IHM::creerFenetreStatistique()
{
    QVBoxLayout* layoutStatistique = new QVBoxLayout;
    fenetreStatistique             = new QWidget;
    boutonRetourMenu2              = new QPushButton("Menu", fenetreStatistique);
    fenetreScrollStatistique       = new QScrollArea(fenetreStatistique);
    fenetres->addWidget(fenetreStatistique);
    layoutStatistique->addWidget(fenetreScrollStatistique);
    layoutStatistique->addWidget(boutonRetourMenu2);

    fenetreStatistique->setLayout(layoutStatistique);
}

void IHM::afficherFenetrePrincipale()
{
    setWindowTitle(QString(NOM_APPLICATION) + QString(" 2024 v") + QString(VERSION_APPLICATION));
#ifdef PLEIN_ECRAN_RASPBERRY
    showFullScreen();
#endif
    afficherFenetreMenu();
}

void IHM::creerConnexionsBoutonsNavigation()
{
    connect(boutonDemarrer, SIGNAL(clicked()), this, SLOT(afficherFenetreProcessus()));
    connect(boutonStatistique, SIGNAL(clicked()), this, SLOT(afficherFenetreStatistique()));
    connect(boutonRetourMenu1, SIGNAL(clicked()), this, SLOT(afficherFenetreMenu()));
    connect(boutonRetourMenu2, SIGNAL(clicked()), this, SLOT(afficherFenetreMenu()));
}

void IHM::afficherFenetreMenu()
{
    fenetres->setCurrentIndex(Fenetre::Menu);
}

void IHM::afficherFenetreStatistique()
{
    fenetres->setCurrentIndex(Fenetre::Statistique);
}

void IHM::afficherFenetreProcessus()
{
    fenetres->setCurrentIndex(Fenetre::Processus);
}
