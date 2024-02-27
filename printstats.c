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

void swapf(float* a, float* b) 
{
  float temp = *a;
  *a = *b;
  *b = temp;
}

void bsort(int n, float* arr) {
    int i, j;
    for (i = 0; i < n - 1; i++)        
        for (j = 0; j < n - i - 1; j++)  
            if (arr[j] > arr[j + 1])
                swapf(&arr[j], &arr[j + 1]);
}

double median(int argc, char** argv)
{
  //argv in an array 
  float arr[argc - 1];
  for(int i = 1; i < argc; i++) {
    arr[i - 1] = atof(argv[i]);
  }

  bsort(argc - 1, arr); 


  if((argc - 1) % 2 == 0) {
    float x = arr[(argc - 1)/2];
    float z = arr[(argc - 1)/2 + 1];
    printf(1, "median: %f\n", x); //
    printf(1, "median: %f\n", z); //

    float res = (x + z) / 2.0;
    return res; 
  }
  else {
    float x = arr[(argc)/2];
    printf(1, "median: %f\n", x); //
    return x;
  }
  return 0;
}

double average(int argc, char** argv)
{
  float sum = 0;
  for(int i = 1; i < argc; i++)
  {
    sum += atof(argv[i]);
  }
  return sum / (float)(argc - 1);
}

double min(int argc, char** argv)
{
  float min = atof(argv[1]);
  for(int i = 1; i < argc; i++) {
    if(atof(argv[i]) <= min) { 
      min = atof(argv[i]);
    }
  }

  return min;
}

double max(int argc, char** argv)
{
  float max = atof(argv[1]);
  for(int i = 1; i < argc; i++) {
    if(atof(argv[i]) >= max) { 
      max = atof(argv[i]);
    }
  }

  return max;
}

// AW: sqrt implementation, based on Quakes Fast Inverse Square Root algorithm
// https://betterexplained.com/articles/understanding-quakes-fast-inverse-square-root/

float sqrt(float x) {
  float xhalf = 0.5f * x;
  int i = *(int*)&x;
  i = 0x5f3759df - (i >> 1);
  x = *(float*)&i;
  x = x*(1.5f - xhalf*x*x); // newtons Method 1st iteration
  x = x*(1.5f - xhalf*x*x); // 2nd iteration
  x = x*(1.5f - xhalf*x*x); // 3rd iteration 98%
  return 1/x;               // changed to get sqrt
}

float stdDev(int argc, char** argv) {
  float avg = average(argc, argv);
  float sum = 0;
  for(int i = 1; i < argc; i++) {
    sum += (atof(argv[i]) - avg) * (atof(argv[i]) - avg);
  }
  return sqrt(sum / (argc - 1));
}

int main (int argc, char** argv) {
  printf(1, "average: %f\n", average(argc, argv)); 
  printf(1, "median: %f\n", median(argc, argv)); 
  printf(1, "max: %f\n", max(argc, argv)); 
  printf(1, "min: %f\n", min(argc, argv)); 
  printf(1, "stdDev: %f\n", stdDev(argc, argv));

  exit();
  return 0;
}


