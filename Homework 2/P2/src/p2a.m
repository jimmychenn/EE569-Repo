I2 = [0 2;
      3 1];
T2 = (I2 + 0.5)/4 * 255
  
I4 = [4*I2   4*I2+2;
      4*I2+3 4*I2+1];
T4 = (I4 + 0.5)/16 * 255

I8 = [4*I4   4*I4+2;
      4*I4+3 4*I4+1];
T8 = (I8 + 0.5)/64 * 255

A4 = [14 10 11 15;
      9  3  0  4 ;
      8  2  1  5 ;
      13 7  6  12];
AT4 = (A4 + 0.5)/16 * 255


%designing a quarter toning algorithm
T4_1 = (I4 + 0.5)/16 * 255 * 1/3
T4_2 = (I4 + 0.5)/16 * 255 * 2/3
T4_3 = (I4 + 0.5)/16 * 255 * 3/3