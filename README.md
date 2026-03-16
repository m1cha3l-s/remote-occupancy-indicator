# Remote occupancy indicator

ESP32 based occupancy marker for meeting rooms, office cubicles and etc. and a simple remote for it. ESP-NOW is used for communication between the the boards, which are using the ESP32-C3 Super Mini

## Assembling
1. Print the both the Indicator and Remote top and bottom parts in a filament of your choice
2. Print the LED part of the Indicator and Remote case in a transparent filament or white filament (not tested) so that the leds can shine through it.
3. Use super glue to put the LED Parts in place (on the inside) if they already don't hold in place, even if they do the super glue wouldn't hurt.
4. The top and bottom of both cases snap together, after you snap them together you can move one the Setup!
5. For mounting use command strips or heavy duty double sided tape!!

## Setup 
1. Select the ESP32 Super Mini in Arduino IDE
2. Flash the MAC-Finder to both the boards and write down the MAC Address which will be sent in the Serial Monitor
3. In the indicator firmware file change the broadcast MAC address to the one the remote gave you
4. Flash!
5. Now in the remote firmware file change the broadcast MAC address to the one the indicator gave you
6. Flash!
7. Now the Indicator and Remote will connect to each other automatically

## Looks
![Indicator case](https://github.com/m1cha3l-s/remote-occupancy-indicator/blob/main/Pictures/Indicator%20-%20Case.png)

![Remote case](https://github.com/m1cha3l-s/remote-occupancy-indicator/blob/main/Pictures/Remote%20-%20Case.png)

## PCB/Schematic
![PCB](https://github.com/m1cha3l-s/remote-occupancy-indicator/blob/main/Pictures/PCB.png)

![Schematic](https://github.com/m1cha3l-s/remote-occupancy-indicator/blob/main/Pictures/Schematic.png)


### BOM
| Part Name | Quantity | Price (USD) | Total (USD) | Link |
|---|---|---|---|---|
| ESP32-C3 Super Mini | 2 | 3.16 | 6.32 | https://www.aliexpress.com/item/1005005834458965.html |
| 20pcs SK6812MINI-E | 1 | 1.75 | 1.75 | https://www.aliexpress.com/item/1005008308801366.html |
| 20PCS Tact Push Button Switch 12V Copper 4Pin SMD Micro Switch 6X6X5mm | 1 | 1.62 | 1.62 | 	https://www.aliexpress.com/item/1005005834458965.html |
| Aliexpress shipping | 1 | 2.55 | 2.55 | |
| Custom PCB (with shipping) | 1 | 4.24 | 4.24 | jlcpcb |
| 3D Printed case | 1 | 0 | 0 | none - I have my own printer |
| Total ||| 16.48 |
