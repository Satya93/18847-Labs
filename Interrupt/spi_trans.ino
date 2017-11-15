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
    //SerialUSB.println("Entered Write");
    // TO DO:
    uint8_t add_l = address & 0b01111111;
    uint8_t add_h = address & 0b10000000;
    add_l = 0b10000000 | add_l;
    //Transmission
    digitalWrite(CS_PIN, LOW);
    
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    
    SPI.transfer(add_l); //Byte0
    
    SPI.transfer(add_h); //Byte1
    SPI.transfer(tx_data); //Byte2
    SPI.endTransaction();
    
    digitalWrite(CS_PIN, HIGH);
}

//------------------------------------------------------------------------------
// spi_read_cmd(): Read from a SPI device
//------------------------------------------------------------------------------
uint8_t spi_read_cmd(uint8_t address) {
    //SerialUSB.println("Entered SPI Address");
    uint8_t rx_data;
    // TO DO:
    uint8_t add_l = address & 0b01111111;
    uint8_t add_h = address & 0b10000000;
    //Transmission
    digitalWrite(CS_PIN, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(add_l); //Byte0
    SPI.transfer(add_h); //Byte1
    rx_data = SPI.transfer(0x00); //Byte2
    SPI.endTransaction();
    //SerialUSB.println("Exited");
    digitalWrite(CS_PIN, HIGH);
    //SerialUSB.println("Deselect");
    //SerialUSB.println(rx_data);
    delay(10);
    return rx_data;
}

//*****************************************************************************

