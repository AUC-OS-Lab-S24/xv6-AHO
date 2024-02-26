#include "types.h"
#include "user.h"

int main (int argc, char** argv[]) {
  float x = 3.822313;
  printf(1,"%f \n", x);

  x = -4.818231;
  printf(1, "%.8f \n", x);
  printf(1, "%.4f \n", x);
  exit();
}


