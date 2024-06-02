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
    choixBouton(0)
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
    this->commentairesOperation = new QLabel("", this);
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

    // récupère l'étape courante
    etape = processusAssemblage->getEtapes().at(numeroEtapeCourante);
    // et l'affiche
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
    // @todo mettre à jour les widgets de la page pour l'affichage de l'étape en cours
    // exemple :
    this->numerotationEtapes->setText(QString::number(etape->getNumero()) + QString("/") +
                                      QString::number(nbEtapes));
    this->nomOperation->setText(etape->getNom());
    this->commentairesOperation->setText("...");
    this->photoOperation->setText("[photo]");
    for(int i = 0; i < etape->getNbBacs(); ++i)
    {
        bacs[i]->setVisible(true);
    }
}

void AffichagePageProcessus::abandonner()
{
    emit abandon(this->nomProcessus->text());
}

void AffichagePageProcessus::creerConnexionsBoutonsNavigation()
{
    // @todo pour les boutons boutonsPageProcessus
    connect(boutonAbandon, SIGNAL(clicked()), this, SLOT(abandonner()));
}

void AffichagePageProcessus::avancerChoix()
{
    // @todo choixBouton suivant
    qDebug() << Q_FUNC_INFO << "choixBouton" << choixBouton;
}

void AffichagePageProcessus::reculerChoix()
{
    // @todo choixBouton précédent
    qDebug() << Q_FUNC_INFO << "choixBouton" << choixBouton;
}

void AffichagePageProcessus::validerChoix()
{
    qDebug() << Q_FUNC_INFO << "choixBouton" << choixBouton;
    // @todo simuler un clic sur le bouton sélectionné pour déclencher le slot correspondant
}
