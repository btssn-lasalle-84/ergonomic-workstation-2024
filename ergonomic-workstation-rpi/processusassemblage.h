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
    QString         nom;
    QString         nomOperation;
    QDialog*        dialog;
    int             tempsMoyen;
    int             nbPieces;
    int             nbPiecesDifferentes;
    int             nbEtapes;
    int             nbBacs;

  public:
    explicit ProcessusAssemblage(QObject* parent = nullptr);
    ~ProcessusAssemblage();
    void    chargerProcessusAssemblage(const QString&);
    QString getNom() const;
    QString getNomOperation() const;
    int     getNbEtapes() const;
    int     getNbPieces() const;
    int     getNbBacs() const;
  signals:
};

#endif // PROCESSUSASSEMBLAGE_H
