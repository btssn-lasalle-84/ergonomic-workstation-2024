#include "affichagepageprocessus.h"

AffichagePageProcessus::AffichagePageProcessus(QWidget* parent) : QWidget(parent)
{
    premiereFenetre   = new QWidget(this);
    nomModule         = new QLabel("Nom Module", this);
    operations        = new QLabel("Opération", this);
    photoExpliquative = new QLabel("photo", this);
    boutonAbandon     = new QPushButton("Abandon", this);
    etapes            = new QStackedWidget(this);
    etapes->addWidget(premiereFenetre);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nomModule);
    layout->addWidget(boutonAbandon);
    layout->addWidget(operations);
    layout->addWidget(photoExpliquative);
    premiereFenetre->setLayout(layout);
}

void AffichagePageProcessus::afficher()
{
    QWidget::show();
}

AffichagePageProcessus::~AffichagePageProcessus()
{
    qDebug() << Q_FUNC_INFO;
}
