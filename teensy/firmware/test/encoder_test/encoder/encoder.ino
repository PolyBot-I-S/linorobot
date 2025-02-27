//Encoder pins definition

/*  BOOK VALUES
// Left encoder

int Left_Encoder_PinA = 2;
int Left_Encoder_PinB = 9;

volatile long Left_Encoder_Ticks = 0;

//Variable to read current state of left encoder pin
volatile bool LeftEncoderBSet;

//Right Encoder

int Right_Encoder_PinA = 3;
int Right_Encoder_PinB = 10;*/

int Left_Encoder_PinA = 35;
int Left_Encoder_PinB = 36;

volatile long Left_Encoder_Ticks = 0;

//Variable to read current state of left encoder pin
volatile bool LeftEncoderBSet;

//Right Encoder

int Right_Encoder_PinA = 2;
int Right_Encoder_PinB = 3;

volatile long Right_Encoder_Ticks = 0;
//Variable to read current state of right encoder pin
volatile bool RightEncoderBSet;


void setup()
{
  //Init Serial port with 115200 buad rate
  Serial.begin(115200);  
  SetupEncoders();
}


void SetupEncoders()
{
  // Quadrature encoders
  
  pinMode(Left_Encoder_PinA, INPUT);      // sets pin A pullup
  pinMode(Left_Encoder_PinB, INPUT);      // sets pin B pullup
  //attachInterrupt(digitalPinToInterrupt(Left_Encoder_PinA), do_Left_Encoder, RISING);
  attachInterrupt(Left_Encoder_PinA, do_Left_Encoder, RISING);
  

  // Right encoder
  pinMode(Right_Encoder_PinA, INPUT);      // sets pin A pullup
  pinMode(Right_Encoder_PinB, INPUT);      // sets pin B pullup

  //attachInterrupt(digitalPinToInterrupt(Right_Encoder_PinA), do_Right_Encoder, RISING); 
  attachInterrupt(Right_Encoder_PinA, do_Right_Encoder, RISING); 
}

void loop()
{
  //delay(500);
  Update_Encoders();
  delay(10);
}


void Update_Encoders()
{
  Serial.print("e");
  Serial.print("\t");
  Serial.print(Left_Encoder_Ticks);
  Serial.print("\t");
  Serial.print(Right_Encoder_Ticks);
  Serial.print("\n");
 }

 void do_Left_Encoder()
{
//  Serial.print("LEFT ");
//  Serial.println(Left_Encoder_Ticks);
  LeftEncoderBSet = digitalRead(Left_Encoder_PinB);   // read the input pin
  Left_Encoder_Ticks += LeftEncoderBSet ? -1 : +1;
   
}
void do_Right_Encoder()
{
//  Serial.print("RIGHT: ");
//  Serial.println(Right_Encoder_Ticks);
  RightEncoderBSet = digitalRead(Right_Encoder_PinB);   // read the input pin
  Right_Encoder_Ticks += RightEncoderBSet ? -1 : +1;
 }
