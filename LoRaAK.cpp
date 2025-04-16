#include <LoRa.h>         
#include "LoRaAK.h"
#include "fonctions.h"     // Ou tout autre header avec prepareLoRaMessage()

const int txPower = 20;

void initLoRa() {
  LoRa.setPins(ss, rst, dio0);  // Initialisation des broches LoRa

  if (!LoRa.begin(433E6)) {
    Serial.println("Erreur: LoRa non détecté!");
  } else {
    LoRa.setTxPower(txPower);
    LoRa.setSpreadingFactor(12);
    LoRa.setSignalBandwidth(125E3);
    LoRa.setCodingRate4(5);
    LoRa.setPreambleLength(8);
    LoRa.setSyncWord(0xF3);
    Serial.println("LoRa prêt.");
  }
}

void sendLoRa() {
  String dataToSend = prepareLoRaMessage();
  LoRa.beginPacket();
  LoRa.print(dataToSend);
  LoRa.endPacket();
  Serial.println("LoRa Sent: " + dataToSend);
}
