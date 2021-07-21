# CheckersRobots

Het checkersRobot project is een damrobot gemaakt met een **Raspberry pi** en **Arduino Uno**, waarbij een Raspberry pi de hoofd controller is. De Arduino stuur de motoren aan door [GRBL](https://github.com/grbl/grbl)  software.

 raspberry pi die over usb G-code naar de Arduino Uno stuurd. Door de verstuurde G-code beweegt de arm naar de vakjes op het dambord.

## G-code

**G-code** is staat voor "Geometric Code" en wordt onderandere gebruikt in cnc (Computerized Numerical Control) machines.
G-code is wordt gebruikt om om de schaakstukken naar de juist plek te verplaats.

Beweeg naar het punt(0,0) met maximale snelheid
```Gcode
G90G0X0Y0
```

Beweeg naar een nieuw relative punt X20 Y20
```Gcode
G21G91X20Y20F127000
```
