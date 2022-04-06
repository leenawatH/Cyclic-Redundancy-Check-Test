#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
long long findCRC(){
 
  char div[] = NULL;
  char crc[20];
  do{
    printf("Enter CRC type : ");
    scanf("%s", &crc);
    printf("%s\n",crc);
    char crc32[] = "CRC-32", crc24[] = "CRC-24", crc16[] = "CRC-16", re16[] = "Reversed-CRC-16" , crc8[] = "CRC-8", crc4[] = "CRC-4";
    if (strcmp(crc,crc32) == 0){
      div[] = "100000100110000010001110110110111";
    }else if(strcmp(crc,crc24)== 0){
      div[] = "1100000000101000100000001";
    }else if(strcmp(crc,crc16)== 0){
      div[] = "11000000000000101";
    }else if(strcmp(crc,re16)== 0){
      div[] = "10100000000000011";
    }else if(strcmp(crc,crc8)== 0){
      div[] = "111010101";
    }else if(strcmp(crc,crc4)== 0){
      div[] = "11111";
    }else{
      printf("Incorrect\n");
    }
  }while(div == 0);
  return div;
}

int main() {
  long long n,a;
  int word_size = 5,count;
  do{
    count = 0;
    printf("Enter Dataword: ");
    scanf("%lld", &n);
    a = n;
    do {
      n /= 10;
      ++count;
    } while (n != 0);
    if(count <word_size){
      printf("Less digit!!!\n");
    }
  }while (count < word_size);
  printf("Number of digits: %d\n", count);
  printf("%lld\n",a);
  long long data[count];
  for(int i = count-1; i >= 0; i--){
    long long temp = a%10;
    a /=10;
    data[i] = temp;
  }
  for(int i = 0; i < count; i++){
    printf("%d\n",data[i]);
  }

  char divisor[] = findCRC();
  printf("%s",divisor);
}
