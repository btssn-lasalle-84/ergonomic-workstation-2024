#include "postetravail.h"
#include "processusassemblage.h"
#include "operateur.h"
#include <QDebug>

PosteTravail::PosteTravail(ProcessusAssemblage* processusAssemblage) :
    QObject(processusAssemblage), processusAssemblage(processusAssemblage), operateur(nullptr)
{
    qDebug() << Q_FUNC_INFO;
}

PosteTravail::~PosteTravail()
{
    qDebug() << Q_FUNC_INFO;
}
