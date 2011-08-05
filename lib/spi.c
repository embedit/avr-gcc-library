#include <spi.h>
#include <avr/io.h>

void spi_init(void)
{
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1);
	DDRB = (1<<PB0)|(1<<PB1)|(1<<PB2);
}

uint8_t spi_send(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}
