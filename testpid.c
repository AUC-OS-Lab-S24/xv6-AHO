#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  printf(1, "Process pid: %d\n", getpid());
  // char myname[16];
  // getpname(getpid());
  // printf(1, "Process name: %s\n", myname);
  // printf(1, "Parent pid: %d\n", getparentpid());
  // char parentname[16];
  // getpname(getparentpid());
  // printf(1, "Parent name: %s\n", parentname);
  exit();
}