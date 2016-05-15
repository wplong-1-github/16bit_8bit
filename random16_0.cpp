#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

#define NUM 6
#define CRCBIT 16
#define FRM (NUM*CRCBIT)

void CRC(int frame[], int C[]);
bool check(int a[], int b[]);

int main(int argc, char *argv[])
{
  //	creat 96 array 
  //	creat 16 arry
  if(argc <= 1) {
    exit(1);
  }
  int n = atoi(argv[1]);

  int frame[FRM];
  int crc[CRCBIT] = {};
  int crcTemp[CRCBIT];
  std::vector<int> flipN;
  int flipTemp;
  unsigned equ = 0;
  unsigned nequ = 0;
  bool tag;

  srand( time(NULL) );

  std::cout << n << std::endl;
  //std::cout << "input complete" << std::endl;
  // 1 million loop start
  for (int j=0; j<1000000; j++)
    {

      for (int i=0; i<FRM; i++)
	{
	  frame[i] = rand() % 2; // Generate a random number between 0 and 1
	  //std::cout << "frame " << i << " " << frame[i] << std::endl;
	}

      // go through CRC    
      CRC(frame, crc);

      // store crc data to crcTemp
      for (int i=0; i<CRCBIT; i++)
	crcTemp[i] = crc[i];

      //std::cout << " before tag " << std::endl;

      // generate n element for flip
      for (int i=0; i<n; i++) 
	{
	  flipTemp = rand() % FRM;

	  //std::cout << " after iterator " << std::endl;	

	  tag = false;
	  for (auto& itr : flipN) 
	    if (itr == flipTemp) {
	      tag = true;
	      break;
	    }
	  
	  while (tag) {
	    flipTemp = rand() % FRM;

	    tag = false;
	    for (auto& itr : flipN) 
	      if (itr == flipTemp) {
		tag = true;
		break;
	      }
	  } // end of while

	  //std::cout << "before pushback "<< std::endl;
	  flipN.push_back(flipTemp);
	}// end of for flip loop

      //std::cout << "before flip" << std::endl;
      // flip n element
      for (int i=0; i<n; i++)
	frame[flipN.at(i)] = !frame[flipN.at(i)];

      //std::cout << "before 2nd CRC" << std::endl;

      // 2nd go through CRC
      CRC(frame, crc);

      // clear for next 10 million loop use
      flipN.clear();

      // compare crc with crcTemp
      check(crcTemp, crc) ? equ++ : nequ++ ;
    
    }    // end of 1 million loop

  std::cout << "equ means difference CAN NOT be tested" << std::endl;
  std::cout << equ << std::endl;

  std::cout << "nequ means difference CAN be tested" << std::endl;
  std::cout << "nequ " << nequ << std::endl;

  return 0;
}


// simulate the process of CRC
void CRC(int frame[], int C[])
{
  int A[16];
  int nextCRC[CRCBIT];

  // Initialize C[]
  for (int i=0; i<CRCBIT; i++)
    C[i] = 0;

  for (int j=0; j<NUM; j++)
    {
      // Feed A[] with frame 16 elements
      for (int i=0; i<16; i++)
	A[i] = frame[i+j*16];
   
      // calculate nextCRC under one 96-pin loop
      //
      nextCRC[0]= A[10]^A[13]^A[15]^A[1]^A[2]^A[4]^A[5]^A[8]^A[9]^C[0]^C[10]^C[11]^C[13]^C[14]^C[2]^C[5]^C[6]^C[7];
      nextCRC[1]= A[0]^A[10]^A[12]^A[13]^A[14]^A[15]^A[2]^A[3]^A[5]^A[7]^C[0]^C[10]^C[12]^C[13]^C[15]^C[1]^C[2]^C[3]^C[5]^C[8];
      nextCRC[2]= A[11]^A[12]^A[13]^A[14]^A[1]^A[2]^A[4]^A[6]^A[9]^C[11]^C[13]^C[14]^C[1]^C[2]^C[3]^C[4]^C[6]^C[9];
      nextCRC[3]= A[0]^A[10]^A[11]^A[12]^A[13]^A[1]^A[3]^A[5]^A[8]^C[10]^C[12]^C[14]^C[15]^C[2]^C[3]^C[4]^C[5]^C[7];
      nextCRC[4]= A[0]^A[11]^A[12]^A[13]^A[15]^A[1]^A[5]^A[7]^A[8]^C[0]^C[10]^C[14]^C[15]^C[2]^C[3]^C[4]^C[7]^C[8];
      nextCRC[5]= A[0]^A[10]^A[11]^A[12]^A[14]^A[4]^A[6]^A[7]^C[11]^C[15]^C[1]^C[3]^C[4]^C[5]^C[8]^C[9];
      nextCRC[6]= A[10]^A[11]^A[13]^A[3]^A[5]^A[6]^A[9]^C[10]^C[12]^C[2]^C[4]^C[5]^C[6]^C[9];
      nextCRC[7]= A[12]^A[13]^A[15]^A[1]^C[0]^C[14]^C[2]^C[3];
      nextCRC[8]= A[0]^A[10]^A[11]^A[12]^A[13]^A[14]^A[15]^A[1]^A[2]^A[4]^A[5]^A[8]^A[9]^C[0]^C[10]^C[11]^C[13]^C[14]^C[15]^C[1]^C[2]^C[3]^C[4]^C[5]^C[6]^C[7];
      nextCRC[9]= A[0]^A[11]^A[12]^A[14]^A[15]^A[2]^A[3]^A[5]^A[7]^C[0]^C[10]^C[12]^C[13]^C[15]^C[1]^C[3]^C[4]^C[8];
      nextCRC[10]= A[10]^A[11]^A[13]^A[14]^A[1]^A[2]^A[4]^A[6]^C[11]^C[13]^C[14]^C[1]^C[2]^C[4]^C[5]^C[9];
      nextCRC[11]= A[0]^A[12]^A[15]^A[2]^A[3]^A[4]^A[8]^C[0]^C[11]^C[12]^C[13]^C[15]^C[3]^C[7];
      nextCRC[12]= A[10]^A[11]^A[13]^A[14]^A[15]^A[3]^A[4]^A[5]^A[7]^A[8]^A[9]^C[0]^C[10]^C[11]^C[12]^C[1]^C[2]^C[4]^C[5]^C[6]^C[7]^C[8];
      nextCRC[13]= A[10]^A[12]^A[13]^A[14]^A[2]^A[3]^A[4]^A[6]^A[7]^A[8]^A[9]^C[11]^C[12]^C[13]^C[1]^C[2]^C[3]^C[5]^C[6]^C[7]^C[8]^C[9];
      nextCRC[14]= A[10]^A[11]^A[12]^A[15]^A[3]^A[4]^A[6]^A[7]^C[0]^C[11]^C[12]^C[3]^C[4]^C[5]^C[8]^C[9];
      nextCRC[15]= A[10]^A[11]^A[14]^A[2]^A[3]^A[5]^A[6]^A[9]^C[10]^C[12]^C[13]^C[1]^C[4]^C[5]^C[6]^C[9];

      for (int k=0; k<CRCBIT; k++)
	{
	  C[k] = nextCRC[k];
	  //	  std::cout << "after CRC C[]:" << C[k] << std::endl;
	}

    }
}

// check two array, all element equal
bool check(int a[], int b[])
{
  for (int i=0; i<CRCBIT; i++)
    if (a[i] != b[i])
      return false;

  return true;
}
