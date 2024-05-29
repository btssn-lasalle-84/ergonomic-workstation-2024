#ifndef PROCESSUSASSEMBLAGE_H
#define PROCESSUSASSEMBLAGE_H
#define RACINE_PROCESSUS_ASSEMBLAGE "/processus-assemblage"

#include <QObject>
#include <QList>
#include <QWidget>

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
    QString         nomProcessus;
    QDialog*        dialog;
    int             tempsMoyen;
    int             nbPieces;
    int             nbPiecesDifferentes;
    int             nbEtapes;

  public:
    explicit ProcessusAssemblage(QObject* parent = nullptr);
    ~ProcessusAssemblage();
    void    chargerProcessusAssemblage(const QString&);
    QString getNom() const;
    int     getNbEtapes() const;
    int     getNbPieces();
  signals:
};

#endif // PROCESSUSASSEMBLAGE_H
