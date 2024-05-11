# Arduino RC Car

License: Attribution-NonCommercial 4.0 International

For commercial use, please contact us at hey@toys.engineering with a description of your project and how you plan to use this project.

## Getting Started

The Arduino RC Car project allows you to control any model/toy/robot with servo and brushed DC motors. It can be used for RC cars and other vehicles such as trains, city layouts, boats, etc.

The easiest way to get started is to use the [Loco.Engineering car module](https://loco.engineering/products/rc-car-electronics/remote-control-car-module-for-arduino), which includes 2 DC motor drivers, an audio amplifier, WiFi/BLE connectivity, Drop Up voltage converter, and can control multiple servo motors. If you prefer to build your own hardware, check the advice in the "Custom board" section below.

The project consists of 2 subprojects (subfolders):

- A car controller - the firmware that should be uploaded to a board installed in a car/vehicle
- A remote controller - the firmware that should be uploaded to a board used in the remote controller

## How to Upload the Firmware

- Install Arduino IDE
- Connect your board to a computer
- Open the ".ino" files in the "car_controller" and "remote_controller" folders in the Arduino IDE. "car_controller" should be uploaded to your vehicle, and "remote_controller" should be uploaded to a board used in the remote controller
- Set the GPIOs you use on your boards (only required for custom boards; Loco.Engineering boards should work out of the box)
- Upload the projects to the boards

## Custom Board

If you prefer not to use the Loco.Engineering car module, you can make your own car board from development boards available on the market. Here's what you need:

#### For a Car Board
- ESP32-S3, ESP32-C3, ESP32-C6 based development boards with a built-in battery charging module
- BDC motor driver connected
- Drop Up voltage converter from 2.7V - 5V to 5V (only if you want to use a servo motor)

#### For a Remote Controller
- ESP32-S3, ESP32-C3, ESP32-C6 based development boards with a built-in battery charging module
- 2 joysticks with analog signals per axis
- A battery (optional)

#### How to Use a Custom Board
- Connect all development boards together
- Set the GPIOs you use on your boards (see car_controller.ino and remote_controller.ino)
- Upload firmware to your board

Feel free to contact us at hey@loco.engineering if you have any questions or feedback.
