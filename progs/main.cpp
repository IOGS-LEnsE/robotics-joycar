/**
 * FILENAME :        main.cpp          
 *
 * DESCRIPTION :
 *       Testing Joy-It Car Control system based on Nucleo Board
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    15/jan/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

#include "mbed.h"
#include "JoyCar.h"

/// Internal boolean print function
void printbool(bool v, char* name);

/// I2C interface
I2C  my_i2c(D14, D15);

/// Motor driver
JoyCar_Motor    my_motor(&my_i2c);

/// Distance sensor mounted on a servomotor
JoyCar_ServoDist my_dist(D6);

/// Headlights
JoyCar_HeadLights my_lights(D8);

/// JoyCar inputs/outputs declaration - based on Joy-It Car platform
Ticker controlLoopTik;


/* Methods */
/**
 * Interrupt routine attached to the sampling of the Contol Loop System
 *
 * @return Updates the system control loop outputs
 */
void ISR_controlLoopTik(void);

/* Main code */
int main()
{
    // Initialization
    printf("Robot Init...\r\n");

    /// Distance Servomotor
    //my_dist.initServo();
    
    /// PWM Driver init
    printbool(my_motor.initPWMController(), "Init Motor");


    controlLoopTik.attach(&ISR_controlLoopTik, 100us);

    /// Headlights
    printf("LEDs OK...\r\n");
    my_lights.setAllLights(100, 0, 50);


    while (true){       
        printbool(my_motor.goForward(70, 0), "\tGo Forward");
        my_lights.setAllLights(0, 0, 50);
        wait_us(1000000);
        printbool(my_motor.stopSoft(), "\tStop");
        my_lights.setAllLights(100, 0, 0);
        wait_us(1000000);
        printbool(my_motor.goReverse(0, 100), "\tGo Reverse");
        my_lights.setAllLights(0, 100, 0);
        wait_us(1000000);
        printbool(my_motor.stopSoft(), "\tStop");
        my_lights.setAllLights(100, 0, 0);
        wait_us(1000000);
    }
}


/* */
void ISR_controlLoopTik(void){


}



/// Internal boolean print function
void printbool(bool v, char* name){
    if(v == true)
        printf("%s = True \r\n", name);
    else
        printf("%s = False \r\n", name);
    
}