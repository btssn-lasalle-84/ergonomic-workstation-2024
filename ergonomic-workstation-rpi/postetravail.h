#ifndef POSTETRAVAIL_H
#define POSTETRAVAIL_H

#include <QObject>

class ProcessusAssemblage;
class Operateur;

class PosteTravail : public QObject
{
    Q_OBJECT
  private:
    ProcessusAssemblage* processusAssemblage;
    Operateur*           operateur;

  public:
    explicit PosteTravail(ProcessusAssemblage* processusAssemblage = nullptr);
    ~PosteTravail();
};

#endif // POSTETRAVAIL_H
