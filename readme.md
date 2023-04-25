# Silver Box Modular HiFi Preamp

> __Note: This project is still very early in development. Features, functions, and interfaces are subject to change.__

The Silver Box Modular HiFi Preamp allows a person to choose the exact inputs and outputs that a user wants to have. It is common to need to combine or switch between many different sources which all need to go to a single playback source. For instance a person may have TOSLINK optical from their TV, RCA source from a turntable, and a balanced source from a USB audio interface. With this device, all of those can be accommodated and output to one set of speakers.

The chassis provides the analog signal routing, volume control, switching and indication. It is driven by an ESP32 so that functions can be controlled over WiFi, and eventually with smart home integration.

Peripherals are modular cards that can be slotted in to any of the available channels. Peripherals can be active or passive and can function as inputs, outputs, effects, visualizations, maybe more!

The chassis provides each peripheral with:

- Audio send to summing bus, main bus audio output, and audio out from left-adjacent module.
- Global mute and per peripheral muting.
- +/- 12V, +5V, +3.3V power rails.
- An I2C data interface with interrupt capabilities.
- Automatic identification of common module types with additional configuration possible over I2C.


# Current Status

__April 25 2023 Update:__ The project is currently in the __hardware prototyping__ phase. PCB's have been produced and are being assembled. Very close to beginning testing. A minimum viable product could be functional by end of May 2023.

Design files will be updated here as progress is made.

The current schematics are available in .pdf in the __ecad__ folder:

- [ecad/motherboard.pdf](ecad/motherboard.pdf)
- [ecad/controlboard.pdf](ecad/controlboard.pdf)
- [ecad/peripheral-example-board.pdf](ecad/peripheral-example-board.pdf)
- [ecad/prototype-power-supply.pdf](ecad/prototype-power-supply.pdf)

The current 3D models/assemblies for the project are available in .step format in the __mcad__ folder:

- [mcad/silver-box-modular_assembly.step](mcad/silver-box-modular_assembly.step)
- [mcad/motherboard.step](mcad/motherboard.step)
- [mcad/controlboard.step](mcad/controlboard.step)
- [mcad/peripheral-example-board.step](mcad/peripheral-example-board.step)

The BOM for this project is evolving and changing with the project. The current state of the BOM can be viewed at 

- [Motherboard](https://octopart.com/bom-tool/XiIWqOJY)
- [Peripheral test board](https://octopart.com/bom-tool/2ID8Y56N)
- [Protype power supply](https://octopart.com/bom-tool/b4PDtAU9)

Next steps:

- [ ] Bring docs up to date with current development state.
- [ ] Setup dev environment
- [ ] Document the mcad model and explain key features.
- [ ] Organize and refine the 3d prints that will be required for the prototype.
- [ ] Put together power supply module that will be used for early development.
  	- Board should have breakouts for external lab power option
  	- MCU for development and testing of I2C, power sequencing, power monitoring
  	- Polyfuse or other protection circuit. 
- [x] Create blank/passive modules for prototyping.
- [x] Synchronize/clean the Octopart BOM with the schematic.
- [x] Final review and production of prototype PCB's.

Farther out:

- 4 layer board after hardware features and form is frozen.
- Power supply design following findings learned from prototyping efforts.
- Expand available peripheral designs, active balanced I/O. Headphone amp output, S/PDIF digital input, VU 
- Integrate with MQTT for smart home capabilities. Eventual integration with commercial smart home systems.


# Concept sketches/renders:

![](docs/i/prototype_render_front.png)

![](docs/i/prototype_render_quarter.png)

![](sketches/concept_sketches_2023.02.01.png)

