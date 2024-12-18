#include <stdio.h>

int main()
{
  int arr[4] = {10, 50, 79, 54};
  int a = 50;
  int term = 0;
  for (int i = 0; i < 4; i++)
  {
    if (arr[i] == a)
    {
      printf("Found! Item is at %d \n", (i + 1));
      break;
    }
  }
  return 0;
}