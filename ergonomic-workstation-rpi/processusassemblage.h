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
    // @todo ajouter un attribut pour le chemin vers le processus d'assemblage
    int tempsMoyen;
    int nbPieces;
    int nbPiecesDifferentes;
    int nbEtapes;
    int nbBacs;

  public:
    explicit ProcessusAssemblage(QObject* parent = nullptr);
    ~ProcessusAssemblage();
    void    chargerProcessusAssemblage(const QString&);
    QString getNom() const;
    QString getNomOperation() const;
    QString getNomImage() const;
    // @todo ajouter l'accesseur get pour le chemin vers le processus d'assemblage
    int           getNbEtapes() const;
    int           getNbPieces() const;
    int           getNbBacs() const;
    QList<Etape*> getEtapes() const;

  signals:
};

#endif // PROCESSUSASSEMBLAGE_H
