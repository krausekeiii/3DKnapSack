// KnapsackProgrammingProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

//INT_MAX will be used to represent infinity, and INT_MIN for negative infinity

//param S is for size, substituted for "l" for readability
//returns subset of items whose size is exactly S and weight exactly W (i.e., traceback function included)
vector<int> knapSack(const vector<int>&weights, const vector<int>& values, const int W, const int S) {
    if (weights.size() != values.size()) {
        cout << "Size of weight vector and values vector must be the same!" << endl;
        return {};
    }

    //inititalize 3D memoization object w/ values of 0
    vector<vector<vector<int>>> mem(weights.size(),  vector<vector<int>>(W+1, vector<int>(S+1)));

    //begin bottom-up eval
    for (int i = 0; i < weights.size(); i++) {
        for (int w = 0; w <= W; w++) {
            for (int k = 0; k <= S; k++) {
                //first 3 cases of OPT(i,w,k)
                if (i < k || (w > 0 && k == 0) || (w == 0 && k > 0)) mem[i][w][k] = INT_MIN;
                //4th case
                else if (w == 0 && k == 0) mem[i][w][k] = 0;
                //5th case
                else if (weights[i] > w) mem[i][w][k] = mem[i - 1][w][k];
                //6th case
                else mem[i][w][k] = max( mem[i - 1][w][k], (values[i] + mem[i - 1][w - weights[i]][k-1]) );
            }
        }
    }

    //begin traceback to find possible solution
    int wi = W, s = S, n = weights.size() - 1;
    vector<int> chosen;

    while (n > 0 && wi > 0 && s > 0) {
        if (mem[n][wi][s] != mem[n - 1][wi][s]) {
            chosen.push_back(n);
            wi -= weights[n];
            s -= 1;
        }
        n -= 1;
    }

    //double check if size is desired size and weight
    if (chosen.size() != S || wi != 0) {
        cout << "Combination with desired size " << S << " is not possible with weight restriction " << W;
        return {};
    }

    return chosen;
}



int main()
{
    int size = 5;
    int weight = 13;
    vector<int> weights = { 0,1,3,3,3,4 };
    vector<int> values = { 0,1,2,3,3,4 };

    vector<int> chosen = knapSack(weights, values, weight, size);

    if (chosen.size() == size) {
        cout << "Index (or Indices) of desired item amount that add(s) up to desired weight:\n";
        for (int i = chosen.size() - 1; i >= 0; --i) {
            cout << chosen[i] << " ";
        }
    }
    
    return 0;
}
