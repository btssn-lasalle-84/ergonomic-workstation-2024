#include "processusassemblage.h"
#include "postetravail.h"
#include "etape.h"
#include "bac.h"
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QTextCodec>
#include <QCoreApplication>

ProcessusAssemblage::ProcessusAssemblage(QObject* parent) :
    QObject(parent), posteTravail(new PosteTravail(this)), nom(""), tempsMoyen(0), nbPieces(0),
    nbPiecesDifferentes(0), nbEtapes(0)
{
    qDebug() << Q_FUNC_INFO;
}

ProcessusAssemblage::~ProcessusAssemblage()
{
    qDebug() << Q_FUNC_INFO;
}

void ProcessusAssemblage::chargerProcessusAssemblage(const QString& nomProcessusAssemblage)
{
    chemin = QCoreApplication::applicationDirPath() + QString(RACINE_PROCESSUS_ASSEMBLAGE) +
             QString("/") + nomProcessusAssemblage + QString("/");
    qDebug() << Q_FUNC_INFO << "chemin" << chemin;
    QString fichierINI = chemin + nomProcessusAssemblage + QString(".ini");
    qDebug() << Q_FUNC_INFO << "fichierINI" << fichierINI;

    QSettings configurationProcessusAssemblage(fichierINI, QSettings::IniFormat);
    configurationProcessusAssemblage.setIniCodec(QTextCodec::codecForName("UTF-8"));

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
    etapes.clear();
    for(int i = 1; i <= nbEtapes; i++)
    {
        /*
            Exemple d'une étape :
            [Etape1]
            nom="Placer le composant Q1, Q2 et Q3"
            bacs=1
            image=2n7002.png
         */
        QString nomSectionEtape = QString("Etape%1").arg(i);
        QString nomEtape =
          configurationProcessusAssemblage.value(nomSectionEtape + "/nom").toString();
        QString nomImageEtape =
          configurationProcessusAssemblage.value(nomSectionEtape + "/image").toString();
        int nbBacs = configurationProcessusAssemblage.value(nomSectionEtape + "/bacs").toInt();
        qDebug() << Q_FUNC_INFO << "nomSectionEtape" << nomSectionEtape << "nomEtape" << nomEtape
                 << "nbBacs" << nbBacs << "nomImageEtape" << nomImageEtape;
        for(int j = 1; j <= nbBacs; j++)
        {
            QString nomSectionBac = QString("Bac%1.%2").arg(i).arg(j);
            int     idBac = configurationProcessusAssemblage.value(nomSectionBac + "/id").toInt();
            QString nomPiece =
              configurationProcessusAssemblage.value(nomSectionBac + "/piece").toString();
            int nbPieces = configurationProcessusAssemblage.value(nomSectionBac + "/nb").toInt();
            QString nomImagePiece =
              configurationProcessusAssemblage.value(nomSectionBac + "/image").toString();
            qDebug() << Q_FUNC_INFO << "nomSectionBac" << nomSectionBac;
            bacUtilise.push_back(new Bac(idBac, nomPiece, nbPieces, nomImagePiece));
        }
        etapes.push_back(new Etape(i, nomEtape, nomImageEtape, bacUtilise));
        bacUtilise.clear();
    }
    qDebug() << Q_FUNC_INFO << "nbEtapes chargées" << etapes.size();
}

QString ProcessusAssemblage::getNom() const
{
    return nom;
}

QString ProcessusAssemblage::getNomImage() const
{
    return nomImage;
}

QString ProcessusAssemblage::getChemin() const
{
    return chemin;
}

int ProcessusAssemblage::getNbEtapes() const
{
    return nbEtapes;
}

int ProcessusAssemblage::getNbPieces() const
{
    return nbPieces;
}

int ProcessusAssemblage::getNbBacs() const
{
    return nbBacs;
}

QList<Etape*> ProcessusAssemblage::getEtapes() const
{
    return etapes;
}
