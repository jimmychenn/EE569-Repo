I2 = [0 2;
      3 1];
T2 = (I2 + 0.5)/4 * 255
  
I4 = [4*I2   4*I2+2;
      4*I2+3 4*I2+1];
I8 = [4*I4   4*I4+2;
      4*I4+3 4*I4+1];
T8 = (I8 + 0.5)/64 * 255