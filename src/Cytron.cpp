#include "Cytron.h"

Cytron::Cytron(uint8_t mode, uint8_t inPin, uint8_t anPin)
{
  _mode = mode;
  _anPin = anPin;
  _inPin = inPin;

  pinMode(inPin, OUTPUT);
  pinMode(anPin, OUTPUT);
}

Cytron::Cytron(uint8_t mode, Stream *stream, uint8_t channel)
{
  _mode = mode;
  _stream = stream;
  _channel = channel;
}

Cytron::Cytron(uint8_t mode, Stream *stream, uint8_t address, uint8_t channel)
{
  _mode = mode;
  _stream = stream;
  _address = address;
  _channel = channel;
}

void Cytron::send_dummy_bit(void)
{
  _stream->write(128);
  delay(500);
}

void Cytron::clockwise(uint8_t pwm)
{
  switch (_mode)
  {
  case ANALOG:
    analogWrite(_anPin, pwm);
    digitalWrite(_inPin, LOW);
    break;

  case SERIAL_SIMPLIFIED:
    pwm = (_channel << 7 | 0b00000000 | map(pwm, 0, 255, 0, 63));
    _stream->write(pwm);
    break;

  case SERIAL_PACKETIZED:
    pwm = map(pwm, 0, 255, 127, 255);
    this->send_data(pwm);
    break;
  }
}

void Cytron::anti_clockwise(uint8_t pwm)
{
  switch (_mode)
  {
  case ANALOG:
    analogWrite(_anPin, pwm);
    digitalWrite(_inPin, HIGH);
    break;

  case SERIAL_SIMPLIFIED:
    pwm = (_channel << 7 | 0b01000000 | map(pwm, 0, 255, 0, 63));
    _stream->write(pwm);
    break;

  case SERIAL_PACKETIZED:
    pwm = map(pwm, 0, 255, 127, 0);
    this->send_data(pwm);
    break;
  }
}

void Cytron::brake(void)
{
  switch (_mode)
  {
  case ANALOG:
    analogWrite(_anPin, 0);
    digitalWrite(_inPin, LOW);
    break;

  case SERIAL_SIMPLIFIED:
    _stream->write(_channel << 7 | 0b00000000);
    break;

  case SERIAL_PACKETIZED:
    this->send_data(127);
    break;
  }
}

void Cytron::send_data(uint8_t speed)
{
  _packet[1] = (_channel << 3) | _address;
  _packet[2] = speed;
  _packet[3] = _packet[0] + _packet[1] + _packet[2];

  for (uint8_t i = 0; i < 4; i++)
  {
    _stream->write(_packet[i]);
  }
}
