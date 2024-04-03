#include "processusassemblage.h"
#include "postetravail.h"
#include "etape.h"
#include "dialoguemodule.h"
#include <QDebug>

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
