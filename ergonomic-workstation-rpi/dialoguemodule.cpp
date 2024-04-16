#include "dialoguemodule.h"
#include <QDebug>

DialogueModule::DialogueModule(QObject* parent) : QObject(parent), portSerie(new QSerialPort(this))
{
    qDebug() << Q_FUNC_INFO;
}

DialogueModule::~DialogueModule()
{
    // @todo appeler arreter()
    qDebug() << Q_FUNC_INFO;
}

void DialogueModule::demarrer()
{
    qDebug() << Q_FUNC_INFO;
    // @todo appeler configurerPortSerie()
    // @todo puis appeler ouvrirPortSerie()
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
    // @todo voir avec l'EC pour le choix du débit
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
    // @todo vérifier si la trame reçue est valide (au moins si elle commence par '$' et elle se
    // termine '\n'

    return false;
}

void DialogueModule::decoderTrame(QByteArray trame)
{
    // @todo retirer '$' et '\n'

    // @todo splitter la trame avec le séparateur de champs

    // @todo si c'est une trame 'E' (encodeur), il faut extraire l'action sous forme d'un int

    // @todo puis avec un switch, définir les case TypeEncodage pour émettre les signaux
    // encodeurDroite(), encodeurGauche() ou encodeurValidation() remarque : ces signaux sont
    // connectés à des lots de l'IHM
}

void DialogueModule::envoyerTrame(QString trame)
{
    // @todo si portSerie est ouvert, alors ajouter le '\n' à la trame puis l'envoyer avec la
    // méthode write remarque : il faut utiliser trame.toLatin1() dans l'appel write()
}

void DialogueModule::recevoirTrame()
{
    QByteArray donneesRecues;

    while(portSerie->waitForReadyRead(500))
    {
        donneesRecues.append(portSerie->readAll());
    }
    qDebug() << Q_FUNC_INFO << "donneesRecues" << donneesRecues;

    // @todo si la trame est valdie (appel de la méthode verifierTrame())
    // @todo décoder la trame (appel de la méthoder decoderTrame())
}

void DialogueModule::gererErreur(QSerialPort::SerialPortError erreur)
{
    qDebug() << Q_FUNC_INFO << "erreur" << erreur << "isOpen" << portSerie->isOpen();
    // Erreur à l'ouverture : QSerialPort::DeviceNotFoundError
    // @todo il faudra emettre un signal erreurOuvertureModule() pourque l'IHM affiche une boîte de
    // dialogue d'erreur

    // Erreur en cours d'exécution si on envoie une trame : QSerialPort::ResourceError
    if(erreur == QSerialPort::ResourceError)
    {
        fermerPortSerie();
        // @todo il faudra emettre un signal erreurDialogueModule() pourque l'IHM affiche une boîte
        // de dialogue d'erreur de communication
    }
}
