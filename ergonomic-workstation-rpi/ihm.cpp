#include "ihm.h"
#include "processusassemblage.h"
#include "affichagepageprocessus.h"
#include "dialoguemodule.h"
#include <QDebug>
#include <QCoreApplication>

/**
 * @file ihm.cpp
 *
 * @brief Définition de la classe IHM
 * @author Gabain AVRIL
 * @version 1.0
 */

/**
 * @brief Constructeur de la classe IHM
 * @fn IHM::IHM
 * @param parent L'adresse de l'objet parent, si nullptr IHM sera la
 * fenêtre principale de l'application
 */
IHM::IHM(QWidget* parent) :
    QWidget(parent), processusAssemblage(new ProcessusAssemblage(this)),
    dialogueModule(new DialogueModule(this)),
    cheminRacineProcessusAssemblage(QCoreApplication::applicationDirPath() +
                                    QString(RACINE_PROCESSUS_ASSEMBLAGE)),
    choixBoutonsFenetreMenu(ActionFenetreMenu::ActionDemarrer),
    choixBoutonsFenetreStatistique(ActionFenetreStatistique::ActionFSMenu),
    choixBoutonsFenetreProcessus(ActionFenetreProcessus::ActionFPMenu), fenetres(nullptr)
{
    qDebug() << Q_FUNC_INFO;
    creerFenetres();
    creerConnexionsBoutonsNavigation();
    creerConnexionsGUI();
    afficherFenetrePrincipale();
    initialiserDialogueModule();
    qDebug() << Q_FUNC_INFO;
}

IHM::~IHM()
{
    dialogueModule->arreter();
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
    // les boutons de cette fenêtre
    QPushButton* boutonDemarrer =
      new QPushButton("Commencer un processus d'assemblage", fenetreMenu);
    boutonsFenetreMenu.push_back(boutonDemarrer);
    boutonDemarrer->setFocus();
    QPushButton* boutonStatistique = new QPushButton("Statistiques", fenetreMenu);
    boutonsFenetreMenu.push_back(boutonStatistique);

    titre   = new QLabel(fenetreMenu);
    version = new QLabel(fenetreMenu);
    titre->setText(NOM_APPLICATION);
    titre->setObjectName("titre");
    titre->setAlignment(Qt::AlignCenter);
    version->setText(QString("v ") + VERSION_APPLICATION);
    version->setObjectName("version");
    version->setAlignment(Qt::AlignCenter);
    titre->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    version->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    fenetres->addWidget(fenetreMenu);
    layoutMenu->addStretch();
    layoutMenu->addWidget(titre);
    layoutMenu->addWidget(version);
    layoutMenu->addStretch();
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
    boutonRetourMenu1->setFocus();
    boutonsFenetreProcessus.push_back(boutonRetourMenu1);
    fenetres->addWidget(fenetreProcessus);
    connexionPosteDeTravail = new QLabel("Poste de travail non connecté", fenetreProcessus);

    // Lister les processus d'assemblage
    // QDir racineProcessusAssemblage(QDir::currentPath() + RACINE_PROCESSUS_ASSEMBLAGE);
    QDir racineProcessusAssemblage(cheminRacineProcessusAssemblage);
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

    layoutProcessus->addWidget(connexionPosteDeTravail);
    layoutProcessus->addSpacing(50);
    QVBoxLayout* layoutBoutonsProcessus = new QVBoxLayout;
    layoutBoutonsProcessus->setAlignment(Qt::AlignCenter);
    int margeCotes    = (qApp->primaryScreen()->availableSize().width() * 0.15);
    int largeurBouton = (qApp->primaryScreen()->availableSize().width() - margeCotes);
    for(int i = 0; i < listeProcessusAssemblage.size(); ++i)
    {
        boutonsFenetreProcessus.push_back(
          new QPushButton(listeProcessusAssemblage.at(i), fenetreProcessus));
        layoutBoutonsProcessus->addWidget(boutonsFenetreProcessus.last());
        // boutonsFenetreProcessus.last()->setStyleSheet("color: #AD956B;");
        boutonsFenetreProcessus.last()->setMinimumWidth(largeurBouton);
        boutonsFenetreProcessus.last()->setMaximumWidth(largeurBouton);
    }

    layoutProcessus->addLayout(layoutBoutonsProcessus);
    layoutProcessus->addStretch();
    layoutProcessus->addWidget(boutonRetourMenu1);
    fenetreProcessus->setLayout(layoutProcessus);
}

void IHM::creerFenetreStatistique()
{
    QVBoxLayout* layoutStatistique = new QVBoxLayout;
    fenetreStatistique             = new QWidget;
    boutonRetourMenu2              = new QPushButton("Menu", fenetreStatistique);
    boutonsFenetreStatistique.push_back(boutonRetourMenu2);
    fenetres->addWidget(fenetreStatistique);
    layoutStatistique->addStretch();
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
    // Pour la fenêtre Fenetre::Menu
    connect(boutonsFenetreMenu[ActionFenetreMenu::ActionDemarrer],
            SIGNAL(clicked()),
            this,
            SLOT(afficherFenetreProcessus()));
    connect(boutonsFenetreMenu[ActionFenetreMenu::ActionStatistique],
            SIGNAL(clicked()),
            this,
            SLOT(afficherFenetreStatistique()));

    // Pour la fenêtre Fenetre::Statistique
    connect(boutonsFenetreStatistique[ActionFenetreStatistique::ActionFSMenu],
            SIGNAL(clicked()),
            this,
            SLOT(afficherFenetreMenu()));

    // Pour la fenêtre Fenetre::Processus
    connect(boutonsFenetreProcessus[ActionFenetreProcessus::ActionFPMenu],
            SIGNAL(clicked()),
            this,
            SLOT(afficherFenetreMenu()));

    // Pour le dialogue avec le module poste de travail
    connect(dialogueModule,
            SIGNAL(moduleConnecte()),
            this,
            SLOT(afficherConnexionPosteDeTravail()));
    connect(dialogueModule,
            SIGNAL(moduleDeconnecte()),
            this,
            SLOT(afficherDeconnexionPosteDeTravail()));
    connect(dialogueModule,
            SIGNAL(erreurOuvertureModule()),
            this,
            SLOT(afficherErreurOuverturePosteDeTravail()));
    connect(dialogueModule,
            SIGNAL(erreurDialogueModule()),
            this,
            SLOT(afficherErreurDialoguePosteDeTravail()));
    creerConnexionEncodeurMenu();
}

void IHM::creerConnexionEncodeurMenu()
{
    connect(dialogueModule, SIGNAL(encodeurDroite()), this, SLOT(avancerChoix()));
    connect(dialogueModule, SIGNAL(encodeurGauche()), this, SLOT(reculerChoix()));
    connect(dialogueModule, SIGNAL(encodeurValidation()), this, SLOT(validerChoix()));
}

void IHM::creerDeconnexionEncodeurMenu()
{
    disconnect(dialogueModule, SIGNAL(encodeurDroite()), this, SLOT(avancerChoix()));
    disconnect(dialogueModule, SIGNAL(encodeurGauche()), this, SLOT(reculerChoix()));
    disconnect(dialogueModule, SIGNAL(encodeurValidation()), this, SLOT(validerChoix()));
}

void IHM::creerConnexionsGUI()
{
    // Pour la GUI
    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(chargerProcessusAssemblage(int)));

    for(int i = 1; i < boutonsFenetreProcessus.size(); ++i)
    {
        signalMapper->setMapping(boutonsFenetreProcessus[i], i - 1);
        connect(boutonsFenetreProcessus[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
    }
}

void IHM::initialiserDialogueModule()
{
    connexionPosteDeTravail->setText("Poste de travail non connecté");
    dialogueModule->demarrer();
}

void IHM::afficherFenetreMenu()
{
    fenetres->setCurrentIndex(Fenetre::Menu);
    qDebug() << Q_FUNC_INFO << "fenetre" << fenetres->indexOf(fenetreMenu);
}

void IHM::afficherFenetreStatistique()
{
    fenetres->setCurrentIndex(Fenetre::Statistique);
    qDebug() << Q_FUNC_INFO << "fenetre" << fenetres->indexOf(fenetreStatistique);
}

void IHM::afficherFenetreProcessus()
{
    fenetres->setCurrentIndex(Fenetre::Processus);
    qDebug() << Q_FUNC_INFO << "fenetre" << fenetres->indexOf(fenetreProcessus);
}

void IHM::chargerProcessusAssemblage(int numeroProcessus)
{
    processusAssemblage->chargerProcessusAssemblage(listeProcessusAssemblage.at(numeroProcessus));
    qDebug() << Q_FUNC_INFO << "numeroProcessus" << numeroProcessus;
    qDebug() << Q_FUNC_INFO << "nomProcessus" << processusAssemblage->getNom();
    qDebug() << Q_FUNC_INFO << "nbEtapes" << processusAssemblage->getNbEtapes();

    if(processusAssemblage->getNbEtapes() > 0)
    {
        creerDeconnexionEncodeurMenu();
        pageProcessus = new AffichagePageProcessus(fenetres, processusAssemblage, dialogueModule);
        connect(pageProcessus,
                SIGNAL(abandon(QString)),
                this,
                SLOT(abandonnerProcessusAssemblage(QString)));
        connect(pageProcessus,
                SIGNAL(fini(QString)),
                this,
                SLOT(terminerProcessusAssemblage(QString)));
        pageProcessus->afficher();
    }
}

void IHM::abandonnerProcessusAssemblage(QString nomProcessus)
{
    qDebug() << Q_FUNC_INFO << "nomProcessus" << nomProcessus;
    disconnect(pageProcessus,
               SIGNAL(abandon(QString)),
               this,
               SLOT(abandonnerProcessusAssemblage(QString)));
    delete pageProcessus;
    // @todo gérer l'abandon d'un processus d'assemblage
    // puis
    creerConnexionEncodeurMenu();
    afficherFenetreProcessus();
}

void IHM::terminerProcessusAssemblage(QString nomProcessus)
{
    disconnect(pageProcessus,
               SIGNAL(fini(QString)),
               this,
               SLOT(terminerProcessusAssemblage(QString)));
    delete pageProcessus;
    // @todo gérer la fin d'un processus d'assemblage
    // puis
    creerConnexionEncodeurMenu();
    afficherFenetreProcessus();
}

void IHM::afficherConnexionPosteDeTravail()
{
    connexionPosteDeTravail->setText("Poste de travail connecté");
}

void IHM::afficherDeconnexionPosteDeTravail()
{
    // @todo Afficher le message de déconnexion
    connexionPosteDeTravail->setText("");
}

void IHM::afficherErreurOuverturePosteDeTravail()
{
    // @todo Afficher le message d'erreur
    connexionPosteDeTravail->setText("");
}

void IHM::afficherErreurDialoguePosteDeTravail()
{
    // @todo Afficher le message d'erreur
    connexionPosteDeTravail->setText("");
}

void IHM::avancerChoix()
{
    int fenetreCourante = fenetres->currentIndex();
    switch(fenetreCourante)
    {
        case Fenetre::Menu:
            choixBoutonsFenetreMenu =
              (choixBoutonsFenetreMenu + 1) % ActionFenetreMenu::NbActionsFenetreMenu;
            boutonsFenetreMenu[choixBoutonsFenetreMenu]->setFocus();
            qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreMenu" << choixBoutonsFenetreMenu;
            break;
        case Fenetre::Statistique:
            // @todo si nouveaux boutons
            break;
        case Fenetre::Processus:
            choixBoutonsFenetreProcessus =
              (choixBoutonsFenetreProcessus + 1) % boutonsFenetreProcessus.size();
            boutonsFenetreProcessus[choixBoutonsFenetreProcessus]->setFocus();
            qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreProcessus"
                     << choixBoutonsFenetreProcessus;
            break;
    }
}

void IHM::reculerChoix()
{
    int fenetreCourante = fenetres->currentIndex();
    switch(fenetreCourante)
    {
        case Fenetre::Menu:
            choixBoutonsFenetreMenu =
              (choixBoutonsFenetreMenu - 1) % ActionFenetreMenu::NbActionsFenetreMenu;
            if(choixBoutonsFenetreMenu == -1)
                choixBoutonsFenetreMenu = ActionFenetreMenu::NbActionsFenetreMenu - 1;
            boutonsFenetreMenu[choixBoutonsFenetreMenu]->setFocus();
            qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreMenu" << choixBoutonsFenetreMenu;
            break;
        case Fenetre::Statistique:
            // @todo si nouveaux boutons
            break;
        case Fenetre::Processus:
            choixBoutonsFenetreProcessus =
              (choixBoutonsFenetreProcessus - 1) % boutonsFenetreProcessus.size();
            if(choixBoutonsFenetreProcessus == -1)
                choixBoutonsFenetreProcessus = boutonsFenetreProcessus.size() - 1;
            boutonsFenetreProcessus[choixBoutonsFenetreProcessus]->setFocus();
            qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreProcessus"
                     << choixBoutonsFenetreProcessus;
            break;
    }
}

void IHM::validerChoix()
{
    int fenetreCourante = fenetres->currentIndex();
    switch(fenetreCourante)
    {
        case Fenetre::Menu:
            qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreMenu" << choixBoutonsFenetreMenu;
            // on simule un clic sur le bouton sélectionné
            boutonsFenetreMenu[choixBoutonsFenetreMenu]->clicked();
            break;
        case Fenetre::Statistique:
            qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreStatistique"
                     << choixBoutonsFenetreStatistique;
            boutonsFenetreStatistique[choixBoutonsFenetreStatistique]->clicked();
            break;
        case Fenetre::Processus:
            qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreProcessus"
                     << choixBoutonsFenetreProcessus;
            boutonsFenetreProcessus[choixBoutonsFenetreProcessus]->clicked();
            break;
    }
}
