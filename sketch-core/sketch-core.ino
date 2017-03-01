/***********************************************
* tiempodesiembra.es
* root controller 0.0.1
**********************************************/

const char VERSION = {"0.0.2"};

/***********************************************
* Device setup
**********************************************/

/* Tiempo de siembra */
/* uuid - https://www.uuidgenerator.net/ */

// Unique ID for this device
const char DEVICE_UNIT_UUID   = {"8d1b208e-cadb-4767-b199-cda6cbed3b0d"};

// Cryto KEY used to share message with the root device.
const char DEVICE_LINK_CRYPTO = {"960e4ce7-53e2-48ac-b7bb-30ef00f2d20d"};

const int RF24_CE_PIN                         = 9;     // nRF24L01 ce pin
const int RF24_CSN_PIN                        = 10;    // nRF24L01 csn pin

/***********************************************
*
*
*    Do NOT change anything from this point
*
*
**********************************************/

/***********************************************
* Libraries
**********************************************/

// Vars
#include <printf.h>

// Comm
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

/***********************************************
* System definitions
**********************************************/

/* Loop */
const int LOOP_DELAY = 1 * 1000; // <seconds> * <ms>

/* Comm */
int msg[1];
RF24 radio(RF24_CE_PIN, RF24_CSN_PIN);
const uint64_t pipe = 0xE8E8F0F0E1LL;

// Received message
String message;

/***********************************************
* Functions
**********************************************/

void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  Serial.println("Start receiving");
}

void parseMessage() {
  Serial.println(message);
  message = "";
}

void loop(void){

  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));

    if((String(text) != "X") == 1)
    {
      message = String(message + text);
    }
    else
    {
      parseMessage();
    }
  }

  delay(LOOP_DELAY);

}
