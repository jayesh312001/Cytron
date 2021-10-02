#ifndef CYTRON_H
#define CYTRON_H

#include "Arduino.h"

#define DUMMY_BIT 128
#define HEADER 85

enum
{
    ANALOG,
    SERIAL_SIMPLIFIED,
    SERIAL_PACKETIZED
};

class Cytron
{
public:
    // Constructor for the cytron class
    Cytron(uint8_t mode, uint8_t anPin, uint8_t inPin);                     // For PWM Independent mode
    Cytron(uint8_t mode, Stream *stream, uint8_t channel);                  // For Serial Simplified mode
    Cytron(uint8_t mode, Stream *stream, uint8_t address, uint8_t channel); // For Serial Packetized mode
    // Function to send the dummy bit
    void send_dummy_bit(void);
    void clockwise(uint8_t pwm);
    void anti_clockwise(uint8_t pwm);
    void brake(void);

private:
    uint8_t _mode;
    uint8_t _inPin;
    uint8_t _anPin;

    Stream *_stream;
    uint8_t _dummy_bit = DUMMY_BIT;
    void send_data(uint8_t speed);
    uint8_t _channel;

    uint8_t _address;
    uint8_t _packet[4] = {HEADER, 0, 0, 0};
};

#endif