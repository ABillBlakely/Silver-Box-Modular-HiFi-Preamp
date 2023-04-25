# Connector Interface

The Silver Box Modular HiFi Preamp allows a user to swap cards, called peripherals, to facilitate a wide variety of desired input and output combinations. The controller provides the ability to mute individual inputs and provides volume control. The modular interface relies on a 36 pin PCI card edge connector. This connector supplies the peripheral with power, ID's the peripherals function, allows digital communications, and connects the stereo audio to three connection points, described below.


# Audio Send/Receive

Each module has one send and two receives available. Each of these endpoints is a stereo connection.

* __POMI__ Peripheral Out Master In: This sends audio that comes in from an external connector out to the master bus. The controller provides the facility to mute each individual stereo pair sent to POMI. All POMI sends are summed together and sent to the volume control.

* __MOPI__ Master Out, Peripheral In: The signal from the volume control is fed out to every module. Every module sees the same summed signal simultaneously. This means that multiple output peripherals can be installed, but the controller will not be able to select between them. If this behavior is req'd, an advanced output peripheral that includes muting/volume control plus I2C communication should be used.

* __AOPI__ Adjacent Out, Peripheral In: This signal ties to POMI signal of the left-hand adjacent module. It does not go through the buffer, muting, summing, or volume control; it is the raw unbuffered signal from that module. It can be used for a variety of cases such as Input VU meter, Input EQ/Trim, or as a way to bypass the controller board and feed an output module directly. 


# Power

There are 4 power rails available:

* +/-15 V supply is intended to be the analog power supply and should to be used to power any active audio components on the board. 
* 5 V and 3.3 V supplies are intended primarily to power digital devices, These can be used for audio purposes but are generally much noisier. The 5V rail should also be used to pull up the ID pins.

Each power rail has a separate ground return pin on the connector and care should be taken to maintain good routing of these return paths. 

# ID3:0

The ID pins are used to pass basic information about the peripheral back to the controller. This allows for automatic configuration and adaptation of the user interface when a peripheral is swapped. For example, the input button will not select peripherals that do not set the Is_input ID bit. More advanced peripherals can communicate over I2C for additional configuration, but should still communicate as much info as possible over the ID pins. 

> __Note 1: The ID Bit definition is a work in progress and subject to change.__

<!-- I'm not sure if I like "...not output or does not receive...". I might need to include output / not output as well, this could be done without multi state id's by merging USE I2C to the ~INT pin, See Note 2. This decision really comes down to: does the controller need to know what is and is not a simple output.-->

IDN: Low / High

ID0: Sends to POMI (is an input) / No Send (is not an input)

ID1: Receive from AOPI, is output (Ex: controller bypass)/ Receive from AOPI, is not output (ex: Input VU) OR does not receive from AOPI

ID2: Receives from MOPI (is output) / Receive from MOPI but not output (ex: out VU) OR does not receive from MOPI

ID3: Uses I2C / does not use I2C


For instance, the special case of all "high" values could be used in the case of an input VU meter. It receives the unbuffered audio from the adjacent peripheral and visualizes the levels of the input with an led bar graph.

In the future, ID pins may be multi state to allow configuration of more options so to maintain future compatibility ID pins should be strongly pulled up or down. 

# I2C

The controller allows for I2C communication to establish more advanced behavior. As the controller firmware matures, more advanced features will be added to the peripherals. 

The controller I2C bus is multiplexed so each peripheral has a dedicated I2C channel. This prevents any potential conflict in addresses between boards. 

When a peripheral is detected with the "Use I2C" ID pin set, the full address space is scanned to detect all available I2C endpoint addresses. peripherals must set an interrupt in order to send information back to the controller. 

Peripheral/controller communication will function based on a subscribe/notify style of communication. 


# Special Note: Peripheral insertion detection with ~INT and ID3

In the special case where a peripheral is configured with ID3:0 == 1111, it is not possible to determine whether a slot is empty or occupied. For this reason the controller relies on the ~INT pin being pulled low to indicate that a peripheral is inserted. The controller will then scan the ID bits, If  "Use I2C" Bit is also low, the controller will look for a message: a configuration message will indicate a new peripheral and any other message will indicate an unchanged peripheral. If the "Use I2C" bit is high, this will also indicate a new peripheral, and the controller will initialize the new peripheral. 

__In other words, peripherals not using I2C should pull ~INT low, and peripherals with I2C should send an interrupt on power up.__


> __Note 2: ID3 and ~INT could be combined, an ~INT that stays low would indicate no I2C use, and an ~INT the is triggered and then goes high would indicate I2C use. interrupts would need to be under 50ms or something.__

