#include <iostream>

long long Partition(long long a[], long long left, long long right) {
  long long pivot = a[(left + right) / 2];
  long long i = left;
  long long j = right;
  while(i <= j) {
    while (a[i] < pivot) {
      i++;
    }
    while (a[j] > pivot) {
      j--;
    }
    if (i >= j) break;
    std::swap(a[i], a[j]);
    i++;
    j--;
  }
  return j;
}

void QuickSort(long long a[], long long left, long long right) {
  if (left < right) {
    int pivot = Partition(a, left, right);
    QuickSort(a, left, pivot);
    QuickSort(a, pivot + 1, right);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  std::cin >> n;
  long long* buffer = new long long[n];
  for (int i = 0; i < n; i++) {
    std::cin >> buffer[i];
  }
  QuickSort(buffer, 0, n - 1);
  for (int i = 0; i < n; i++){
    std::cout<<buffer[i]<<" ";
  }
  delete[] buffer;
}