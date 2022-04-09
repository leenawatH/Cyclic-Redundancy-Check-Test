#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int random(int upper,int lower){
  int ran;
  
  srand(time(0));
  ran = (rand() % (upper - lower +1)) + lower;
  
  return ran;
}

const char *findCRC()
{
  char crc[20];
  printf("Enter CRC type : ");
  scanf("%s", &crc);
  char crc32[] = "CRC-32", crc24[] = "CRC-24", crc16[] = "CRC-16", re16[] = "Reversed-CRC-16", crc8[] = "CRC-8", crc4[] = "CRC-4";
  if (strcmp(crc, crc32) == 0)
  {
    return "100000100110000010001110110110111";
  }
  else if (strcmp(crc, crc24) == 0)
  {
    return "1100000000101000100000001";
  }
  else if (strcmp(crc, crc16) == 0)
  {
    return "11000000000000101";
  }
  else if (strcmp(crc, re16) == 0)
  {
    return "10100000000000011";
  }
  else if (strcmp(crc, crc8) == 0)
  {
    return "111010101";
  }
  else if (strcmp(crc, crc4) == 0)
  {
    return "11111";
  }
  else
  {
    printf("Incorrect\n");
    findCRC();
  }
  return 0;
}

int xor (int a, int b) {
  int c;
  if (a == b)
  {
    c = 0;
  }
  else
  {
    c = 1;
  }
  return c;
}

int main(void)
{
  long long n, a;
  int word_size = 5, count;
  //input
  do
  {
    count = 0;
    printf("Enter Dataword: ");
    scanf("%lld", &n);
    a = n;
    do
    {
      n /= 10;
      ++count;
    } while (n != 0);
    if (count < word_size)
    {
      printf("Less digit!!!\n");
    }
  } while (count < word_size);
  //set data from one data to array
  long long data[count];
  for (int i = count - 1; i >= 0; i--)
  {
    long long temp = a % 10;
    a /= 10;
    data[i] = temp;
  }
  //get CRC type of divide
  //eg. input = "CRC-32"
  const char *div = findCRC();
  //turn string from polynomial from question(set just result in type binary in funtion findCRC()) to array
  int data_div[strlen(div)];
  for (int i = 0; i < strlen(div); i++)
  {
    if (div[i] == '0')
    {
      data_div[i] = 0;
    }
    else
    {
      data_div[i] = 1;
    }
  }
  //set size for codeword with remainder
  int size_divided = count + strlen(div) - 1;
  int divided[size_divided];
  for (int i = 0; i < count; i++)
  {
    divided[i] = data[i];
  }
  for (int i = count; i < size_divided; i++)
  {
    divided[i] = 0;
  }
  printf("divided = ");
 
  for (int i = 0; i < strlen(div) - 1 + count; i++)
  {
    printf("%d", divided[i]);
  }
  printf("\n");
  //divide process
  int temps[strlen(div)];
  for (int i = 0; i < strlen(div); i++)
  {
    temps[i] = divided[i];
  }
  int then[strlen(div)];
  for (int j = 0; j < count; j++)
  {
    for (int i = 1; i < strlen(div); i++)
    {
      if (temps[0] == 1)
      {
        then[i - 1] = xor(temps[i], data_div[i]);
      }
      else
      {
        then[i - 1] = xor(temps[i], 0);
      }
    }
    then[strlen(div) - 1] = divided[strlen(div) + j];
    for (int i = 0; i < strlen(div); i++)
    {
      temps[i] = then[i];
    }
  }
  //make codeword with remainder
  int result_encode[size_divided];
  for (int i = 0; i < count; i++)
  {
    result_encode[i] = data[i];
  }
  int num = 0;
  for (int i = count; i < size_divided; i++)
  {
    result_encode[i] = then[num];
    num++;
  }
  printf("Number with reminder : ");
  for (int i = 0; i < size_divided; i++)
  {
    printf("%d", result_encode[i]);
  }
  printf("\n");
  //set random number for simulation data was damaged
  printf("If random number is 7,8,9,10 : Data will change for some position\n");
  printf("Random number : ");
  int x  =random(10,1);
  printf("%d\n",x);
  //if random num in more than 7 the data was damaged and change number some position
  if(x >= 7){
    int y  =random(size_divided,5);
    if(result_encode[y] == 0){
      result_encode[y] = 1;
    }else{
      result_encode[y] = 0;
    }
    printf("Number when it change : ");
    for (int i = 0; i < size_divided; i++)
    {
      printf("%d", result_encode[i]);
    }
    printf("\n");
  }
  //do Checker process
  int decode[strlen(div)];
  for (int i = 0; i < strlen(div); i++)
  {
    decode[i] = result_encode[i];
  }
  int then_decode[strlen(div)];
  for (int j = 0; j < count; j++)
  {
    for (int i = 1; i < strlen(div); i++)
    {
      if (decode[0] == 1)
      {
        then_decode[i - 1] = xor(decode[i], data_div[i]);
      }
      else
      {
        then_decode[i - 1] = xor(decode[i], 0);
      }
    }
    then_decode[strlen(div) - 1] = result_encode[strlen(div) + j];
    for (int i = 0; i < strlen(div); i++)
    {
      decode[i] = then_decode[i];
    }
  }
  //check the result that was damaged or not and print the result
  int check0 = 0;
  for (int i = 0; i < strlen(div) - 1; i++)
  {
    if (then_decode[i] != 0)
    {
      break;
    }
    else
    {
      check0++;
    }
  }
  if (check0 == strlen(div) - 1)
  {
    printf("Pass");
  }
  else
  {
    printf("Fail");
  }
}
