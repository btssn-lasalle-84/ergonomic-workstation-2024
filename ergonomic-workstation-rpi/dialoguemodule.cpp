#include "dialoguemodule.h"
#include <QDebug>

DialogueModule::DialogueModule(QObject* parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
}

DialogueModule::~DialogueModule()
{
    qDebug() << Q_FUNC_INFO;
}
