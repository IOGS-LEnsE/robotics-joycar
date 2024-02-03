Overview of the platform
========================

**Joy-It Car** is a platform ...

PICTURE OF THE SYSTEM



Materials
---------

GPIO Expander
-------------

The GPIO Expander is a PF574A. Its I2C address is 0x38.

Connections to the different sensors is given in the Joy-It Car manual.


PWM Controller for motors
-------------------------

The PWM controller and motor driver is a PCA9633. Its I2C address is 0x70.


Initialization of the PWM driver
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

An initialization phase is required : sending 2 bytes with values {0x00 0x01}, and then 2 other bytes with values {0xE8 0xAA} (procedure found in the micropython library examples given by Joy-It).

PWM Channels
~~~~~~~~~~~~

Each motor of the JoyCar platform uses 2 PWM channels of the PCA9633 to be controlled in two directions.

.. flat-table:: PCA9633 PWM channels
   :widths: 20 20 20
   :header-rows: 1

   * - Motor
     - PWM Channel
     - Reg Address
   * - :rspan:`1` Right
     - PWM0
     - 0x02
   * - PWM1
     - 0x03
   * - :rspan:`1` Left
     - PWM2
     - 0x04
   * - PWM3
     - 0x05

Depending on the direction and the speed, you can affect value as mentionned in the next table (from Joy-It JoyCar documentation) :

.. flat-table:: Driving control of the JoyCar platform
   :widths: 20 20 20 20 20
   :header-rows: 2

   * - 
     - :cspan:`1` RIGHT Motor
     - :cspan:`1` LEFT Motor
   * - Function
	 - PWM0
     - PWM1
     - PWM2
     - PWM3
   * - Strong Braking
	 - 0
     - 0
     - 0
     - 0
   * - Soft Braking
	 - 255
     - 255
     - 255
     - 255
   * - Go Forward
	 - 0
     - PWM
     - 0
     - PWM
   * - Go Reverse
     - PWM
     - 0
     - PWM
	 - 0
   * - Turn Left
	 - 0
	 - 0
     - 0
     - PWM