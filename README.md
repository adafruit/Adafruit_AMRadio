# Adafruit_AMRadio
AM radio-transmit from M0 microcontrollers: Circuit Playground Express (not 'classic'), Feather M0, Arduino Zero, etc. Requires latest Adafruit_ZeroDMA library.

Gator-clip antenna to pin A0. Tune receiver to lower frequencies in AM band (examples use 540 KHz by default).

Uses Timer/Counter 5 and DAC. Speaker output will be disabled. DMA driven; interrupts, delay() and millis(), NeoPixels, etc. are all available.
