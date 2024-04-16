#ifndef DIALOGUEMODULE_H
#define DIALOGUEMODULE_H

#include <QObject>
#include <QByteArray>
#include <QSerialPort>

/**
 * @def NOM_PORT_SERIE
 * @brief Le port par défaut du module EC "poste de travail"
 */
#define NOM_PORT_SERIE "/dev/ttyUSB0"

/**
 * @def TYPE_TRAME_ENCODEUR
 * @brief La trame "$E;1|2|3\n" envoyé par le module EC "poste de travail"
 */
#define TYPE_TRAME_ENCODEUR QByteArray("E")

class DialogueModule : public QObject
{
    Q_OBJECT
  private:
    /**
     * @enum TypeEncodage
     * @brief Les differents types d'actions de l'encodeur dans la trame "$E"
     */
    enum TypeEncodage
    {
        INDETERMINE = 0,
        DROITE      = 1,
        GAUCHE      = 2,
        VALIDATION  = 3
    };
    /**
     * @enum NumeroChampTrameEncodeur
     * @brief Les numéros de champs dans la trame "$E;1|2|3\n"
     */
    enum NumeroChampTrameEncodeur
    {
        TYPE_TRAME = 0,
        ACTION     = 1,
        NB_CHAMPS_TRAME_ENCODEUR
    };

  public:
    explicit DialogueModule(QObject* parent = nullptr);
    ~DialogueModule();

    void demarrer();
    void arreter();

    void envoyerTrame(QString trame);

  private:
    QSerialPort* portSerie; //!< pour gérer le port série

    void configurerPortSerie(QString nomPortSerie = NOM_PORT_SERIE);
    void ouvrirPortSerie();
    void fermerPortSerie();
    bool verifierTrame(const QByteArray& trame);
    void decoderTrame(QByteArray trame);

  signals:
    void moduleConnecte();
    void moduleDeconnecte();
    void encodeurDroite();
    void encodeurGauche();
    void encodeurValidation();

  public slots:
    void recevoirTrame();
    void gererErreur(QSerialPort::SerialPortError erreur);
};

#endif // DIALOGUEMODULE_H
