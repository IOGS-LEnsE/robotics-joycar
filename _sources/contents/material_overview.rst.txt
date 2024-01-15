Overview of the platform
========================

**Joy-It Car** is a platform ...

PICTURE OF THE SYSTEM



Materials
---------

GPIO Expander
~~~~~~~~~~~~~

The GPIO Expander is a PF574A. Its I2C address is 0x38.

Connections to the different sensors is given in the Joy-It Car manual.


PWM Controller for motors
~~~~~~~~~~~~~~~~~~~~~~~~~

The PWM controller and motor driver is a PCA9633. Its I2C address is 0x70.

Channels 2, 3, 4 and 5 are used for controlling left motor (channels 2 and 3) and right motor (channels 4 and 5).

|

An initialization phase is required : sending 2 bytes with values {0x00 0x01}, and then 2 other bytes with values {0xE8 0xAA} (procedure found in the micropython library examples given by Joy-It).
