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
    PosteTravail*   posteTravail;
    QList<Etape*>   etapes;
    DialogueModule* dialogueModule;
    QString         nom;
    int             tempsMoyen;
    int             nbPieces;
    int             nbPiecesDifferentes;
    int             nbEtapes;

  public:
    explicit ProcessusAssemblage(QObject* parent = nullptr);
    ProcessusAssemblage(QString, int);
    ~ProcessusAssemblage();
    void chargerProcessusAssemblage(const QString&);

  signals:
};

#endif // PROCESSUSASSEMBLAGE_H
