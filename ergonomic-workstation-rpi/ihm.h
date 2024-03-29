#ifndef IHM_H
#define IHM_H

#include <QMainWindow>

namespace Ui { class IHM; }

class IHM : public QMainWindow
{
    Q_OBJECT

public:
    IHM(QWidget *parent = nullptr);
    ~IHM();

private:
    Ui::IHM *ui;
};
#endif // IHM_H
