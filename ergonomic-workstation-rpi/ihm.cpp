#include "ihm.h"
#include "processusassemblage.h"
#include "affichagepageprocessus.h"
#include "etape.h"
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
    qDebug() << Q_FUNC_INFO;
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
    fenetres->addWidget(fenetreProcessus);

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

    listeDeroulanteProcessus = new QComboBox(this);
    listeDeroulanteProcessus->addItem("");
    listeProcessus.clear();
    for(int i = 0; i < listeProcessusAssemblage.size(); ++i)
    {
        // @todo à transformer en QLabel
        listeProcessus.push_back(new QPushButton(listeProcessusAssemblage.at(i), fenetreProcessus));
        // layoutProcessus->addWidget(listeProcessus.last());
        listeDeroulanteProcessus->addItem(listeProcessusAssemblage.at(i));
    }

    layoutProcessus->addWidget(listeDeroulanteProcessus); // pour les tests
    layoutProcessus->addWidget(boutonRetourMenu1);
    fenetreProcessus->setLayout(layoutProcessus);
}

void IHM::creerFenetreStatistique()
{
    QVBoxLayout* layoutStatistique = new QVBoxLayout;
    fenetreStatistique             = new QWidget;
    boutonRetourMenu2              = new QPushButton("Menu", fenetreStatistique);
    fenetres->addWidget(fenetreStatistique);
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
    connect(listeDeroulanteProcessus,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(chargerProcessusAssemblage(int)));
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

void IHM::chargerProcessusAssemblage(int numeroProcessus)
{
    qDebug() << Q_FUNC_INFO << "numeroProcessus" << numeroProcessus;
    // Test de l'affichage d'une page
    Etape*                  etape = new Etape;
    AffichagePageProcessus* pageProcessus =
      new AffichagePageProcessus(fenetres, listeDeroulanteProcessus->currentText(), 3, etape);
    connect(pageProcessus,
            SIGNAL(abandon(QString)),
            this,
            SLOT(abandonnerProcessusAssemblage(QString)));
    pageProcessus->afficher();
}

void IHM::abandonnerProcessusAssemblage(QString nomProcessus)
{
    qDebug() << Q_FUNC_INFO << "nomProcessus" << nomProcessus;
    // @todo gérer l'abandon d'un processus d'assemblage
    // puis
    afficherFenetreProcessus();
}
