#ifndef PROCESSUSASSEMBLAGE_H
#define PROCESSUSASSEMBLAGE_H

#include <QWidget>

class ProcessusAssemblage : public QWidget
{
    Q_OBJECT
private:
    Etape* etape;
    DialogueModule* dialogueModule;
    QString nom;
    int tempsMoyen;
    int nbPieces;
    int nbPiecesDifferentes;
    int nbEtapes;
public:
    explicit ProcessusAssemblage(QWidget *parent = nullptr);
    ProcessusAssemblage::ProcessusAssemblage();

signals:

};

#endif // PROCESSUSASSEMBLAGE_H
