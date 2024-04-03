#ifndef DIALOGUEMODULE_H
#define DIALOGUEMODULE_H

#include <QObject>

class DialogueModule : public QObject
{
    Q_OBJECT
  public:
    explicit DialogueModule(QObject* parent = nullptr);
    ~DialogueModule();

  signals:
  public slots:
};

#endif // DIALOGUEMODULE_H
