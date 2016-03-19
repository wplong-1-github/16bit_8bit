#include <cstdlib>
#include <iostream>
#include <time.h>
#include "TRandom3.h"

#define NUM 14
#define FRM (NUM*16)

void CRC(int frame[], int C[]);
bool check(int a[], int b[]);
int randTo0or1(double rand);
int randTo0to223(double rand, const double divPtr[]);

int main()
{
  //	creat 224 array 
  //	creat 8 arry
  int frame[FRM];
  int crc[8] = {};
  int crcTemp[8];
  int flipN[3];
  unsigned equ = 0;
  unsigned nequ = 0;
  TRandom3 rnd;

  double rndTemp;

  static double div[224];
 
  // Initialize global variable
  for (int n=0; n<224; n++)
    div[n] = n / 224.0;


  // 1 million loop start
  for (int j=0; j<1000000; j++)
    {
      for (int i=0; i<FRM; i++)
	{
	  rndTemp = rnd.Rndm();
	  //while (rndTemp == 0.5)
	  //rndTemp = rnd.Rndm();

	  frame[i] = randTo0or1(rndTemp); // Generate a random number between 0 and 1
	  //std::cout << "frame " << i << " " << frame[i] << std::endl;
	}

      // go through CRC    
      CRC(frame, crc);

      // store crc data to crcTemp
      for (int i=0; i<8; i++)
	crcTemp[i] = crc[i];

      // flip one element
      flipN[0] = randTo0to223(rnd.Rndm(), div);
      flipN[1] = randTo0to223(rnd.Rndm(), div);
      flipN[2] = randTo0to223(rnd.Rndm(), div);

      while (flipN[1] == flipN[0])
	flipN[1] = randTo0to223(rnd.Rndm(), div);
      
      while (flipN[2] == flipN[0] || flipN[2] == flipN[1])
	flipN[2] = randTo0to223(rnd.Rndm(), div);

      frame[flipN[0]] = !frame[flipN[0]];
      frame[flipN[1]] = !frame[flipN[1]];
      frame[flipN[2]] = !frame[flipN[2]];

      // 2nd go through CRC
      CRC(frame, crc);

      // compare crc with crcTemp
      check(crcTemp, crc) ? equ++ : nequ++ ;
    
    }    // end of 1 million loop

  std::cout << "equ emans difference can not be tested" << std::endl;
  std::cout << "equ " << equ << std::endl;

  std::cout << "nequ means difference can be tested" << std::endl;
  std::cout << "nequ " << nequ << std::endl;

  return 0;
}


// simulate the process of CRC
void CRC(int frame[], int C[])
{
  int A[16];
  int nextCRC[8];

  // Initialize C[]
  for (int i=0; i<8; i++)
    C[i] = 0;

  for (int j=0; j<NUM; j++)
    {
      // Feed A[] with frame 16 elements
      for (int i=0; i<16; i++)
	A[i] = frame[i+j*16];
   
      // calculate nextCRC under one 224-pin loop
      //
      //A0A3A4A5A6A7A8A10A12A15C0C1C2C3C4C7
      nextCRC[0] =  A[0]^A[3]^A[4]^A[5]^A[6]^A[7]^A[8]^A[10]^A[12]^A[15]^C[0]^C[1]^C[2]^C[3]^C[4]^C[7];
      //A0A2A8A9A10A11A12A14A15C5C7
      nextCRC[1] =  A[0]^A[2]^A[8]^A[9]^A[10]^A[11]^A[12]^A[14]^A[15]^C[5]^C[7];
      //A0A1A3A4A5A6A9A11A12A13A14A15C1C2C3C4C6C7 
      nextCRC[2] =  A[0]^A[1]^A[3]^A[4]^A[5]^A[6]^A[9]^A[11]^A[12]^A[13]^A[14]^A[15]^C[1]^C[2]^C[3]^C[4]^C[6]^C[7];
      //A2A6A7A11A13A14A15C0C1C5 
      nextCRC[3] =  A[2]^A[6]^A[7]^A[11]^A[13]^A[14]^A[15]^C[0]^C[1]^C[5];
      //A1A5A6A10A12A13A14C1C2C6 
      nextCRC[4] =  A[1]^A[5]^A[6]^A[10]^A[12]^A[13]^A[14]^C[1]^C[2]^C[6];
      //A3A6A7A8A9A10A11A13A15C0C1C4 
      nextCRC[5] =  A[3]^A[6]^A[7]^A[8]^A[9]^A[10]^A[11]^A[13]^A[15]^C[0]^C[1]^C[4];
      //A2A5A6A7A8A9A10A12A14C0C1C2C5
      nextCRC[6] =  A[2]^A[5]^A[6]^A[7]^A[8]^A[9]^A[10]^A[12]^A[14]^C[0]^C[1]^C[2]^C[5];
      //A1A4A5A6A7A8A9A11A13C0C1C2C3C6 
      nextCRC[7] =  A[1]^A[4]^A[5]^A[6]^A[7]^A[8]^A[9]^A[11]^A[13]^C[0]^C[1]^C[2]^C[3]^C[6];

      for (int k=0; k<8; k++)
	{
	  C[k] = nextCRC[k];
	  //	  std::cout << "after CRC C[]:" << C[k] << std::endl;
	}

    }
}

// check two array, all element equal
bool check(int a[], int b[])
{
  for (int i=0; i<8; i++)
    if (a[i] != b[i])
      return false;

  return true;
}

int randTo0or1(double rand)
{
  if (rand >= 0.5)
    return 1;
  else
    return 0;
}

int randTo0to223(double rand, const double divPtr[])
{
  int j=223;
  
  while(rand < divPtr[j])
    j--;

  return j;
}
