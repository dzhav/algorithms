#include <iostream>

int QuickSelect(int* buffer, int n, int k) {
  if (n == 1) {
    return buffer[0];
  }
  int pivot = buffer[n/2];
  int one_size = 0;
  int two_size = 0;
  for (int i = 0; i < n; i++) {
    if (buffer[i] < pivot) {
      one_size++;
    }
    if (buffer[i] > pivot) {
      two_size++;
    }
  }
  if (k < one_size) {
    //delete[] two_arr ;
    int* new_buffer = new int[one_size]; int cnt = 0;
    for (int i = 0; i < n; i++){
      if (buffer[i] < pivot){
        new_buffer[cnt] = buffer[i]; cnt++;
      }
    }
    QuickSelect(new_buffer, one_size, k);
  }
  else {
    if (k >= one_size and k < n - two_size) {
      return pivot;
    }
    else {
      int* new_buffer = new int[two_size]; int cnt = 0;
      for (int i = 0; i < n; i++){
        if (buffer[i] > pivot){
          new_buffer[cnt] = buffer[i]; cnt++;
        }
      }
      QuickSelect(new_buffer, two_size, k - n + two_size);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  std::cin >> n;
  int k;
  std::cin >> k;
  int* buffer = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> buffer[i];
  }
  std::cout << QuickSelect(buffer, n, k);
  delete[] buffer;
}