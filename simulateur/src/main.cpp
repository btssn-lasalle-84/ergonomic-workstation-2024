/**
 * @file src/main.cpp
 * @brief Programme principal ErgonomicWorkstation 2024
 * @author Thierry Vaira
 * @version 1.0
 */
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <afficheur.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"

//#define DEBUG

// Brochages
#define GPIO_LED_ROUGE   5  //!<
#define GPIO_LED_ORANGE  17 //!<
#define GPIO_LED_VERTE   16 //!<
#define GPIO_SW1         12 //!<
#define GPIO_SW2         14 //!<
#define GPIO_ENCODEUR_A  2
#define GPIO_ENCODEUR_B  4
#define GPIO_ENCODEUR_E  13
#define ADRESSE_I2C_OLED 0x3c //!< Adresse I2C de l'OLED
#define BROCHE_I2C_SDA   21   //!< Broche SDA
#define BROCHE_I2C_SCL   22   //!< Broche SCL

// Protocole (cf. Google Drive)
#define EN_TETE_TRAME    "$"
#define DELIMITEUR_CHAMP ";"
#define DELIMITEURS_FIN  "\n"
#define DELIMITEUR_DATAS ';'
#define DELIMITEUR_FIN   '\n'

//#define BLUETOOTH
#ifdef BLUETOOTH
#define BLUETOOTH_SLAVE //!< esclave
// #define BLUETOOTH_MASTER //!< maître
BluetoothSerial ESPBluetooth;
#endif

// Évaluateur -> Pupitre
/**
 * @enum TypeTrameRecue
 * @brief Les differents types de trame reçue
 */
enum TypeTrameRecue
{
    Inconnu = -1,
    NB_TRAMES_RECUES
};

/**
 * @enum ChampTrame
 * @brief Les differents champs d'une trame
 */
enum ChampTrame
{
    ENTETE = 0,
    NB_CHAMPS
};

/**
 * @enum TypeTrameEnvoyee
 * @brief Les differents types de trame envoyée
 */
enum TypeTrameEnvoyee
{
    ENCODEUR,     // Envoi réponse
    ACQUITTEMENT, // Acquitter
    NB_TRAMES_ENVOYEES
};

/**
 * @enum TypeEncodage
 * @brief Les differents types d'actions de l'encodeur
 */
enum TypeEncodage
{
    INDETERMINE = 0,
    DROITE      = 1,
    GAUCHE      = 2,
    VALIDATION  = 3
};

const String nomsTrameRecue[TypeTrameRecue::NB_TRAMES_RECUES] = {}; //!< nom des trames recues dans
                                                                    //!< le protocole

const String nomsTrameEnvoyee[TypeTrameEnvoyee::NB_TRAMES_ENVOYEES] = {
    "E",
    "A"
}; //!< nom des trames envoyées dans le protocole

bool         bouton     = false; //!<
bool         encodeur   = false; //!<
bool         encodeurA  = false; //!<
bool         encodeurB  = false; //!<
TypeEncodage action     = TypeEncodage::INDETERMINE;
bool         refresh    = false; //!< demande rafraichissement de l'écran OLED
bool         antiRebond = false; //!< anti-rebond
Afficheur    afficheur(ADRESSE_I2C_OLED, BROCHE_I2C_SDA,
                    BROCHE_I2C_SCL);                //!< afficheur OLED SSD1306
String       entete        = String(EN_TETE_TRAME);    // caractère séparateur
String       separateur    = String(DELIMITEUR_CHAMP); // caractère séparateur
String       delimiteurFin = String(DELIMITEURS_FIN);  // fin de trame

String extraireChamp(String& trame, unsigned int numeroChamp)
{
    String       champ;
    unsigned int compteurCaractere  = 0;
    unsigned int compteurDelimiteur = 0;
    char         fin                = '\n';

    if(delimiteurFin.length() > 0)
        fin = delimiteurFin[0];

    for(unsigned int i = 0; i < trame.length(); i++)
    {
        if(trame[i] == separateur[0] || trame[i] == fin)
        {
            compteurDelimiteur++;
        }
        else if(compteurDelimiteur == numeroChamp)
        {
            champ += trame[i];
            compteurCaractere++;
        }
    }

    return champ;
}

/**
 * @brief Envoie une trame réponse
 *
 */
void envoyerTrameEncodeur(int action)
{
    char trameEnvoi[64];
    // Format : $R;NUMERO_QUESTION;NUMERO_REPONSE;TEMPS_REPONSE\n
    sprintf((char*)trameEnvoi, "%sE;%d\n", entete.c_str(), action);
#ifdef BLUETOOTH
    ESPBluetooth.write((uint8_t*)trameEnvoi, strlen((char*)trameEnvoi));
#else
    Serial.write((uint8_t*)trameEnvoi, strlen((char*)trameEnvoi));
#endif

#ifdef DEBUG
    String trame = String(trameEnvoi);
    trame.remove(trame.indexOf("\n"), 1);
    Serial.print("> ");
    Serial.println(trame);
#endif
}

/**
 * @brief Envoie une trame d'acquittement
 *
 */
void envoyerTrameAcquittement()
{
    char trameEnvoi[64];
    // Format : $A\n
    sprintf((char*)trameEnvoi, "%sA\n", entete.c_str());
#ifdef BLUETOOTH
    ESPBluetooth.write((uint8_t*)trameEnvoi, strlen((char*)trameEnvoi));
#else
    Serial.write((uint8_t*)trameEnvoi, strlen((char*)trameEnvoi));
#endif
#ifdef DEBUG
    String trame = String(trameEnvoi);
    trame.remove(trame.indexOf("\n"), 1);
    Serial.print("> ");
    Serial.println(trame);
#endif
}

void IRAM_ATTR encoderA()
{
    if(antiRebond || encodeurA)
        return;

    encodeurA  = true;
    antiRebond = true;
}

void IRAM_ATTR encoderB()
{
    if(antiRebond || encodeurB)
        return;

    encodeurB  = true;
    antiRebond = true;
}

void IRAM_ATTR encoderE()
{
    if(antiRebond || encodeur)
        return;

    encodeur   = true;
    antiRebond = true;
}

/**
 * @brief Lit une trame via le Bluetooth
 *
 * @fn lireTrame(String &trame)
 * @param trame la trame reçue
 * @return bool true si une trame a été lue, sinon false
 */
bool lireTrame(String& trame)
{
#ifdef BLUETOOTH
    if(ESPBluetooth.available())
    {
        trame.clear();
        trame = ESPBluetooth.readStringUntil(DELIMITEUR_FIN);
#ifdef DEBUG
        Serial.print("< ");
        Serial.println(trame);
#endif
        trame.concat(DELIMITEUR_FIN); // remet le DELIMITEUR_FIN
        return true;
    }
#else
    if(Serial.available())
    {
        trame.clear();
        trame = Serial.readStringUntil(DELIMITEUR_FIN);
#ifdef DEBUG
        Serial.print("< ");
        Serial.println(trame);
#endif
        trame.concat(DELIMITEUR_FIN); // remet le DELIMITEUR_FIN
        return true;
    }
#endif // BLUETOOTH

    return false;
}

/**
 * @brief Vérifie si la trame reçue est valide et retorune le type de la trame
 *
 * @fn verifierTrame(String &trame)
 * @param trame
 * @return TypeTrame le type de la trame
 */
TypeTrameRecue verifierTrame(String& trame)
{
    String format;

    for(int i = 0; i < TypeTrameRecue::NB_TRAMES_RECUES; i++)
    {
        // Format : ${TYPE};...\n
        format = entete + nomsTrameRecue[i];

        if(trame.indexOf(format) != -1)
        {
            return (TypeTrameRecue)i;
        }
        else
        {
#ifdef DEBUG
            Serial.println("");
#endif
        }
    }
#ifdef DEBUG
    Serial.println("Type de trame : inconnu");
#endif
    return Inconnu;
}

void reinitialiserAffichage()
{
    afficheur.setMessageLigne(Afficheur::Ligne1, ""); //
    afficheur.setMessageLigne(Afficheur::Ligne2, ""); //
    afficheur.setMessageLigne(Afficheur::Ligne3, ""); //
    afficheur.setMessageLigne(Afficheur::Ligne4, ""); //
    refresh = true;
}

/**
 * @brief Initialise les ressources du programme
 *
 * @fn setup
 *
 */
void setup()
{
    Serial.begin(115200);
    while(!Serial)
        ;

    pinMode(GPIO_LED_ROUGE, OUTPUT);
    pinMode(GPIO_LED_ORANGE, OUTPUT);
    pinMode(GPIO_LED_VERTE, OUTPUT);
    // pinMode(GPIO_SW1, INPUT_PULLUP);
    // pinMode(GPIO_SW2, INPUT_PULLUP);
    pinMode(GPIO_ENCODEUR_A, INPUT_PULLUP);
    pinMode(GPIO_ENCODEUR_B, INPUT_PULLUP);
    pinMode(GPIO_ENCODEUR_E, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(GPIO_ENCODEUR_A), encoderA, FALLING);
    attachInterrupt(digitalPinToInterrupt(GPIO_ENCODEUR_B), encoderB, FALLING);
    attachInterrupt(digitalPinToInterrupt(GPIO_ENCODEUR_E), encoderE, FALLING);

    digitalWrite(GPIO_LED_ROUGE, LOW);
    digitalWrite(GPIO_LED_ORANGE, LOW);
    digitalWrite(GPIO_LED_VERTE, LOW);

    afficheur.initialiser();

    String titre  = "";
    String stitre = "=====================";

#ifdef BLUETOOTH
#ifdef BLUETOOTH_MASTER
    String nomBluetooth = "iot-esp-maitre";
    ESPBluetooth.begin(nomBluetooth, true);
    const uint8_t* adresseESP32 = esp_bt_dev_get_address();
    char           str[18];
    sprintf(str,
            "%02x:%02x:%02x:%02x:%02x:%02x",
            adresseESP32[0],
            adresseESP32[1],
            adresseESP32[2],
            adresseESP32[3],
            adresseESP32[4],
            adresseESP32[5]);
    stitre = String("== ") + String(str) + String(" ==");
    titre  = nomBluetooth;
#else
    String nomBluetooth = "ew-p1";
    ESPBluetooth.begin(nomBluetooth);
    const uint8_t* adresseESP32 = esp_bt_dev_get_address();
    char           str[18];
    sprintf(str,
            "%02x:%02x:%02x:%02x:%02x:%02x",
            adresseESP32[0],
            adresseESP32[1],
            adresseESP32[2],
            adresseESP32[3],
            adresseESP32[4],
            adresseESP32[5]);
    stitre = String("== ") + String(str) + String(" ==");
    titre  = nomBluetooth;
#endif // BLUETOOTH_MASTER
#else
    stitre = String("===================");
    titre  = "ew-p1";
#endif // BLUETOOTH

#ifdef DEBUG
    Serial.println(titre);
    Serial.println(stitre);
#endif

    afficheur.setTitre(titre);
    afficheur.setSTitre(stitre);
    afficheur.afficher();

    // initialise le générateur pseudo-aléatoire
    // Serial.println(randomSeed(analogRead(34)));
    Serial.println(esp_random());
}

/**
 * @brief Boucle infinie d'exécution du programme
 *
 * @fn loop
 *
 */
void loop()
{
    String         trame;
    TypeTrameRecue typeTrame;
    char           strMessageDisplay[24];

    if(refresh)
    {
        afficheur.afficher();
        refresh = false;
    }

    if(antiRebond)
    {
        afficheur.afficher();
        delay(300);
        antiRebond = false;
    }

    if(encodeur)
    {
        // validation
        encodeur = false;
        action   = TypeEncodage::VALIDATION;
        envoyerTrameEncodeur(int(action));
        afficheur.setMessageLigne(Afficheur::Ligne4, String("VALIDATION"));
        refresh = true;
    }

    if(encodeurA)
    {
        // gauche
        encodeurA = false;
        action    = TypeEncodage::GAUCHE;
        envoyerTrameEncodeur(int(action));
        afficheur.setMessageLigne(Afficheur::Ligne3, String("GAUCHE"));
        afficheur.setMessageLigne(Afficheur::Ligne4, String(""));
        refresh = true;
#ifdef DEBUG
        Serial.println(strMessageDisplay);
#endif
    }

    if(encodeurB)
    {
        // droite
        encodeurB = false;
        action    = TypeEncodage::DROITE;
        envoyerTrameEncodeur(int(action));
        afficheur.setMessageLigne(Afficheur::Ligne3, String("DROITE"));
        afficheur.setMessageLigne(Afficheur::Ligne4, String(""));
        refresh = true;
#ifdef DEBUG
        Serial.println(strMessageDisplay);
#endif
    }

    if(lireTrame(trame))
    {
        typeTrame = verifierTrame(trame);
        refresh   = true;
#ifdef DEBUG
        if(typeTrame >= 0)
            Serial.println("\nTrame : " + nomsTrameRecue[typeTrame]);
#endif
        String strNumeroQuestion;
        String strTempsAlloue;
        switch(typeTrame)
        {
            case Inconnu:
                break;
            default:
#ifdef DEBUG
                Serial.println("Trame invalide !");
#endif
                break;
        }
    }
}
