#include <Arduino.h>

class Controller
{
    public:
        Controller(int motor_pin_ina, int motor_pin_inb, int pwm_pin);
        void spin(int pwm);

    private:
        int motor_pin_ina_;
        int motor_pin_inb_;
        int pwm_pin_;
};

Controller::Controller(int motor_pin_ina, int motor_pin_inb, int pwm_pin):

    motor_pin_ina_(motor_pin_ina),
    motor_pin_inb_(motor_pin_inb),
    pwm_pin_(pwm_pin)
{
    pinMode(motor_pin_ina_, OUTPUT);
    pinMode(motor_pin_inb_, OUTPUT);
    pinMode(pwm_pin_, OUTPUT);

    //ensure that the motor is in neutral state during bootup
    analogWrite(pwm_pin_, abs(0));
}

void Controller::spin(int pwm)
{

    if(pwm > 0)
    {
        digitalWrite(motor_pin_ina_, HIGH);
        digitalWrite(motor_pin_inb_, LOW);
    }
    else if(pwm < 0)
    {
        digitalWrite(motor_pin_ina_, LOW);
        digitalWrite(motor_pin_inb_, HIGH);
    }
   
    analogWrite(pwm_pin_, abs(pwm));

}
