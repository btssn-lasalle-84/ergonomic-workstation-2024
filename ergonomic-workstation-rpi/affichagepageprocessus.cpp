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
    choixBoutonsPageProcessus(ActionPageProcessus::ActionSuivant)
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
    creerBacs();
    this->boutonEtapeSuivante = new QPushButton("Suivant", this); // choix 0
    boutonsPageProcessus.push_back(boutonEtapeSuivante);
    this->boutonEtapeSuivante->setFocus();
    this->boutonAbandon = new QPushButton("Abandon", this); // choix 1
    boutonsPageProcessus.push_back(boutonAbandon);

    creerConnexionsBoutonsNavigation();
    creerConnexionEncodeur();

    // les layouts
    QVBoxLayout* layoutPage      = new QVBoxLayout;
    QHBoxLayout* layoutHeader    = new QHBoxLayout;
    QHBoxLayout* layoutOperation = new QHBoxLayout;
    QHBoxLayout* layoutContenu   = new QHBoxLayout;
    QHBoxLayout* layoutBacs      = new QHBoxLayout;
    QHBoxLayout* layoutFooter    = new QHBoxLayout;

    // agencement des layouts
    layoutPage->addLayout(layoutHeader);
    layoutPage->addLayout(layoutContenu);
    layoutPage->addLayout(layoutOperation);
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
        layoutBacs->addWidget(encadrementsBacs[i]);
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
    creerDeconnexionEncodeur();
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

    // @todo envoyer l'étape au poste de travail

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
    this->photoOperation->setPixmap(
      QPixmap(processusAssemblage->getChemin() + QString(REPERTOIRE_IMAGES) + etape->getNomImage())
        .scaled(QSize(250, 600), Qt::KeepAspectRatio));
    cacherBacs();
    for(int i = 0; i < etape->getNbBacs(); ++i)
    {
        int numeroBac = etape->getBac(i)->getIdBac();
        encadrementsBacs[numeroBac - 1]->setVisible(true);
        numerosBacs[numeroBac - 1]->setStyleSheet("color: #11b518;");
        piecesBacs[numeroBac - 1]->setText(etape->getBac(i)->getTypeDePiece());
        nbPiecesBacs[numeroBac - 1]->setText("x" +
                                             QString::number(etape->getBac(i)->getNbPieces()));
        imagesBacs[numeroBac - 1]->setPixmap(QPixmap(processusAssemblage->getChemin() +
                                                     QString(REPERTOIRE_IMAGES) +
                                                     etape->getBac(i)->getNomImagePiece())
                                               .scaled(QSize(50, 50), Qt::KeepAspectRatio));
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
    connect(boutonsPageProcessus[ActionPageProcessus::ActionSuivant],
            SIGNAL(clicked()),
            this,
            SLOT(afficherEtape()));
    connect(boutonsPageProcessus[ActionPageProcessus::ActionAbandon],
            SIGNAL(clicked()),
            this,
            SLOT(abandonner()));
}

void AffichagePageProcessus::creerConnexionEncodeur()
{
    connect(dialogueModule, SIGNAL(encodeurDroite()), this, SLOT(avancerChoix()));
    connect(dialogueModule, SIGNAL(encodeurGauche()), this, SLOT(reculerChoix()));
    connect(dialogueModule, SIGNAL(encodeurValidation()), this, SLOT(validerChoix()));
}

void AffichagePageProcessus::creerDeconnexionEncodeur()
{
    disconnect(dialogueModule, SIGNAL(encodeurDroite()), this, SLOT(avancerChoix()));
    disconnect(dialogueModule, SIGNAL(encodeurGauche()), this, SLOT(reculerChoix()));
    disconnect(dialogueModule, SIGNAL(encodeurValidation()), this, SLOT(validerChoix()));
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

void AffichagePageProcessus::creerBacs()
{
    // les QFrame pour les bacs
    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        QFrame* frame = new QFrame(this);
        frame->setObjectName(QString("bac") + QString::number(i + 1));
        encadrementsBacs.push_back(frame);
    }

    // les QLabel pour les bacs
    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        numerosBacs.push_back(
          new QLabel(QString("Bac ") + QString::number(i + 1), encadrementsBacs[i]));
    }

    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        piecesBacs.push_back(new QLabel(QString("") + QString::number(i + 1), encadrementsBacs[i]));
    }

    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        nbPiecesBacs.push_back(
          new QLabel(QString("") + QString::number(i + 1), encadrementsBacs[i]));
    }

    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        imagesBacs.push_back(new QLabel(QString("") + QString::number(i + 1), encadrementsBacs[i]));
    }

    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        numerosBacs[i]->setAlignment(Qt::AlignCenter);
        piecesBacs[i]->setAlignment(Qt::AlignCenter);
        nbPiecesBacs[i]->setAlignment(Qt::AlignCenter);
        imagesBacs[i]->setAlignment(Qt::AlignCenter);
    }

    // les QVBoxLayout pour les bacs
    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        QVBoxLayout* layoutBac = new QVBoxLayout;
        layoutBac->addWidget(numerosBacs[i]);
        layoutBac->addWidget(piecesBacs[i]);
        layoutBac->addWidget(nbPiecesBacs[i]);
        layoutBac->addWidget(imagesBacs[i]);
        encadrementsBacs[i]->setLayout(layoutBac);
        layoutsBacs.push_back(layoutBac);
    }

    cacherBacs();
}

void AffichagePageProcessus::cacherBacs()
{
    for(int i = 0; i < NB_BACS_MAX; ++i)
    {
        QSizePolicy sizePolicy = encadrementsBacs[i]->sizePolicy();
        sizePolicy.setRetainSizeWhenHidden(true);
        encadrementsBacs[i]->setSizePolicy(sizePolicy);
        encadrementsBacs[i]->setVisible(false);
    }
}
