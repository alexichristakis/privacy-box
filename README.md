# Behind Every Tap

A simple box with 7 eyes that look towards any side that is tapped. The enclosure is constructed out of laser-cut plywood, 3D printed mounting brackets, and wood glue. All fabrication files can be found under the fabrication folder.

![Finished box](assets/finished_box.jpeg)

## Fabrication

Because readily-available positionally-aware servos have a limited range of 180 degrees, the layout had to carefully consider the angle of each mounted servo to enable them to look at all 4 sides of the box. In the layout shown below, every servo has its available range directed towards the center of the box, with two extremes positioned at two adjacent sides.

While the original plan involved using either piezoelectric or vibration sensors to detect which side of the box the user tapped, it ultimately was too difficult to differentiate between the sensor's signals to determine which side was activated. Using an accelerometer, the box listens to it's horizontal and vertical acceleration to detect if it was tapped. One issue with this solution is that the deceleration of the box can outweigh the initial acceleration, leading to the code misreading the data as a tap from the opposite side. More careful thresholds and reading from the sensor would fix this issue.

### Layout

![Box layout](./assets/layout.png)

### Wiring

![Wiring diagram](./assets/wiring&#32;diagram.png)

The wiring diagram shows each mounted servo with a dashed circle representing the size and position of the eye it controls, as well as a dashed semi-circle depicting the available rotation. The 7 servos are connected to the ESP's pins 12, 13, 14, 25, 26, 27, and 33 for PWM position control. The accelerometer is powered from the 5V pin, and uses pins 2 and 15 for digital data transfer with help from the Wire library.

The servo mounts which secure the motors to the bottom plate of the box were designed in SketchUp and look like this:

![Servo mount](./assets/servo_mount.png)

Four connector pieces were also printed to secure the lid to the box in a removable way. They hold a nut in each side to make the construction easier.

![Connector](./assets/box_connector.png)