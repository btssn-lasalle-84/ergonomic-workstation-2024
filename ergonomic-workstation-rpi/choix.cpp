#include "choix.h"
#include <QDebug>

Choix::Choix(QString nom, int numero, QWidget* parent /*= 0*/) :
    QLabel(parent), nom(nom), numero(numero), couleur("")
{
    QPalette palette;

    palette.setColor(QPalette::Window, QColor(QColor(255, 255, 255)));
    setAutoFillBackground(true);
    setPalette(palette);
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setText(nom);
    setFont(QFont("Courier New", 18));
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void Choix::setCouleur(QString couleur)
{
    this->couleur = couleur;
}

void Choix::setCouleur(int r, int g, int b)
{
    QString  couleur;
    QString  texteCouleur;
    QChar    c = '0';
    QPalette palette;

    palette.setColor(QPalette::Window, QColor(QColor(r, g, b)));
    setAutoFillBackground(true);
    setPalette(palette);

    couleur = QString("#%1%2%3").arg(r, 2, 16, c).arg(g, 2, 16, c).arg(b, 2, 16, c);
    if(r <= 70 && g <= 70 && b <= 70)
    {
        texteCouleur = QString("<font color=white>") + nom + QString("</font>");
    }
    else
    {
        texteCouleur = QString("<font color=black>") + nom + QString("</font>");
    }
    setText(texteCouleur);
    this->couleur = couleur;
}

void Choix::setCouleur(QColor color)
{
    QString  couleur;
    QString  texteCouleur;
    QChar    c = '0';
    QPalette palette;

    palette.setColor(QPalette::Window, QColor(color));
    setAutoFillBackground(true);
    setPalette(palette);

    couleur = QString("#%1%2%3")
                .arg(color.red(), 2, 16, c)
                .arg(color.green(), 2, 16, c)
                .arg(color.blue(), 2, 16, c);
    if(color.red() <= 70 && color.green() <= 70 && color.blue() <= 70)
    {
        texteCouleur = QString("<font color=white>") + nom + QString("</font>");
    }
    else
    {
        texteCouleur = QString("<font color=black>") + nom + QString("</font>");
    }
    setText(texteCouleur);
    this->couleur = couleur;
}

void Choix::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked(numero);
    }
}
