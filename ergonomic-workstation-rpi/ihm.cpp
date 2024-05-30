#include "ihm.h"
#include "processusassemblage.h"
#include "affichagepageprocessus.h"
#include "dialoguemodule.h"
#include <QDebug>

/**
 * @file ihm.cpp
 *
 * @brief Définition de la classe IHM
 * @author Gabain AVRIL
 * @version 0.2
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
    cheminRacineProcessusAssemblage(QString(CHEMIN_SERVEUR_NFS) +
                                    QString(RACINE_PROCESSUS_ASSEMBLAGE)),
    choixBoutonsFenetreMenu(ActionFenetreMenu::ActionDemarrer), fenetres(nullptr)
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
    connexionPosteDeTravail = new QLabel("Non connecté", fenetreProcessus);

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
        // listeProcessus.push_back(new QPushButton(listeProcessusAssemblage.at(i),
        // fenetreProcessus));
        // layoutProcessus->addWidget(listeProcessus.last());
        listeDeroulanteProcessus->addItem(listeProcessusAssemblage.at(i));
    }

    layoutProcessus->addWidget(connexionPosteDeTravail);
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
    connect(boutonRetourMenu2, SIGNAL(clicked()), this, SLOT(afficherFenetreMenu()));

    // Pour la fenêtre Fenetre::Processus
    connect(boutonRetourMenu1, SIGNAL(clicked()), this, SLOT(afficherFenetreMenu()));

    // Pour le dialogue avec le module poste de travail
    connect(dialogueModule, SIGNAL(encodeurDroite()), this, SLOT(avancerChoix()));
    connect(dialogueModule, SIGNAL(encodeurGauche()), this, SLOT(reculerChoix()));
    connect(dialogueModule, SIGNAL(encodeurValidation()), this, SLOT(validerChoix()));
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
}

void IHM::creerConnexionsGUI()
{
    // Pour la GUI
    connect(listeDeroulanteProcessus,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(chargerProcessusAssemblage(int)));
}

void IHM::initialiserDialogueModule()
{
    connexionPosteDeTravail->setText("Non connecté");
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
    listeDeroulanteProcessus->setCurrentIndex(0);
    fenetres->setCurrentIndex(Fenetre::Processus);
    qDebug() << Q_FUNC_INFO << "fenetre" << fenetres->indexOf(fenetreProcessus);
}

void IHM::chargerProcessusAssemblage(int numeroProcessus)
{
    if(listeDeroulanteProcessus->currentIndex() == 0)
        return;
    processusAssemblage->chargerProcessusAssemblage(listeDeroulanteProcessus->currentText());
    qDebug() << Q_FUNC_INFO << "numeroProcessus" << numeroProcessus;
    qDebug() << Q_FUNC_INFO << "nomProcessus" << processusAssemblage->getNom();
    qDebug() << Q_FUNC_INFO << "nbEtapes" << processusAssemblage->getNbEtapes();

    if(processusAssemblage->getNbEtapes() > 0)
    {
        pageProcessus = new AffichagePageProcessus(fenetres, processusAssemblage, dialogueModule);
        connect(pageProcessus,
                SIGNAL(abandon(QString)),
                this,
                SLOT(abandonnerProcessusAssemblage(QString)));
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
    afficherFenetreProcessus();
}

void IHM::afficherConnexionPosteDeTravail()
{
    // @todo Afficher le message de connexion
    connexionPosteDeTravail->setText("Connecté");
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
    choixBoutonsFenetreMenu =
      (choixBoutonsFenetreMenu + 1) % ActionFenetreMenu::NbActionsFenetreMenu;
    boutonsFenetreMenu[choixBoutonsFenetreMenu]->setFocus();
    qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreMenu" << choixBoutonsFenetreMenu;
}

void IHM::reculerChoix()
{
    choixBoutonsFenetreMenu =
      (choixBoutonsFenetreMenu - 1) % ActionFenetreMenu::NbActionsFenetreMenu;
    if(choixBoutonsFenetreMenu == -1)
        choixBoutonsFenetreMenu = ActionFenetreMenu::NbActionsFenetreMenu - 1;
    boutonsFenetreMenu[choixBoutonsFenetreMenu]->setFocus();
    qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreMenu" << choixBoutonsFenetreMenu;
}

void IHM::validerChoix()
{
    qDebug() << Q_FUNC_INFO << "choixBoutonsFenetreMenu" << choixBoutonsFenetreMenu;
    // on simule un clic sur le bouton sélectionné
    boutonsFenetreMenu[choixBoutonsFenetreMenu]->clicked();
}
