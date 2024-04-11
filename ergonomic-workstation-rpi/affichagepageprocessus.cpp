#include "affichagepageprocessus.h"

AffichagePageProcessus::AffichagePageProcessus(QWidget* parent) : QWidget(parent)
{
}

void AffichagePageProcessus::afficher()
{
    QWidget::show();
    nomModule     = new QLabel(this);
    boutonAbandon = new QPushButton("Pipi", this);

    nomModule->setText("caca");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nomModule);
    layout->addWidget(boutonAbandon);
    setLayout(layout);
}
