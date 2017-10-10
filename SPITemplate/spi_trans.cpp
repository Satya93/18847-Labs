// Reading and Writing the SPI bus

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include "spi_trans.h"

//******************************************************************************
// Function Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// spi_write_cmd(): Transmit to a SPI device
//------------------------------------------------------------------------------
void spi_write_cmd(uint8_t address, uint8_t tx_data) {
    // TO DO:

    //Chip select high and initialize transaction
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(CS_PIN,LOW);

    //Transmission
    SPI.transfer()

    //Chip select disable and end transaction
    digitalWrite(CS_PIN,HIGH);
    SPI.endTransaction();
}

//------------------------------------------------------------------------------
// spi_read_cmd(): Read from a SPI device
//------------------------------------------------------------------------------
uint8_t spi_read_cmd(uint8_t address) {
    uint8_t rx_data;
    // TO DO:
    
    return rx_data;
}

//*****************************************************************************
