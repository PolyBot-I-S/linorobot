// Read in 12-bits Magnetic Encoder AEAT-6012-A06  into Arduino Nano
// RobinL modified by linarism, isircu

#include <Arduino.h>

class MagEncoder
{
    public:
        MagEncoder(int enc_pin_do, int enc_pin_clk, int enc_pin_csn);
        float getAngle();

    private:
        int enc_pin_do_;
        int enc_pin_clk_;
        int enc_pin_csn_;
        float angle_scalar_;
};

//Controller::Controller(driver motor_driver, int pwm_pin, int motor_pinA, int motor_pinB):
MagEncoder::MagEncoder(int enc_pin_do, int enc_pin_clk, int enc_pin_csn):

    enc_pin_do_(enc_pin_do),
    enc_pin_clk_(enc_pin_clk),
    enc_pin_csn_(enc_pin_csn),
    
    //num_bits_(num_bits),
    angle_scalar_(pow(2.0, 12))

{
    pinMode(enc_pin_do_, INPUT);
    pinMode(enc_pin_clk_, OUTPUT);
    pinMode(enc_pin_csn_, OUTPUT);

    //Start here
    digitalWrite(enc_pin_clk_, HIGH);
    digitalWrite(enc_pin_csn_, HIGH);
}


float MagEncoder::getAngle(){
  unsigned int dataOut = 0;

  digitalWrite(enc_pin_csn_, LOW);
  delayMicroseconds(1); //Waiting for Tclkfe

  //Passing 12 times, from 0 to 11
  for(int x=0; x<12; x++){
    digitalWrite(enc_pin_clk_, LOW);
    delayMicroseconds(1); //Tclk/2
    digitalWrite(enc_pin_clk_, HIGH);
    delayMicroseconds(1); //Tdo valid, like Tclk/2
    dataOut = (dataOut << 1) | digitalRead(enc_pin_do_); //shift all the entering data to the left and past the pin state to it. 1e bit is MSB
  }

  digitalWrite(enc_pin_csn_, HIGH); //deselects the encoder from reading

  float angle = 360.0 / angle_scalar_ * dataOut;
  return angle;

}
