# SPI Bridge

The code shows a SPI bridge between Arduino (ATmega32u4) and ReSpeaker (MT7688). The MT7688 is as a SPI master and ATmega32u4 as a SPI slave.

The data transformation is duplex. 

### for ATmega32u4

```
  char c = SPDR;  // read SPI Data Register

  SPDR = c;   // write back to SPI, it will be transfed to the master next time
  ```
  
