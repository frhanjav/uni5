#include <stdio.h>

int main()
{
  int arr[6] = {9, 23, 56, 60, 74, 90};
  int half = (6 + 1) / 2;
  int s = 74;
  for (int i = 0; i < half; i++)
  {
    if (s == arr[half])
    {
      i = 0;
      printf("Found at %d\n", half);
      return 0;
    }
    if (s > arr[half])
    {
      i = 0;
      continue;
    }
    else
    {
      i = 0;
      continue;
    }
    half = half / 2;
  }
  printf("not found\n");
  return 0;
}