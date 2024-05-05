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

    // une trame 'E' (encodeur) ?
    if(champs.at(0) == TYPE_TRAME_ENCODEUR)
    {
        bool ok = false;
        int  typeEncodage =
          champs.at(ACTION).toInt(&ok, 10); // il faut extraire l'action sous forme d'un int
        qDebug() << Q_FUNC_INFO << "ok = " << ok << "typeEncodage = " << typeEncodage;
        if(!ok)
            return;
        switch(typeEncodage)
        {
            case DROITE:
                emit encodeurDroite();
                break;
            case GAUCHE:
                emit encodeurGauche();
                break;
            case VALIDATION:
                emit encodeurValidation();
                break;
        }
    }
}

void DialogueModule::envoyerTrame(QString trame)
{
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
    // trame valide ?
    if(verifierTrame(donneesRecues))
    {
        decoderTrame(donneesRecues); // décoder la trame
    }
}

void DialogueModule::gererErreur(QSerialPort::SerialPortError erreur)
{
    qDebug() << Q_FUNC_INFO << "erreur" << erreur << "isOpen" << portSerie->isOpen();
    // @todo il faudra connecter le signal erreurOuvertureModule() pour que l'IHM affiche une boîte
    // de dialogue d'erreur
    if(erreur == QSerialPort::DeviceNotFoundError)
        emit erreurOuvertureModule();

    // Erreur en cours d'exécution si on envoie une trame : QSerialPort::ResourceError
    if(erreur == QSerialPort::ResourceError)
    {
        fermerPortSerie();
        emit erreurDialogueModule();
    }
}
