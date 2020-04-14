//Including the library that will help us in receiving and sending the values from processing
#include <VSync.h>
ValueReceiver<1> receiver;  // Receiver Object
ValueSender<1> sender;      // Sender Object

// The below variables will be syncronized with the Processing and they should be same on the both sides.
int output;
int input;

int ledPin = 13; //LED Pin

void setup()
{
  /* Starting the serial communication because we are communicating with the
    Arduino through serial. The baudrate should be same as on the processing side. */
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  // Synchronizing the variables with the processing. The variables must be int type.
  receiver.observe(output);
  sender.observe(input);
}

void loop()
{
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
    input = 2;
  }
  sender.sync();
}
