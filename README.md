## Wattmeter

Based on AK3Y's wattmeter published in QSL magazine.

See license in `main.cpp` for code.  Some other files (like the font) are licensed separately.

Build variances:
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

Build notes:
1. Assemble the heatsink, RF PCB, and flange resistor prior to soldering
2. Use 4x 6mm M3 screws to hold the PCB to the heatsink
3. Use 4x 15mm~6mm M3 standoffs as if they were nuts to hold the RF PCB to the case via 4x 8mm M3 screws
4. Use 4x M3 lock nuts to hold the Pico PCB to the M3 standoffs
5. Use 2x 6mm M2 screws to hold the flange resistor to the heatsink
6. Use 4x 8mm M2 screws and M2 lock nuts to hold the OLED display in place - be gentle on the board
7. Use 4x 6mm M2 screws to assemble the rest of the case