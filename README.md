## Wattmeter

Based on AK3Y's wattmeter published in QSL magazine.

See license in `main.cpp` for code.  Some other files (like the font) are licensed separately.

### Differences from previous designs
1. Built to run upside-down (heatsink up)
2. Changed to use a Pi Pico 2 to reduce BOM cost
3. Added some built-in standoffs to case
4. Added new holes for USB, and for optional PowerPoles
5. Changed dimensions of PCB and drill/tap locations for heatsink
6. Used 128x64 OLED from AliExpress which did not match datasheet / original dimensions at all
7. Changed microstrip width based on recommendation from calculator
8. I used connectors for everything, but you could just solder the wires in
9. Changed other dimensions of case cutouts
10. Used mostly different parts from original design

### Printing
Try to orient the parts so the smooth side faces out.
1. Print bottom shell normally.
2. The top shell should be rotated 180 degrees for better printing.
3. Front and back panels should be oriented so the "outside" of each plate faces the build plate for a smooth finish.

### Assembly

#### Parts Required

| ID      | Description                   | QTY | Optional QTY |
|---------|-------------------------------|-----|--------------|
| PCB1    | RF PCB                        | 1   |              |
| PCB2    | Pico PCB                      | 1   |              |
| A1      | Raspberry Pi Pico 2           | 1   |              |
| A2      | SSD1306 128x64 I2C OLED       | 1   |              |
| C1      | 10nF 1206 Cer. Cap.           | 1   |              |
| C2      | 1nF 1206 Cer. Cap.            | 1   |              |
| C3      | 10uF 35V 5mm Elec. Cap.       |     | 1            |
| C4      | 47uF 35V 5mm Elec. Cap.       |     | 1            |
| D1-2a,b | TMMBAT41FILM 100V Diode       | 3   |              |
| D3      | PBZTBR13.0B Zener Diode       | 1   |              |
| D4      | 1N5819                        |     | 1            |
| HS1     | 60x45x18mm heatsink           | 1   |              |
| J1      | SMA board-edge connector      | 1   |              |
| J2      | JST-XA BM02B-XASS-TF          | 1   |              |
| J3-4    | JST-XA B02B-XASK-1            | 1   | 1            |
| J5      | 1x4 2.54mm Breakaway Hdr.     | 1   |              |
| R1      | RFR 50-250 Flange Resistor    | 1   |              |
| R2      | 100K 1206 Resistor            | 1   |              |
| R3      | 3K 1206 Resistor              | 1   |              |
| R4      | DNP                           |     |              |
| TH1     | DNP                           |     |              |
| U1      | UA7805                        |     | 1            |
| VR1     | 100K PT10WV05-104A2020-3-NE-S | 1   |              |

#### Cable Assemblies
Cable assemblies assume Pin 1 of a connector is the RIGHTMOST contact if you are looking at the connector's contact end, with the latch facing UP.
Cut wires to the length indicated, then strip and crimp them.

1. 5" Inter-PCB Wire
   1. JST-XA connectors
   2. RF PCB side: Pin 1 is red, Pin 2 is black
   3. Pico PCB side: Pin 1 is black, Pin 2 is red
   4. Pins 1 and 2 are reversed on either board
2. 2.5" PowerPole Wire (optional)
   1. JST-XA connector and PowerPole connector
   2. Pico PCB side: Pin 1 is red, Pin 2 is black
3. 3.5" OLED Wire (DuPont/Molex)
   1. Connectors are symmetrical
   2. Try to use a marked or black conductor for GND
    

#### Tools Needed
1. Crimping tool for JST & DuPont connectors
2. Crimping tool for PowerPole connectors
3. Drill bits and taps for M2 and M3 screw holes
4. Wire cutters, strippers, pliers
5. Metric allen key / screwdriver / wrench / socket for M2/3 screws and nuts
6. Soldering iron with solder, flux, and solder-wick
7. 3D printer if printing your own case

#### Steps
1. Assemble the heatsink, RF PCB, and flange resistor prior to soldering anything.
   1. Use 4x 6mm M3 screws to hold the PCB to the heatsink
   2. Use 2x 6mm M2 screws to hold the flange resistor to the heatsink
   3. Make sure the flange resistor tab rests on/above the PCB pad for it
2. Soldering the RF PCB
   1. Use flux liberally
   2. The pads for diodes were designed for larger diodes, but many will fit fine
3. Soldering the Pico PCB
   1. Parts U1, C3, C4, D4, and J4 may be omitted if you do not want an external power supply other than USB
   2. D4 is a very tight fit
   3. Use flux to help solder the Pico 2
   4. R4 and Thermistor are optional in case you want to have a Thermistor (you will need to code this in)
4. Installing the PCBs
   1. Insert 4x 8mm M3 screws into the screw holes on the "top" shell from the outside
   2. Place the RF PCB into the "top" shell with the heatsink going through the big hole, and the SMA adapter through the small side hole, aligned with the M3 screws
   3. Attach 4x 15mm~6mm M3 hex standoffs (female side) to the M3 screws to hold the RF PCB down
   4. Attach one end of the inter-PCB wire to the RF PCB
   5. Place the Pico PCB onto the M3 hex standoffs (male side) so that the potentiometer and BOOTSEL button align to the holes when the "bottom" shell is placed onto the "top" shell
   6. Use 4x M3 lock nuts to hold the Pico PCB to the M3 standoffs
   7. Attach the other end of the inter-PCB wire to the Pico PCB
5. Assembling the OLED panel
   1. Mark on the top edge of the OLED panel above the GND pin
   2. Use 4x 8mm M2 screws and M2 lock nuts to hold the OLED display in place on the front panel - be gentle with the PCB
   3. Place the OLED display panel so the connector is above the Pico PCB
   4. Attach the OLED wire between the display and the PCB
6. Assembling the Power/USB panel
   1. Install the PowerPole connector
   2. File the hole for the PowerPole connector if needed
   3. Use glue to secure the PowerPole connector if desired
   4. Place the Power/USB panel so the PowerPole connector is above the Pico PCB
   5. Attach the PowerPole wire to the PCB
7. Assemble the top of the case
   1. Place the "bottom" shell on the assembly
   2. Affix with 4x 6mm M2 screws
