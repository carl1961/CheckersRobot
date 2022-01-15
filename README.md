# CheckersRobots

The checkersRobot project is a draughts robot made with a **Raspberry pi** and **Arduino Uno**, where a Raspberry pi is the main controller. The Arduino controls the motors by G-code [GRBL](https://github.com/grbl/grbl)  software.

 Raspberry Pi that sent over USB G code to the Arduino Uno. The sent G-code moves the arm to the boxes on the checkerboard.

## G-code

**G-code** stands for "Geometric Code" and is used in cnc (Computerized Numerical Control) machines.
G-code is used to move the chess pieces to the right place.

Move to the point(0.0) at maximum speed
'''Gcode
G90G0X0Y0
```

Move to a new relativ point X20 Y20
'''Gcode
G21G91X20Y20F127000
```
