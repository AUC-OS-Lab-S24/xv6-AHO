#include "types.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char *argv[]) {

  // Create a file
  int fd = open("test.txt", O_CREATE | O_RDWR);
    
  // writing 25 blocks of data to the file
  for(int i = 0; i < 5*512; i++) {
    write(fd, '1', 5);
  }


  // Truncate the file to 10 blocks
  truncate("test.txt", 10);
  close(fd);
  exit();
}