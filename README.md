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

### BOM
| Part Name | Quantity | Price (USD) | Total (USD) | Link |
|---|---|---|---|---|
| ESP32-C3 SuperMiny | 2 | 2.98 | 5.96 | https://www.aliexpress.com/item/1005005834458965.html |
| 20pcs SK6812MINI-E | 1 | 1.96 | 1.96 | https://www.aliexpress.com/item/1005008308801366.html |
| 20PCS Tact Push Button Switch 12V Copper 4Pin SMD Micro Switch 6X6X5mm | 1 | 1.62 | 1.62 | 	https://www.aliexpress.com/item/1005005834458965.html |
| Custom PCB | 1 | 4.24 | 4.24 | jlcpcb |
| 3D Printed case | 1 | 0 | 0 | none - I have my own printer |
| Total ||| 13.78 |
