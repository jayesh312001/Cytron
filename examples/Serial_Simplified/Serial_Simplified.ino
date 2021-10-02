#include <Cytron.h>

#include <Cytron.h>

Cytron c1(SERIAL_SIMPLIFIED, &Serial3, 1);
void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
  c1.clockwise(255);
  delay(1000);
  c1.anti_clockwise(255);
  delay(1000);
}
