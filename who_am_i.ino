status_t LSM303C::WhoAmI()
{
  debug_println("Starting Check");
  uint8_t data, comp;
  status_t resp;
  comp = 0x3D;
  I2C_ByteRead(MAG_I2C_ADDR,MAG_WHO_AM_I, data);
  if (data!=comp)
  {
    resp = IMU_HW_ERROR;
    debug_println("Error!");
  }
  else
  {
    resp = IMU_SUCCESS;
    debug_println("Success!");
  }
  return resp;
}