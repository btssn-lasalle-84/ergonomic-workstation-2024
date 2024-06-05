#ifndef PROCESSUSASSEMBLAGE_H
#define PROCESSUSASSEMBLAGE_H

#define RACINE_PROCESSUS_ASSEMBLAGE "/processus-assemblage"

#include <QObject>
#include <QList>

class PosteTravail;
class Etape;
class DialogueModule;

class ProcessusAssemblage : public QObject
{
    Q_OBJECT
  private:
    PosteTravail* posteTravail;
    QList<Etape*> etapes;
    QString       nom;
    QString       nomImage;
    QString       chemin;
    int           tempsMoyen;
    int           nbPieces;
    int           nbPiecesDifferentes;
    int           nbEtapes;
    int           nbBacs;

  public:
    explicit ProcessusAssemblage(QObject* parent = nullptr);
    ~ProcessusAssemblage();
    void          chargerProcessusAssemblage(const QString&);
    QString       getNom() const;
    QString       getNomImage() const;
    QString       getChemin() const;
    int           getNbEtapes() const;
    int           getNbPieces() const;
    int           getNbBacs() const;
    QList<Etape*> getEtapes() const;

  signals:
};

#endif // PROCESSUSASSEMBLAGE_H
