#include "affichagepageprocessus.h"
#include "processusassemblage.h"
#include "etape.h"
#include "bac.h"
#include "dialoguemodule.h"
#include <QDebug>

/**
 * @brief Constructeur de la classe AffichagePageProcessus
 * @details Gère l'affichage pour une étape du processus d'assemblage
 * @fn AffichagePageProcessus::AffichagePageProcessus
 * @param fenetres la page à ajouter à fenetres
 * @param processus le processus d'assemblage
 */
AffichagePageProcessus::AffichagePageProcessus(QStackedWidget*      fenetres,
                                               ProcessusAssemblage* processus,
                                               DialogueModule*      dialogueModule) :
    QWidget(fenetres),
    processusAssemblage(processus), dialogueModule(dialogueModule), etape(nullptr),
    numeroEtapeCourante(0), nbEtapes(processusAssemblage->getNbEtapes()), fenetres(fenetres),
    choixBoutonsPageProcessus(0)
{
    qDebug() << Q_FUNC_INFO;
    // ajoute une page
    page = new QWidget(this);
    fenetres->addWidget(page);
    // les widgets
    this->numerotationEtapes    = new QLabel("", this);
    this->nomProcessus          = new QLabel(processusAssemblage->getNom(), this);
    this->chronometre           = new QLabel("00:00", this);
    this->nomOperation          = new QLabel("", this);
    this->commentairesOperation = new QTextBrowser(this);
    this->photoOperation        = new QLabel("", this);
    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        bacs.push_back(new QLabel(QString("Bac ") + QString::number(i + 1), this));
    }
    for(int i = 0; i < bacs.size(); ++i)
    {
        bacs[i]->setVisible(false);
    }
    this->boutonEtapeSuivante = new QPushButton("Suivant", this); // choix 0
    boutonsPageProcessus.push_back(boutonEtapeSuivante);
    this->boutonAbandon = new QPushButton("Abandon", this); // choix 1
    boutonsPageProcessus.push_back(boutonAbandon);
    creerConnexionsBoutonsNavigation();

    // les layouts
    QVBoxLayout* layoutPage      = new QVBoxLayout;
    QHBoxLayout* layoutHeader    = new QHBoxLayout;
    QHBoxLayout* layoutOperation = new QHBoxLayout;
    QHBoxLayout* layoutContenu   = new QHBoxLayout;
    QHBoxLayout* layoutBacs      = new QHBoxLayout;
    QHBoxLayout* layoutFooter    = new QHBoxLayout;

    // agencement des layouts
    layoutPage->addLayout(layoutHeader);
    layoutPage->addLayout(layoutOperation);
    layoutPage->addLayout(layoutContenu);
    layoutPage->addLayout(layoutBacs);
    layoutPage->addLayout(layoutFooter);

    // personnalisation des layouts
    layoutHeader->setAlignment(Qt::AlignCenter);
    layoutOperation->setAlignment(Qt::AlignCenter);
    layoutContenu->setAlignment(Qt::AlignCenter);
    layoutBacs->setAlignment(Qt::AlignCenter);
    layoutFooter->setAlignment(Qt::AlignCenter);

    // placement des widgets
    layoutHeader->addWidget(this->numerotationEtapes);
    layoutHeader->addStretch();
    layoutHeader->addWidget(this->nomProcessus);
    layoutHeader->addStretch();
    layoutHeader->addWidget(this->chronometre);
    layoutOperation->addWidget(this->nomOperation);
    layoutContenu->addWidget(this->commentairesOperation);
    layoutContenu->addWidget(this->photoOperation);
    layoutBacs->addStretch();
    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        layoutBacs->addWidget(bacs[i]);
        layoutBacs->addStretch();
    }
    layoutFooter->addWidget(this->boutonAbandon);
    layoutFooter->addStretch();
    layoutFooter->addWidget(this->boutonEtapeSuivante);

    // fixe le layout
    page->setLayout(layoutPage);

    afficherEtape();
}

AffichagePageProcessus::~AffichagePageProcessus()
{
    qDebug() << Q_FUNC_INFO;
}

void AffichagePageProcessus::afficher()
{
    fenetres->setCurrentWidget(page);
}

void AffichagePageProcessus::afficherEtape()
{
    if((numeroEtapeCourante + 1) == nbEtapes)
    {
        this->boutonEtapeSuivante->setText("Terminer");
    }
    else if(numeroEtapeCourante == nbEtapes)
    {
        emit fini(this->nomProcessus->text());
        return;
    }
    // récupère l'étape courante
    etape = processusAssemblage->getEtapes().at(numeroEtapeCourante);

    // et l'affiche
    this->numerotationEtapes->setText(QString::number(etape->getNumero()) + QString("/") +
                                      QString::number(nbEtapes));
    this->nomOperation->setText(etape->getNom());
    QString fichierHTML = processusAssemblage->getChemin() + QString("etape") +
                          QString::number(etape->getNumero()) + QString(".html");
    if(QFileInfo::exists(fichierHTML))
    {
        this->commentairesOperation->setSource(fichierHTML);
    }
    this->photoOperation->setPixmap(QPixmap(processusAssemblage->getChemin() +
                                            QString(REPERTOIRE_IMAGES) + etape->getNomImage()));
    for(int i = 0; i < etape->getNbBacs(); ++i)
    {
        bacs[i]->setVisible(true);
    }

    if((numeroEtapeCourante + 1) <= nbEtapes)
    {
        ++numeroEtapeCourante;
    }
}

void AffichagePageProcessus::abandonner()
{
    emit abandon(this->nomProcessus->text());
}

void AffichagePageProcessus::creerConnexionsBoutonsNavigation()
{
    connect(dialogueModule, SIGNAL(encodeurDroite()), this, SLOT(avancerChoix()));
    connect(dialogueModule, SIGNAL(encodeurGauche()), this, SLOT(reculerChoix()));
    connect(dialogueModule, SIGNAL(encodeurValidation()), this, SLOT(validerChoix()));
    connect(boutonsPageProcessus[ActionPageProcessus::ActionSuivant],
            SIGNAL(clicked()),
            this,
            SLOT(afficherEtape()));
    connect(boutonsPageProcessus[ActionPageProcessus::ActionAbandon],
            SIGNAL(clicked()),
            this,
            SLOT(abandonner()));
}

void AffichagePageProcessus::avancerChoix()
{
    choixBoutonsPageProcessus =
      (choixBoutonsPageProcessus + 1) % ActionPageProcessus::NbActionsPageProcessus;
    boutonsPageProcessus[choixBoutonsPageProcessus]->setFocus();
    qDebug() << Q_FUNC_INFO << "choixBouton" << choixBoutonsPageProcessus;
}

void AffichagePageProcessus::reculerChoix()
{
    choixBoutonsPageProcessus =
      (choixBoutonsPageProcessus - 1) % ActionPageProcessus::NbActionsPageProcessus;
    if(choixBoutonsPageProcessus == -1)
        choixBoutonsPageProcessus = ActionPageProcessus::NbActionsPageProcessus - 1;
    boutonsPageProcessus[choixBoutonsPageProcessus]->setFocus();
    qDebug() << Q_FUNC_INFO << "choixBouton" << choixBoutonsPageProcessus;
}

void AffichagePageProcessus::validerChoix()
{
    qDebug() << Q_FUNC_INFO << "choixBouton" << choixBoutonsPageProcessus;
    // @todo simuler un clic sur le bouton sélectionné pour déclencher le slot correspondant
    boutonsPageProcessus[choixBoutonsPageProcessus]->clicked();
}
