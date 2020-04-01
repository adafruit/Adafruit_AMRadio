# Adafruit AMRadio [![Build Status](https://github.com/adafruit/Adafruit_AMRadio/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/Adafruit_AMRadio/actions)

AM radio-transmit from M0 microcontrollers: Circuit Playground Express (not 'classic'), Feather M0, Arduino Zero, etc. Requires latest Adafruit_ZeroDMA library.

## Wiring
Connect antenna to pin A0 (a gator-clip jumper wire works fine). Tune receiver to lower frequencies in AM band (examples use 540 KHz by default). **RANGE IS LIMITED TO A FEW INCHES**, so don't take this too seriously, simply a fun science project kind of thing. A proper antenna for this frequency would be impractically long, *hundreds* of feet, and transmit power from the microcontroller pin is extremely limited anyway.

Tutorial is located here:
https://learn.adafruit.com/circuit-playground-express-dac-hacks

### Notes
Uses Timer/Counter 5 and DAC. Speaker output will be disabled. DMA driven; interrupts, delay() and millis(), NeoPixels, etc. are all available.

Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!

# Dependencies

* [Adafruit_ZeroDMA](https://github.com/adafruit/Adafruit_ZeroDMA)

# Contributing

Contributions are welcome! Please read our [Code of Conduct](https://github.com/adafruit/Adafruit_AMRadio/blob/master/CODE_OF_CONDUCT.md>)
before contributing to help this project stay welcoming.

## Documentation and doxygen
Documentation is produced by doxygen. Contributions should include documentation for any new code added.

Some examples of how to use doxygen can be found in these guide pages:

https://learn.adafruit.com/the-well-automated-arduino-library/doxygen

https://learn.adafruit.com/the-well-automated-arduino-library/doxygen-tips

Written by Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.

MIT license, all text above must be included in any redistribution

To install, use the Arduino Library Manager and search for "Adafruit AM radio library" and install the library.
