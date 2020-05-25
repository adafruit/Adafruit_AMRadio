/*!
 * @file Adafruit_AMRadio.h
 *
 * DMA-driven AM radio-transmit audio library for M0 microcontrollers
 * (Circuit Playground Express, Feather M0, Arduino Zero, etc.).
 * Gator-clip antenna to pin A0. Tune receiver to lower frequencies in AM
 * band (examples use 540 KHz by default).
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
 *
 * MIT license, all text above must be included in any redistribution
 *
 */

#ifndef _ADAFRUIT_AMRADIO_H_
#define _ADAFRUIT_AMRADIO_H_

#include <Adafruit_ZeroDMA.h>

/**
 * @brief Class for using a M0 microcontroller as a short-range
 * AM audio transmitter.
 */
class Adafruit_AMRadio {
public:
  /**
   * @brief Construct a new Adafruit_AMRadio::Adafruit_AMRadio object.
   */
  Adafruit_AMRadio();

  /**
   * @brief  Call to begin AM audio transmission at a given frequency.
   *
   * @param  freq  Frequency should be low AM, the lower the better -- try
   *               540000, or some receivers go a bit lower, maybe 510000.
   * @return bool  true on success, false on failure.
   */
  boolean begin(uint32_t freq = 540000); // 510000+

  /**
   * @brief `write(n)` is equivalent to `analogWrite(n)`; accepts 10-bit
   * input (0-1023).  Any function that uses DAC for audio (WAV player,
   * Talkie, etc.) can be easily modified to use this instead of the DAC.
   *
   * @param center_frequency
   * Input   Carrier hi,lo
   *   0  ->   512 511
   * 511  ->   767 256
   *1023  ->  1023   0
   */
  void write(uint16_t center_frequency); // 0-1023

  /**
   * @brief  Similar to Arduino tone() function, except duration is required;
   *         function "blocks" and does not run in the background.
   *
   * @param  freq  Tone frequency in Hz.
   * @param  msec  Duration in milliseconds.
   * @param  vol   Volume level (0-1023, default=1023).
   */
  void tone(uint16_t freq, uint32_t msec, uint16_t vol = 1023);

private:
  uint16_t carrier[2];  ///< Square wave; 2 elements, hi & low
  Adafruit_ZeroDMA dma; ///< SAMD DMA object
};

#endif // _ADAFRUIT_AMRADIO_H_
