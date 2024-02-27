#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int mypid = getpid();
  printf(1, "Process pid: %d\n", mypid);
  char* myname;
  myname = getpname(mypid);
  printf(1, "Process name: %s\n", myname);
  int parentpid = getparentpid();
  printf(1, "Parent pid: %d\n", parentpid);
  char *parentname;
  parentname = getpname(parentpid);
  printf(1, "Parent name: %s\n", parentname);
  exit();
}