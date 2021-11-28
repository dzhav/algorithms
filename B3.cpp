/*
 * Фаталиев Джавид Б05-125
 * Задача B - 2-ой контест
 * Реализуйте структуру данных из n элементов a1,a2…an, поддерживающую следующие операции:

присвоить элементу ai значение j;
найти знакочередующуюся сумму на отрезке от l до r включительно (al−al+1+al+2−…±ar).
Входные данные
В первой строке входного файла содержится натуральное число n (1≤n≤105) — длина массива. Во второй строке записаны начальные значения элементов (неотрицательные целые числа, не превосходящие 104).

В третьей строке находится натуральное число m (1≤m≤105) — количество операций. В последующих m строках записаны операции:

операция первого типа задается тремя числами 0 i j (1≤i≤n, 1≤j≤104).
операция второго типа задается тремя числами 1 l r (1≤l≤r≤n).*/

#include <iostream>
#include <vector>

int next_2_degree(int value) {
  int i = 0;
  while (value >> i) ++i;
  return 1 << i;
}

class Tree_summa {
 private:
  std::vector<int> mini;
  void build(int index, int left, int right) {
    if (left == right) {
      return;
    }
    int mid = (left + right) / 2;
    build(2 * index + 1, left, mid);
    build(2 * index + 2, mid + 1, right);
    mini[index] = (mini[2 * index + 1] + mini[2 * index + 2]);
  }
  int sum(int index, int i_left, int i_right, int left, int right) {
    if (right < i_left) {
      return 0;
    }
    if (i_right < left) {
      return 0;
    }
    if (left <= i_left && i_right <= right) {
      return mini[index];
    }
    int mid = (i_left + i_right) / 2;
    return (sum(2 * index + 1, i_left, mid, left, right) +
        sum(2 * index + 2, mid + 1, i_right, left, right));
  }
  void update(int index, int left, int right, int val, int pos) {
    if (left == right) {
      mini[index] = val;
      return;
    }
    int mid = (left + right) / 2;
    if (pos <= mid) {
      update(2 * index + 1, left, mid, val, pos);
    } else {
      update(2 * index + 2, mid + 1, right, val, pos);
    }
    mini[index] = (mini[2 * index + 1] + mini[2 * index + 2]);
  }
 public:
  Tree_summa(const std::vector<int> &arr) : mini(next_2_degree(arr.size()) * 2, 0) {
    std::copy(arr.begin(), arr.end(), mini.begin() + mini.size() / 2 - 1);
    build(0, 0, mini.size() / 2 - 1);
  }
  int Sum(int left, int right) {
    if (left % 2 == 1) {
      return sum(0, 0, mini.size() / 2 - 1, left, right) * -1;
    } else {
      return sum(0, 0, mini.size() / 2 - 1, left, right);
    }
  }
  void Update(int val, int pos) {
    if (pos % 2 == 1) {
      update(0, 0, mini.size() / 2 - 1, -1 * val, pos);
    } else {
      update(0, 0, mini.size() / 2 - 1, val, pos);
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  for (int i = 1; i < n; i += 2) {
    a[i] *= -1;
  }
  Tree_summa tree(a);
  for (int i_ = 0; i_ < m; i_++) {
    int x;
    std::cin >> x;
    if (x == 1) {
      int i;
      int j;
      std::cin >> i >> j;
      std::cout << tree.Sum(i - 1, j - 1) << "\n";
    } else {
      int l;
      int r;
      std::cin >> l >> r;
      tree.Update(r, l - 1);
    }
  }
}