# MQTT-WIFI-DHT11

Read temperature and humidity from DHT11 connected to NodeMCU and send the data through MQTT to a Raspberry Pi. 

> Optionally, you can use the provided Raspberry Pi client written using Node.js to listen for the MQTT messages and to send them to ThingsBoard.

### Deep sleep vs light sleep

If you are using a battery which doesn't turn off itself after low activity, then feel free to use [mqtt-wifi-dht11-deep-sleep.ino](mqtt-wifi-dht11-deep-sleep.ino).

![diagram.png](diagram.png)

On the other hand, if you are using a battery which turns off itself such a modern power bank for mobile charging, use [mqtt-wifi-dht11-light-sleep.ino](mqtt-wifi-dht11-light-sleep.ino).

:warning: If using light sleep approach remove the wire from RST to D0 pins.

Deep sleep fully turns off the NodeMCU device while the light sleep mode just turns off some features of the NodeMCU (consumes more battery).
