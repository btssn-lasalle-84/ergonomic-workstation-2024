#include "affichagepageprocessus.h"
#include "etape.h"
#include "choix.h"
#include <QDebug>

/**
 * @brief Constructeur de la classe AffichagePageProcessus
 * @details Gère l'affichage pour une étape du processus d'assemblage
 * @fn AffichagePageProcessus::AffichagePageProcessus
 * @param fenetres la page à ajouter à fenetres
 * @param nomProcessus le nom du processus d'assemblage
 * @param nbEtapes le nombre d'étapes total pour le processus d'assemblage
 * @param etape l'Etape à afficher
 */
AffichagePageProcessus::AffichagePageProcessus(QStackedWidget* fenetres,
                                               QString         nomProcessus,
                                               int             nbEtapes,
                                               Etape*          etape) :
    QWidget(fenetres),
    fenetres(fenetres), etape(etape), nbEtapes(nbEtapes), choixBouton(0)
{
    qDebug() << Q_FUNC_INFO;
    // ajoute une page
    page = new QWidget(this);
    fenetres->addWidget(page);

    // les widgets
    this->numerotationEtapes =
      new QLabel(QString::number(etape->getNumero()) + QString("/") + QString::number(nbEtapes),
                 this);
    this->nomProcessus          = new QLabel(nomProcessus, this);
    this->chronometre           = new QLabel("00:00", this);
    this->nomOperation          = new QLabel("Opération", this);
    this->commentairesOperation = new QLabel("...", this);
    this->photoOperation        = new QLabel("[photo]", this);
    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        bacs.push_back(new QLabel(QString("Bac ") + QString::number(i + 1), this));
    }
    this->boutonEtapeSuivante = new Choix("->", 0, this);      // choix 0
    this->boutonAbandon       = new Choix("Abandon", 1, this); // choix 1
    this->boutonAbandon->setCouleur(150, 0, 150);
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
}

AffichagePageProcessus::~AffichagePageProcessus()
{
    qDebug() << Q_FUNC_INFO;
}

void AffichagePageProcessus::afficher()
{
    fenetres->setCurrentWidget(page);
}

void AffichagePageProcessus::abandonner()
{
    emit abandon(this->nomProcessus->text());
}

void AffichagePageProcessus::creerConnexionsBoutonsNavigation()
{
    connect(boutonAbandon, SIGNAL(clicked(int)), this, SLOT(abandonner()));
}
