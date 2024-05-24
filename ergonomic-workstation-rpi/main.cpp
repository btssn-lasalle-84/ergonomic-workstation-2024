#include "ihm.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application Quizzy
 * @author Gabain AVRIL
 * @version 0.2
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    IHM          ihm;

    ihm.showMaximized();

    return a.exec();
}
