# Remote occupancy indicator

ESP32 based occupancy marker for meeting rooms, office cublicles and etc. and a simple remote for it.

### Setup 
1. Select the ESP32 Super Mini in Arduino IDE
2. Flash the MAC-Finder to both the boards and write down the MAC Address which will be sent in the Serial Monitor
3. In the indicator firmware file change the broadcast MAC address to the one the remote gave you
4. Flash!
5. Now in the remote firmware file change the boardcast MAC address to the one the indicator gave you
6. Flash!
7. Now the Indicator and Remote will connect to each other automatically

