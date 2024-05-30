#include "processusassemblage.h"
#include "postetravail.h"
#include "etape.h"
#include "dialoguemodule.h"
#include "etape.h"
#include "bac.h"
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
    nom      = configurationProcessusAssemblage.value("ProcessusAssemblage/nom").toString();
    nbEtapes = configurationProcessusAssemblage.value("ProcessusAssemblage/etapes").toInt();
    nomImage = configurationProcessusAssemblage.value("ProcessusAssemblage/image").toString();
    bool existenceGlossaire =
      configurationProcessusAssemblage.value("ProcessusAssemblage/glossaire").toBool();
    QVector<Bac*> bacUtilise;
    qDebug() << Q_FUNC_INFO << "nom" << nom << "nbEtapes" << nbEtapes << "nomImage" << nomImage
             << "existenceGlossaire" << existenceGlossaire;

    // Parcourir les étapes du processus
    for(int i = 1; i <= nbEtapes; i++)
    {
        /*
            Exemple d'une étape :
            [Etape1]
            nom="Placer le composant Q1, Q2 et Q3"
            bacs=1
            image=2n7002.png
         */
        QString nomSection = QString("Etape%1").arg(i);
        nomOperation       = configurationProcessusAssemblage.value(nomSection + "/nom").toString();
        int nbBacs         = configurationProcessusAssemblage.value(nomSection + "/bacs").toInt();
        qDebug() << Q_FUNC_INFO << "nomOperation" << nomOperation << "nbBacs" << nbBacs
                 << "nomSection" << nomSection;
        for(int j = 1; j <= nbBacs; j++)
        {
            QString nomSectionBac = QString("Bac%1.%2").arg(i).arg(j);
            int     idBac = configurationProcessusAssemblage.value(nomSectionBac + "/id").toInt();
            QString nomPiece =
              configurationProcessusAssemblage.value(nomSectionBac + "/piece").toString();
            int nbPieces = configurationProcessusAssemblage.value(nomSectionBac + "/nb").toInt();
            QString nomImagePiece =
              configurationProcessusAssemblage.value(nomSectionBac + "/image").toString();

            bacUtilise.push_back(new Bac(idBac, nomPiece, nbPieces, nomImage));
            qDebug() << Q_FUNC_INFO << "nomSectionBac" << nomSectionBac << "idBac" << idBac
                     << "nomPiece" << nomPiece << "nomImagePiece" << nomImagePiece << "bacUtilise"
                     << bacUtilise;
        }
        etapes.push_back(new Etape(i, bacUtilise));
        qDebug() << Q_FUNC_INFO << "etape" << i << "Etape" << etapes;

        bacUtilise.clear();
        // @todo instancier les objets Etape et les ajouter à la QList etapes
    }
}

QString ProcessusAssemblage::getNom() const
{
    return nom;
}

int ProcessusAssemblage::getNbEtapes() const
{
    return nbEtapes;
}

int ProcessusAssemblage::getNbBacs() const
{
    return nbBacs;
}

QString ProcessusAssemblage::getNomOperation() const
{
    return nomOperation;
}

QString ProcessusAssemblage::getNomImage() const
{
    return nomImage;
}
