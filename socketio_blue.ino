//Including the library that will help us in receiving and sending the values from processing
#include <VSync.h>
ValueReceiver<1> receiver;  // Receiver Object
ValueSender<1> sender;      // Sender Object
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

// The below variables will be syncronized with the Processing and they should be same on the both sides.
int output;
int input;

int ledPin = 13; //LED Pin

void setup()
{
  /* Starting the serial communication because we are communicating with the
    Arduino through serial. The baudrate should be same as on the processing side. */
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Goodnight moon!");
  
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
  
  pinMode(ledPin, OUTPUT);

  // Synchronizing the variables with the processing. The variables must be int type.
  receiver.observe(output);
  sender.observe(input);
}

void loop()
{
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
  
  // Receiving the output from the processing.
  receiver.sync();

  // Matching the received output to light up LED
  if (output == 1)
  {
    digitalWrite(ledPin, HIGH);
    input = 1;
  }
  else if (output == 2)
  {
    digitalWrite(ledPin, LOW);
    //input = 2;
    input = outputValue;
  }
  sender.sync();

  delay(100);
}
