/*!
 * @file Adafruit_AMRadio.cpp
 *
 * @mainpage AM radio transmit audio library for M0 microcontrollers.
 *
 * @section intro_sec Introduction
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
 * @section dependencies Dependencies
 *
 * This library depends on <a
 * href="https://github.com/adafruit/Adafruit_ZeroDMA"> Adafruit_ZeroDMA</a>
 * being present on your system. Please make sure you have installed the
 * latest version before using this library.
 *
 * @section author Author
 *
 * Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
 *
 * @section license License
 *
 * MIT license, all text above must be included in any redistribution
 *
 */

#include <Adafruit_AMRadio.h>

Adafruit_AMRadio::Adafruit_AMRadio() {}

bool Adafruit_AMRadio::begin(uint32_t freq) {
  carrier[0] = 767;
  carrier[1] = 256;

  // TIMER INIT ------------------------------------------------------------
  // TC5 is used; same as Arduino Tone library or Adafruit_CompositeVideo

  GCLK->CLKCTRL.reg = (uint16_t)(GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 |
                                 GCLK_CLKCTRL_ID(GCM_TC4_TC5));
  while (GCLK->STATUS.bit.SYNCBUSY == 1)
    ;

  TC5->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (TC5->COUNT16.STATUS.bit.SYNCBUSY)
    ;

  TC5->COUNT16.CTRLA.reg =     // Configure timer counter
      TC_CTRLA_MODE_COUNT16 |  // 16-bit counter mode
      TC_CTRLA_WAVEGEN_MFRQ |  // Match Frequency mode
      TC_CTRLA_PRESCALER_DIV1; // 1:1 Prescale
  while (TC5->COUNT16.STATUS.bit.SYNCBUSY)
    ;

  TC5->COUNT16.CC[0].reg = ((F_CPU + freq) / (freq * 2)) - 1;
  while (TC5->COUNT16.STATUS.bit.SYNCBUSY)
    ;

  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
  while (TC5->COUNT16.STATUS.bit.SYNCBUSY)
    ;

    // DAC INIT --------------------------------------------------------------

#ifdef ADAFRUIT_CIRCUITPLAYGROUND_M0
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW); // Switch off speaker (DAC to A0 pin only)
#endif
  analogWriteResolution(10); // Let Arduino core initialize the DAC,
  analogWrite(A0, 512);      // ain't nobody got time for that!

  // DMA INIT --------------------------------------------------------------

  dma.setTrigger(TC5_DMAC_ID_OVF);
  dma.setAction(DMA_TRIGGER_ACTON_BEAT);
  dma.allocate();
  dma.addDescriptor(carrier, (void *)&DAC->DATA.reg, 2, DMA_BEAT_SIZE_HWORD,
                    true, false);
  dma.loop(true);
  return dma.startJob();
}

void Adafruit_AMRadio::write(uint16_t center_frequency) {
  center_frequency /= 2;
  carrier[0] = 512 + center_frequency;
  carrier[1] = 511 - center_frequency;
}

void Adafruit_AMRadio::tone(uint16_t freq, uint32_t msec, uint16_t vol) {
  if (vol > 1023)
    vol = 1023;
  vol /= 2; // 0 to 511
  uint32_t halfWave = (1000000 + freq) / (freq * 2), x, usec = msec * 1000,
           startTime = micros();
  while ((x = (micros() - startTime)) <= usec) {
    write(((x / halfWave) & 1) ? (512 + vol) : (511 - vol));
  }
  write(512);
}
