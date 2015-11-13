/* ----
A very simple example that reports the Particle devices IP address over OSC.

Note that the message is sent only sent once during setup so your reeiving
computer should be listening on port 9999 before the device has initialised.

Make sure to change the computerIPAddress to match that of the receiving
computer. the message will be received on port 9999.

--- */

#include "particle-osc/particle-osc.h"

IPAddress computerIPAddress = IPAddress(192,168,1,2); // put the IP address of your computer here.
IPAddress particleIPAddress;
OSCMessage particleIPMessage("/coreip");

#define LOCALPORT  8888 // the port your Particle device can receive messages on.
#define REMOTEPORT 9999 // the port on your computer where the OSC messages will be sent.

UDP UdpConnection;

void setup() {
  UdpConnection.begin(LOCALPORT);

  particleIPAddress = WiFi.localIP();
  particleIPMessage.add(particleIPAddress[0]).add(particleIPAddress[1]).add(particleIPAddress[2]).add(particleIPAddress[3]);

  UdpConnection.beginPacket(computerIPAddress, REMOTEPORT);
  particleIPMessage.send(UdpConnection);
  UdpConnection.endPacket();
}

void loop() {

}
