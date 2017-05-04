# Smart Home
Student project - subjects Mobile And Context Services
## Simple motion detector send valuue through radio (pir_arduinoMiniPro_rf24)
### Functionality
0. Begin communication at 9600 bps
1. Every loop read pir output value
2. Send 0(nothing)/1(motion) **ONCE** on 90 channel to other RF24 receiver in payload
```
struct payloadRF24Msg 
{
  unsigned int sensorValue;
};
```
3. Print sending value on serial bus
### Connections
![Alt text](pir_arduinoMiniPro_rf24/connections.png?raw=true "Connections")

## Simple server receiving on radio and sending through ethernet (ethernet_arduinoUno_rf24_center)
### Functionality
0. Begin communication at 9600 bps
1. If someone send 1/0 turn on relay1/2 
2. Send received message through ehternet

### Connections
![Alt text](ethernet_arduinoUno_rf24_center/connections.png?raw=true "Connections")