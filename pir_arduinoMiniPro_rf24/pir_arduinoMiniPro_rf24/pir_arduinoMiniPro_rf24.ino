#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

RF24 radio24(7,8);
RF24Network network(radio24);

/** RF24 IDs */
const uint16_t pirNodeId = 01;
const uint16_t serverNodeId = 00;

/** Analog input pin that the PIR is attached too */
const int pirDigitalPIN = 4; 
 
/** Value read from the pir values = HIRH/LOW */
int pirSensorValue = 0;  

/** Bool for discriminate whether high value was sended */ 
bool highValueWasSended = false;

/** RF24 send scruct */
struct payloadRF24Msg 
{
  unsigned int sensorValue;
};

void setup() 
{
  /** Initialize serial communications at 9600 bps */
  Serial.begin(9600);
  /** Initialize SPI pins for RF24 module */
  SPI.begin();

  radio24.begin();
  /** Channel 90 communication from this node */
  network.begin(90, pirNodeId);
}

void loop() 
{
  /** Update network state every loop */
  network.update();
  /** Read PIR value every loop */
  pirSensorValue = digitalRead(pirDigitalPIN);
  
  if(pirSensorValue == HIGH) 
      sendValueThroughRF24(1);
  else
      sendValueThroughRF24(0);
}

void sendValueThroughRF24(unsigned int val) 
{
  if(val == 1 && highValueWasSended)
    return;
  if(val == 0 && !highValueWasSended)
    return;
  Serial.print("SENDING :");
  Serial.println(val);
  RF24NetworkHeader header(serverNodeId);
  payloadRF24Msg payload = {val};
  bool ok = network.write(header, &payload, sizeof(payload));
  if(ok) 
  {
    Serial.println(" SENDED.");
    if(val == 1)
      highValueWasSended = true;
    else 
      highValueWasSended = false;
  }
  else 
  {
    Serial.println(" FAILED.");
  }
}

