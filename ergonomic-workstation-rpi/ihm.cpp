#include "ihm.h"
#include "ui_ihm.h"

IHM::IHM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IHM)
{
    ui->setupUi(this);
}

IHM::~IHM()
{
    delete ui;
}

