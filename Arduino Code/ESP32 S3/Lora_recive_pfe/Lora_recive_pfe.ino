/*
#include <LoRa.h>

#include <SPI.h>

// Configuration des broches pour le module LoRa
#define SCK 12
#define MISO 13
#define MOSI 11
#define SS 10
#define RST 8
#define DIO0 21 
#define DATARECEIVERLED 4  
int expectedPacket = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  pinMode(DATARECEIVERLED,OUTPUT);
  digitalWrite(DATARECEIVERLED,LOW);
  
  // Initialisation du module LoRa
  Serial.println("Initialisation LoRa...");
  LoRa.setPins(SS, RST, DIO0); // Configuration des broches
  LoRa.setSpreadingFactor(7);    // Transmission rapide (~100 ms)
  LoRa.setSignalBandwidth(250E3); // Augmenter le débit
  LoRa.setTxPower(10);            // Respect des 10 dBm max en France

  if (!LoRa.begin(433.5E6))  // Configure la fréquence à 433.5 MHz
 {    // Configurer la fréquence 433 MHz
    Serial.println("Échec de l'initialisation du LoRa !");
    while (1);
  }
  Serial.println("LoRa initialisé, en attente de messages...");
}

void loop() {
  // Vérifie si un paquet a été reçu
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
     Serial.println("Message reçu !");
     //digitalWrite(DATARECEIVERLED, !digitalRead(DATARECEIVERLED));
     digitalWrite(DATARECEIVERLED, HIGH); 
  
   
    // Lecture du contenu du message
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    // Afficher le message reçu
 
    Serial.println(receivedMessage);
    
    int receivedPacketNum = receivedMessage.substring(7).toInt();
    if (receivedPacketNum != expectedPacket) {
      Serial.println("⚠️ Paquet perdu ou désynchronisation détectée !");
    }
    
    expectedPacket = receivedPacketNum + 1;
    // Afficher les informations supplémentaires
    Serial.print("RSSI : ");
    Serial.println(LoRa.packetRssi()); // Indique la puissance du signal
    Serial.print("SNR : ");
    Serial.println(LoRa.packetSnr());  // Indique le rapport signal/bruit
  }
   else
    {  digitalWrite(DATARECEIVERLED, LOW); }
  
}
*/

/* CODE AVEC ACK
#include <SPI.h>
#include <LoRa.h>

#define SCK 12
#define MISO 13
#define MOSI 11
#define SS 10
#define RST 8
#define DIO0 21   
#define DATARECEIVERLED 4  
void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Initialisation du récepteur LoRa...");
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433.5E6)) {
    Serial.println("Échec de l'initialisation du LoRa !");
    while (1);
  }
  Serial.println("Récepteur LoRa prêt !");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    Serial.println("Message reçu : " + receivedMessage);

    // Envoyer un ACK de retour
    delay(100); // Petite pause pour éviter les conflits de transmission
    LoRa.beginPacket();
    LoRa.print("ACK");
    LoRa.endPacket();
    Serial.println("✅ ACK envoyé !");
  }
}
*/


#include <SPI.h>
#include <LoRa.h>

#define SCK 12
#define MISO 13
#define MOSI 11
#define SS 10
#define RST 8
#define DIO0 21 

#define DATARECEIVERLED 5

void setup() {
  Serial.begin(115200);
  pinMode(DATARECEIVERLED,OUTPUT);
  digitalWrite(DATARECEIVERLED,HIGH);
  //LoRa.setPreambleLength(12);
  //LoRa.setCodingRate4(1);
  //LoRa.setSignalBandwidth(250000);
  //LoRa.setSpreadingFactor(8);
  
  while (!Serial);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433.5E6)) {
    while (1); // Impossible d'initialiser
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
      
   }
   Serial.println(receivedMessage);

    //Serial.print("RSSI : ");
    //Serial.println(LoRa.packetRssi()); // Indique la puissance du signal
    //Serial.print("SNR : ");
    //Serial.println(LoRa.packetSnr());  // Indique le rapport signal/bruit

    digitalWrite(DATARECEIVERLED,HIGH);
    delay(100);
    //delay(100); // Petite pause pour éviter conflits
  
  }
  else{digitalWrite(DATARECEIVERLED,LOW);}
  }
 


