#include "processusassemblage.h"
#include "postetravail.h"
#include "etape.h"
#include "dialoguemodule.h"
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QWidget>

ProcessusAssemblage::ProcessusAssemblage(QObject* parent) :
    QObject(parent), posteTravail(new PosteTravail(this)), dialogueModule(new DialogueModule(this)),
    nom(""), tempsMoyen(0), nbPieces(0), nbPiecesDifferentes(0), nbEtapes(0)
{
    qDebug() << Q_FUNC_INFO;
}

ProcessusAssemblage::~ProcessusAssemblage()
{
    qDebug() << Q_FUNC_INFO;
}

void ProcessusAssemblage::chargerProcessusAssemblage(const QString& nomProcessusAssemblage)
{
    qDebug() << Q_FUNC_INFO << "nomProcessusAssemblage" << nomProcessusAssemblage;

    QString fichierINI = QDir::currentPath() + QString(RACINE_PROCESSUS_ASSEMBLAGE) + QString("/") +
                         nomProcessusAssemblage + QString("/") + nomProcessusAssemblage +
                         QString(".ini");

    qDebug() << Q_FUNC_INFO << "fichierINI" << fichierINI;
    QSettings configurationProcessusAssemblage(fichierINI, QSettings::IniFormat);

    /*
        [ProcessusAssemblage]
        nom="Module O-LEDs-BP"
        etapes=3
        image=module-oled-bp.png
        glossaire=true
     */
    QString nomProcessus =
      configurationProcessusAssemblage.value("ProcessusAssemblage/nom").toString();
    int     nbEtapes = configurationProcessusAssemblage.value("ProcessusAssemblage/etapes").toInt();
    QString nomImage =
      configurationProcessusAssemblage.value("ProcessusAssemblage/image").toString();
    bool existenceGlossaire =
      configurationProcessusAssemblage.value("ProcessusAssemblage/glossaire").toBool();
    qDebug() << Q_FUNC_INFO << "nom" << nom << "nbEtapes" << nbEtapes << "nomImage" << nomImage
             << "existenceGlossaire" << existenceGlossaire;

    for(int i = 1; i <= nbEtapes; i++)
    {
        /*
            [Etape1]
            nom="Placer le composant Q1, Q2 et Q3"
            bacs=1
            image=2n7002.png
         */
        QString nomSection = QString("Etape%1").arg(i);
        QString nom        = configurationProcessusAssemblage.value(nomSection + "/nom").toString();
        int     nbBacs     = configurationProcessusAssemblage.value(nomSection + "/bacs").toInt();
        qDebug() << Q_FUNC_INFO << "nom" << nom << "nbBacs" << nbBacs;
    }
}

QString ProcessusAssemblage::getNom() const
{
    qDebug() << Q_FUNC_INFO << "méthode exéctutée";
    return this->nom;
    qDebug() << "nom" << nom;
}

int ProcessusAssemblage::getNbEtapes() const
{
    return nbEtapes;
}
