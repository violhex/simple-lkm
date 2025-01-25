#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int dev = open("/dev/laplas", O_RDONLY);
  if (dev == -1)
  {
    printf("[LC ~ ERROR] - Opening was not possible.\n");
    return -1;
  }
  printf("[LC] - Successfully Opened NULLV.\n");
  close(dev);
  return 0;
}


