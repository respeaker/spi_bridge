/**
 * Use Arduino (atmega32u4) as a SPI slave
 *
 * by Seeed Studio (http://seeedstudio.com)
 */

#include <SPI.h>

char spi_buf[64];
volatile byte spi_buf_index = 0;
volatile byte spi_event = 0;

void setup (void)
{
  Serial.begin(57600);
  Serial1.begin(57600);

  spi_slave_init();
}

void spi_slave_init()
{
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);

  // enable SPI slave mode
  SPCR |= _BV(SPE);

  SPI.attachInterrupt();
}

// SPI interrupt handler
ISR (SPI_STC_vect)
{
  char c = SPDR;  // read SPI Data Register
  if (spi_buf_index >= sizeof(spi_buf)) {
    spi_buf_index = 0;
  }

  if ('\n' == c) {
    spi_event = 1;
    spi_buf[spi_buf_index] = '\0';
  } else {
    spi_buf[spi_buf_index] = c;
    spi_buf_index++;
  }
}


void loop (void)
{
  // USB to UART
  while (Serial1.available() && Serial.availableForWrite()) {
    Serial.write((char)Serial1.read());
  }
  while (Serial.available() && Serial1.availableForWrite()) {
    Serial1.write((char)Serial.read());
  }

  if (spi_event) {
    spi_event = 0;
    spi_buf_index = 0;
    Serial.print("spi rx:");
    Serial.println(spi_buf);
  }
    
}
