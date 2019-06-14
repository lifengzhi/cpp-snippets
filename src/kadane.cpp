// https://medium.com/@rsinghal757/kadanes-algorithm-dynamic-programming-how-and-why-does-it-work-3fd8849ed73d

#include <climits>
#include <vector>

int maxSumSubArray(std::vector<int> const &A) {
  int n = A.size();
  int local_max = 0;
  int global_max = INT_MIN;

  for (int i = 0; i < n; i++) {
    local_max = std::max(A[i], A[i] + local_max);
    if (local_max > global_max) {
      global_max = local_max;
    }
  }

  return global_max;
}

int main() {
  std::vector<int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  return maxSumSubArray(v);
}
