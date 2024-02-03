/**
 * FILENAME :        JoyCar.cpp          
 *
 * DESCRIPTION :
 *       Direct Current Motor control by a standard H-bridge (L293/L298)
 *
 *       This library gives function to control a Direct Current Motor by
 *  a standard H-bridge (type L293 or L298)
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    19/jan/2023
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */


#include    "JoyCar.h"
#include <cstdint>


JoyCar_Motor::JoyCar_Motor(I2C *_i2c){
    /* Initialisation of i2c module */
    if (_i2c){ delete __i2c; }
    __i2c=_i2c;
    __i2c->frequency(JOYCAR_I2C_FREQ);
    thread_sleep_for(100);      // 100 ms
}


bool JoyCar_Motor::initPWMController(){
    uint8_t ack = -1;
    // Initialization
    char cmd[] = {0, 1};
    /*
    cmd[0] = 0x00;
    cmd[1] = 0x01;
    */
    ack = this->__i2c->write( JOYCAR_MOTOR_ADD << 1, cmd, 2 );
    if(ack != 0)    return false;
    thread_sleep_for(10);      // 10 ms
    
    cmd[0] = 0xE8;
    cmd[1] = 0xAA;
    ack = this->__i2c->write( JOYCAR_MOTOR_ADD << 1, cmd, 2 );
    if(ack != 0)    return false;
    return true;
    thread_sleep_for(10);      // 10 ms
}

bool JoyCar_Motor::sendSpeed(uint8_t ch_add, char val){
    uint8_t ack = -1;
    char cmd[2];
    cmd[0] = ch_add;
    cmd[1] = val;
    ack = this->__i2c->write( JOYCAR_MOTOR_ADD << 1, cmd, 2 );
    
    if(ack != 0)    return false;  
    else{
        thread_sleep_for(10);      // 10 ms
        return true;  
    }    
}

bool JoyCar_Motor::goForward(uint8_t speedR, uint8_t speedL){
    bool ack = false;
    uint8_t r_speed = speedR * 2.55;
    uint8_t l_speed = speedL * 2.55;
    // Right motor
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM0_REG, 0);
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM1_REG, r_speed);
    printf("\t\tSR = %d \r\n", r_speed);
    // Left motor
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM2_REG, l_speed);
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM3_REG, 0);
    thread_sleep_for(10);      // 10 ms
    return ack;
}


bool JoyCar_Motor::goReverse(uint8_t speedR, uint8_t speedL){
    bool ack = false;
    uint8_t r_speed = speedR * 2.55;
    uint8_t l_speed = speedL * 2.55;
    // Right motor
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM0_REG, r_speed);
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM1_REG, 0);
    // Left motor
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM2_REG, 0);
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM3_REG, l_speed);
    thread_sleep_for(10);      // 10 ms
    return ack;
}

bool JoyCar_Motor::stopSoft(void){
    bool ack = false;
    // Right motor
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM0_REG, 0);
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM1_REG, 0);
    // Left motor
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM2_REG, 0);
    ack = ack || this->sendSpeed(JOYCAR_MOTOR_PWM3_REG, 0);
    thread_sleep_for(10);      // 10 ms
    return ack;
}

JoyCar_ServoDist::JoyCar_ServoDist(PinName _servPWM): __servo(_servPWM) {
    __servo.period_ms(20);
    __servo.pulsewidth_us(1500);    // central value - Speed = 0
}

void JoyCar_ServoDist::initServo(void){
    __servo.pulsewidth_us(1500);
}


JoyCar_HeadLights::JoyCar_HeadLights(PinName _leds): __led_in(_leds), __my_strip(_leds, NB_OF_LEDS){
    this->__my_strip.set_timings(6, 13, 14, 5); // Specific to L476RG
    this->__my_strip.break_trame();
    
    /// Power off all the lights
    for(int ik = 0; ik < NB_OF_LEDS; ik++){
        this->_array[ik] = 0;
    }
    this->__my_strip.break_trame();
    this->__my_strip.send_leds(this->_array);
}

int JoyCar_HeadLights::convertPixel(uint8_t r, uint8_t g, uint8_t b){
    return (g << 16) + (r << 8) + b;
}

void JoyCar_HeadLights::setAllLights(uint8_t R, uint8_t G, uint8_t B){
    int color = convertPixel(R, G, B);
    /// Set the same color to all the lights
    for(int ik = 0; ik < NB_OF_LEDS; ik++){
        this->_array[ik] = color;
    }
    this->__my_strip.break_trame();
    this->__my_strip.send_leds(this->_array);
}