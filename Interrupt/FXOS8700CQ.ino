#include "FXOS8700CQ.h"
#include <math.h>

//******************************************************************************
// Public Function Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// FXOS8700CQ(): Initialize configuration parameters
//------------------------------------------------------------------------------
FXOS8700CQ::FXOS8700CQ() {
    magODR = MODR_100HZ; // Magnetometer data/sampling rate
    magOSR = MOSR_5;     // Choose magnetometer oversample rate

    pinMode(CS_PIN, OUTPUT);        // Select the GPIO Pin 51 as SPI Chip Select
    digitalWrite(CS_PIN, HIGH);     // Set Pin to high (Active Low)
}

//------------------------------------------------------------------------------
// writeReg(): Writes to a register
//------------------------------------------------------------------------------
void FXOS8700CQ::writeReg(uint8_t reg, uint8_t data) {
     // TO DO: 
     spi_write_cmd(reg,data);
}

//------------------------------------------------------------------------------
// readReg(): Reads from a register
//------------------------------------------------------------------------------
uint8_t FXOS8700CQ::readReg(uint8_t reg) {
    
    uint8_t rx_data;
    rx_data = spi_read_cmd(reg);
    return(rx_data);
}

//------------------------------------------------------------------------------
// readMagData(): Read the magnometer X, Y and Z axisdata
//------------------------------------------------------------------------------
int FXOS8700CQ::readMagData() {
    uint8_t mag_l;
    uint8_t mag_h;
    uint16_t mag_val;
    uint16_t raw_val;
    float mag_val2;
    
    
    mag_l = readReg(FXOS8700CQ_M_OUT_X_LSB);
    mag_h = readReg(FXOS8700CQ_M_OUT_X_MSB);
    raw_val = (mag_h*256 )+mag_l;
    mag_val = (mag_h*256 )+mag_l;
    if(mag_val>32768)
    {
      mag_val= ~(mag_val)+1;
    }
    mag_val2 = float(mag_val*0.1);
    //SerialUSB.print("X : ");
    //SerialUSB.print(raw_val);
    //SerialUSB.print(mag_val2);
    //SerialUSB.print("   ");

    mag_l = readReg(FXOS8700CQ_M_OUT_Y_LSB);
    mag_h = readReg(FXOS8700CQ_M_OUT_Y_MSB);
    raw_val = (mag_h*256 )+mag_l;
    mag_val = (mag_h*256)+mag_l;
    if(mag_val>32768)
    {
      mag_val= ~(mag_val)+1;
    }
    mag_val2 = float(mag_val*0.1);
    //SerialUSB.print("Y : ");
    //SerialUSB.print(raw_val);
    //SerialUSB.print(mag_val2);
    //SerialUSB.print("   ");

    mag_l = readReg(FXOS8700CQ_M_OUT_Z_LSB);
    mag_h = readReg(FXOS8700CQ_M_OUT_Z_MSB);
    raw_val = (mag_h*256 )+mag_l;
    mag_val = (mag_h*256)+mag_l;
    if(mag_val>32768)
    {
      mag_val= ~(mag_val)+1;
    }
    mag_val2 = float(mag_val*0.1);
    //SerialUSB.print("Z is : ");
    SerialUSB.println(raw_val);
    //SerialUSB.println(mag_val2);

    //mag_l = spi_read_cmd(FXOS8700CQ_M_DR_STATUS);
    //SerialUSB.println(mag_l);
    //SerialUSB.println(" ");
    return raw_val;
    
}

//------------------------------------------------------------------------------
// standby(): Put the FXOS8700CQ into standby mode for writing to registers
//------------------------------------------------------------------------------
void FXOS8700CQ::standby() {
   //Chip select high and initialize transaction
   spi_write_cmd(FXOS8700CQ_CTRL_REG1,0x18);
   //Chip select disable and end transaction

}

//------------------------------------------------------------------------------
// active(): Put the FXOS8700CQ into active mode to output data
//------------------------------------------------------------------------------
void FXOS8700CQ::active() {
   //Chip select high and initialize transaction
   spi_write_cmd(FXOS8700CQ_CTRL_REG1,0x19);
   //Chip select disable and end transaction
}

//------------------------------------------------------------------------------
// init(): Initialize the magnetometer
//         This function will put the magnetometer in standby mode, modify the 
//         registers that put the device in mag-only mode, set the correct data
//         rate (ODR) and oversampling rate (OSR) for the magnetometer and put
//         it back in active mode
//------------------------------------------------------------------------------
void FXOS8700CQ::init() {
   SerialUSB.println("Init Function : ");
   spi_write_cmd(FXOS8700CQ_CTRL_REG1,24);
   spi_write_cmd(FXOS8700CQ_M_CTRL_REG1,0x15);
   spi_write_cmd(FXOS8700CQ_CTRL_REG1,25);
   SerialUSB.println(" ");
   

}

//------------------------------------------------------------------------------
// checkWhoAmI(): Check the whoAmI register
//------------------------------------------------------------------------------
void FXOS8700CQ::checkWhoAmI(void) {
    //Compare Values
    if(FXOS8700CQ_WHOAMI_VAL != spi_read_cmd(FXOS8700CQ_WHO_AM_I))
    {
      SerialUSB.println("Device Authentication Failed");
      while(1);
    }
    else
    {
      SerialUSB.println("Device Authentication Passed");
    };
}

void FXOS8700CQ::enableInt() {
  spi_write_cmd(FXOS8700CQ_M_THS_X_MSB, 0b00000000);
  spi_write_cmd(FXOS8700CQ_M_THS_X_LSB, 0b00000000);
  spi_write_cmd(FXOS8700CQ_M_THS_Y_MSB, 0b00000000);
  spi_write_cmd(FXOS8700CQ_M_THS_Y_LSB, 0b00000000);
  spi_write_cmd(FXOS8700CQ_M_THS_Z_MSB, 0b00000000);
  spi_write_cmd(FXOS8700CQ_M_THS_Z_LSB, 0b00000000);
  spi_write_cmd(FXOS8700CQ_M_THS_CFG, 0x63);
}

void FXOS8700CQ::disableInt() {
  spi_write_cmd(FXOS8700CQ_M_THS_CFG, 0x60);
}

void FXOS8700CQ::calibrate() {
  SerialUSB.println("Calibrating...");
}

void FXOS8700CQ::reset() {
  spi_write_cmd(FXOS8700CQ_CTRL_REG2, 0x44);
}
//*****************************************************************************

