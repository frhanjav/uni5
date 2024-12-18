#include <bits/stdc++.h>
using namespace std;

void combinationSum(int ind, int arr[], vector<int> &ds, int target, vector<vector<int> > &can, int n)
{

  // base case
  if (ind >= n)
  {
    if (target == 0)
    {
      can.push_back(ds);
    }
    return;
  }
  // pick
  if (arr[ind] <= target)
  {
    ds.push_back(arr[ind]);
    combinationSum(ind, arr, ds, target - arr[ind], can, n);
    ds.pop_back();
  }

  // not pick
  combinationSum(ind + 1, arr, ds, target, can, n);
}

int main()
{
  int arr[] = {2, 3, 6, 7};
  int n = 4;
  int target = 7;
  vector<vector<int> > can;
  vector<int> ds;
  combinationSum(0, arr, ds, target, can, n);

  for (const auto &combination : can)
    {
        for (int num : combination)
        {
            cout << num << " ";
        }
        cout << endl;
    }
  return 0;
}