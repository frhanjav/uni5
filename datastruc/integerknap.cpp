#include <iostream>
#include <vector>
using namespace std;

int knapSack(int ind, int W, int weight[], int profit[], int n, vector<int> &ds)
{
  if (ind >= n || n == 0 || W == 0)
  {
    int totalProfit = 0;

    for (int i = 0; i < ds.size(); i++)
    {
      totalProfit += profit[ds[i]];
    }
    return totalProfit;
  }

  if (weight[ind] > W)
  {
    return knapSack(ind + 1, W, weight, profit, n, ds);
  }

  ds.push_back(ind);
  int includeProfit = knapSack(ind + 1, W - weight[ind], weight, profit, n, ds);
  ds.pop_back();
  int excludeProfit = knapSack(ind + 1, W, weight, profit, n, ds);

  return max(includeProfit, excludeProfit);
}

int main()
{
  int profit[] = {60, 100, 120};
  int weight[] = {10, 20, 30};
  int W = 50;
  vector<int> ds;
  int n = sizeof(profit) / sizeof(profit[0]);
  cout << "Maximum profit: " << knapSack(0, W, weight, profit, n, ds) << endl;
  return 0;
}