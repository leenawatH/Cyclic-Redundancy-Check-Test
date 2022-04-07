#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
const char* findCRC(){
  char x[1] = "1";
  char crc[20];
  do{
    printf("Enter CRC type : ");
    scanf("%s", &crc);
    char crc32[] = "CRC-32", crc24[] = "CRC-24", crc16[] = "CRC-16", re16[] = "Reversed-CRC-16" , crc8[] = "CRC-8", crc4[] = "CRC-4";
    if (strcmp(crc,crc32) == 0){
      return "100000100110000010001110110110111";
    }else if(strcmp(crc,crc24)== 0){
      return "1100000000101000100000001";
    }else if(strcmp(crc,crc16)== 0){
      return "11000000000000101";
    }else if(strcmp(crc,re16)== 0){
      return "10100000000000011";
    }else if(strcmp(crc,crc8)== 0){
      return "111010101";
    }else if(strcmp(crc,crc4)== 0){
      return "11111";
    }else{
      printf("Incorrect\n");
    }
  }while(x[1] == "1");
  return 0;
}

int xor(int a , int b){
  int c;
  if (a == b){
    c = 0;
  }else{
    c = 1;
  }
  return c;
}

int main(void) {
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
  long long data[count];
  for(int i = count-1; i >= 0; i--){
    long long temp = a%10;
    a /=10;
    data[i] = temp;
  }
  for(int i = 0; i < count; i++){
    printf("%d",data[i]);
  }
  printf("\n");
  const char *div = findCRC();
  long long divide = atoll(div);
  printf("%d",divide);
  int data_div[strlen(div)];
  for(int i = strlen(div)-1; i >= 0; i--){
    long long temp = divide%10;
    divide /=10;
    data_div[i] = temp;
  }
  for(int i = 0;i< strlen(div); i++){
    printf("%d",data_div[i]);
  }
  printf("\n");
  int size_divided = count + strlen(div)-1 ;
  int divided[size_divided];
  for(int i = 0; i < count; i++){
    divided[i] = data[i];
  }
  for(int i = count; i < size_divided; i++){
    divided[i] = 0;
  }
  
  for(int i = 0; i < strlen(div)-1+count; i++){
    printf("%d",divided[i]);
  }
  printf("\n");
  int temps[strlen(div)];
  for(int i = 0; i < strlen(div); i++){
    temps[i] = divided[i];
  }
  int then[strlen(div)];
  for(int j = 0; j< count ; j++){
    for(int i = 0; i <= strlen(div); i++){
      then[i] = xor(temps[i],data_div[1]);
    }
    for(int i = 0; i < strlen(div); i++){
      temps[i] = then[i];
    }
  }
  for(int i = 0; i < strlen(div); i++){
      printf("%d",then[i]);
  }
}
