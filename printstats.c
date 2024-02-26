#include "types.h"
#include "user.h"
// AW

int isNumeric(char* s){
  while(*s != '\0') {
    if(*s < '0' || *s > '9') {return 0;};
    s++;
  }
  return 1;
}

char checkArgs(int argc, char** argv) {
  char flagged = 0; // AW: char here used as a bool
  for(int i = 1; i < argc; i++) { 
      if(!isNumeric(argv[i])) {
          printf(1, "Argument %d is not numeric: %s\n", i, argv[i]);
          flagged = 1;
      }
  }

  return flagged;
}

void swap(void* a, void* b) 
{
  void* temp = a;
  a = b;
  b = temp;
}

void bsort(int argc, char* argv[]) {
  int i, j;
  for (i = 1; i < argc - 1; i++) {      
    for (j = 1; j < argc - i; j++) {
      float a = atof(argv[j]);
      float b = atof(argv[j + 1]);
      if (a > b) {
        swap(&argv[j], &argv[j+1]);
      }
    }
  }
}

float median(int argc, char* argv[])
{
  if (checkArgs(argc, argv)) {exit();}
  bsort(argc, argv);

  if((argc - 1) %2 == 0) {
    return atof(argv[(argc-1)/2]) + atof(argv[(argc-1/2 + 1)]) / 2;
  }
  else {
    return atof(argv[(argc-1)/2]);
  }
  return 0;
}

float average(int argc, char* argv[])
{
  if (checkArgs(argc, argv)) {exit();}
  float sum = 0;
  for(int i = 1; i < argc; i++)
  {
    sum += atoi(argv[i]);
  }
  return sum / (float)(argc - 1);
}


int main (int argc, char * argv[]) {
  printf(1, "average: %f\n", average(argc, argv)); //AW: default float percision is 4 dec
  printf(1, "median: %.7f\n", median(argc, argv)); //AW: default float percision is 4 dec

  exit();
}


