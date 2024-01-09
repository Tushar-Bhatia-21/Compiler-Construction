#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int solution(vector<int> &A) {
    int n = A.size();
    int MAX_MOVES = 0;

    sort(A.begin(), A.end());

    for (int i = 0, j = n - 1; i <= j;) {
        int sum = A[i] + A[j];
        if (sum % 2 == 0) {
            int target = sum / 2;
            int count = 0;

            while (i <= j && A[i] == target) {
                i++;
                count++;
            }

            while (i <= j && A[j] == target) {
                j--;
                count++;
            }

            MAX_MOVES = max(MAX_MOVES, count);
        } else {
            // If the sum is odd, we can't form pairs with equal sum
            i++;
            j--;
        }
    }

    cout << MAX_MOVES;
    return MAX_MOVES;
}

int main() {
    // Example usage:
    vector<int> A = {4, 1, 4, 3, 3, 2, 5, 2};
    cout << "Result for A: " << solution(A) << endl; // Output: 4

    return 0;
}