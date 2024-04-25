#include "dialoguemodule.h"
#include "ihm.h"
#include <QDebug>

DialogueModule::DialogueModule(QObject* parent) : QObject(parent), portSerie(new QSerialPort(this))
{
    qDebug() << Q_FUNC_INFO;
}

DialogueModule::~DialogueModule()
{
    arreter();
    qDebug() << Q_FUNC_INFO;
}

void DialogueModule::demarrer()
{
    qDebug() << Q_FUNC_INFO;
    configurerPortSerie();
    ouvrirPortSerie();
}

void DialogueModule::arreter()
{
    qDebug() << Q_FUNC_INFO;

    fermerPortSerie();
}

void DialogueModule::configurerPortSerie(QString nomPortSerie)
{
    qDebug() << Q_FUNC_INFO << "nomPortSerie" << nomPortSerie;

    portSerie->setPortName(nomPortSerie);
    // @todo voir avec l'EC pour le choix du débit(9600)
    // portSerie->setBaudRate(QSerialPort::Baud9600);
    portSerie->setBaudRate(QSerialPort::Baud115200);
    portSerie->setDataBits(QSerialPort::Data8);
    portSerie->setParity(QSerialPort::NoParity);
    portSerie->setStopBits(QSerialPort::OneStop);
    portSerie->setFlowControl(QSerialPort::NoFlowControl);
}

void DialogueModule::ouvrirPortSerie()
{
    if(portSerie->open(QIODevice::ReadWrite))
    {
        qDebug() << Q_FUNC_INFO;
        connect(portSerie, SIGNAL(readyRead()), this, SLOT(recevoirTrame()));
        connect(portSerie,
                SIGNAL(error(QSerialPort::SerialPortError)),
                this,
                SLOT(gererErreur(QSerialPort::SerialPortError)));
        // @todo signal à connecter dans l'IHM pour signaler visuellement que le poste de travail
        // est bien connecté
        emit moduleConnecte();
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "erreur" << portSerie->error();
    }
}

void DialogueModule::fermerPortSerie()
{
    if(portSerie->isOpen())
    {
        portSerie->close();
        // @todo signal à connecter dans l'IHM pour signaler visuellement que le poste de travail
        // n'est pas connecté
        emit moduleDeconnecte();
    }
}

bool DialogueModule::verifierTrame(const QByteArray& trame)
{
    if(trame.at(0) == '$' && trame.at(trame.size() - 1) == '\n')
    {
        return true;
    }
    return false;
}

void DialogueModule::decoderTrame(QByteArray trame)
{
    trame.remove(0, 1);                // retire le '$'
    trame.remove(trame.size() - 1, 1); // retire le '\n'

    QList<QByteArray> champs = trame.split(';');
    qDebug() << "champs" << champs;

    // si c'est une trame 'E' (encodeur),
    if(champs.at(0) == TYPE_TRAME_ENCODEUR)
    {
        bool ok;
        int  typeEncodage =
          champs.at(1).toInt(&ok, 10); // il faut extraire l'action sous forme d'un int
        qDebug() << Q_FUNC_INFO << "ok == " << ok << "typeEncodage == " << typeEncodage;
        switch(typeEncodage)
        {
            case 1:
                connect(portSerie, SIGNAL(encodeurDroite()), this, SLOT(avancerChoix()));
                break;
            case 2:
                connect(portSerie, SIGNAL(encodeurGauche()), this, SLOT(reculerChoix()));
                break;
            case 3:
                connect(portSerie, SIGNAL(encodeurValidation()), this, SLOT(validerChoix()));
                break;
        }
    }
    // @todo puis avec un switch, définir les case TypeEncodage pour émettre les signaux
    // encodeurDroite(), encodeurGauche() ou encodeurValidation() remarque : ces signaux sont
    // connectés à des slots de l'IHM
}

void DialogueModule::envoyerTrame(QString trame)
{
    // @todo si portSerie est ouvert, alors ajouter le '\n' à la trame puis l'envoyer avec la
    // méthode write remarque : il faut utiliser trame.toLatin1() dans l'appel write()
    if(portSerie->open(QIODevice::WriteOnly))
    {
        portSerie->write(trame.toLatin1());
        portSerie->write("\n");
    }

}

void DialogueModule::recevoirTrame()
{
    QByteArray donneesRecues;

    while(portSerie->waitForReadyRead(500))
    {
        donneesRecues.append(portSerie->readAll());
    }
    qDebug() << Q_FUNC_INFO << "donneesRecues" << donneesRecues;
    // si la trame est valide
    if(verifierTrame(donneesRecues) == true)
    {
        decoderTrame(donneesRecues); // décoder la trame
    }
}

void DialogueModule::gererErreur(QSerialPort::SerialPortError erreur)
{
    qDebug() << Q_FUNC_INFO << "erreur" << erreur << "isOpen" << portSerie->isOpen();
    // Erreur à l'ouverture : QSerialPort::DeviceNotFoundError
    // @todo il faudra emettre un signal erreurOuvertureModule() pour que l'IHM affiche une boîte
    // de dialogue d'erreur
    connect(ihm, SIGNAL(erreurOuvertureModule()), this, SLOT(gererErreur(erreur))

    // Erreur en cours d'exécution si on envoie une trame : QSerialPort::ResourceError
    if(erreur == QSerialPort::ResourceError)
    {
        fermerPortSerie();
        // @todo il faudra emettre un signal erreurDialogueModule() pourque l'IHM affiche une
        // boîte de dialogue d'erreur de communication
        connect(ihm, SIGNAL(erreurDialogueModule()), this, SLOT(gererErreur(erreur)));
    }
}
