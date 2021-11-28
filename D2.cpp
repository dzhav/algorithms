#include <iostream>
#include <algorithm>
#include <cstring>

class Heap{
 private:
  long long *buffer;
  long long *node;
  long long *point;
  long long buffer_size;
  long long size_two;
  long long size;
  long long iter;
  void GrowQuery();
  void GrowBuffer();
  void SiftUp(long long v);
  void SiftDown(long long v);
 public:
  Heap(){
    size_two = 1000;
    iter = 0;
    node = new long long[size_two];
    point = new long long[size_two];
    buffer_size = 1000;
    size = 0;
    buffer = new long long[buffer_size];
  }
  ~Heap(){
    delete[] point;
    delete[] node;
    delete[] buffer;
  }
  void Insert(long long x);
  long long GetMin();
  void ExtractMin();
  void DecreaseKey(long long i, long long delta);
};

void Heap::DecreaseKey(long long i, long long delta) {
  if (iter + 1 >= size_two){
    GrowQuery();
  }
  iter++;
  long long bolt = point[i];
  buffer[bolt] = buffer[bolt] - delta;
  SiftUp(bolt);
}

void Heap::GrowQuery() {
  size_two = size_two * 2;
  auto* new_node = new long long[size_two];
  auto* new_point = new long long[size_two];
  memcpy(new_node, node, (iter + 1) * sizeof(long long));
  memcpy(new_point, point, (iter + 1) * sizeof(long long));
  delete[] node;
  delete[] point;
  node = new_node;
  point = new_point;
}

void Heap::GrowBuffer() {
  buffer_size = buffer_size * 2;
  auto* new_buffer = new long long[buffer_size];
  std::memcpy(new_buffer, buffer, (size+1)* sizeof(long long));
  delete[] buffer;
  buffer = new_buffer;
}

void Heap::SiftDown(long long v) {
  while (2 * v <= size) {
    long long u = 2 * v;
    if (((u+1) <= size) and (buffer[u+1] < buffer[u])) {
      u++;
    }
    if (buffer[u] < buffer[v]) {
      long long first = node[u];
      long long second = node[v];
      point[first] = v;
      point[second] = u;
      node[u] = second;
      node[v] = first;
      std::swap(buffer[u], buffer[v]);
      v = u;
    }
    else break;
  }
}

void Heap::SiftUp(long long v) {
  while(v >= 2) {
    if (buffer[v] < buffer[v/2]) {
      long long first = node[v];
      long long second = node[v/2];
      point[first] = v/2;
      point[second] = v;
      node[v] = second;
      node[v/2] = first;
      std::swap(buffer[v], buffer[v/2]);
      v/=2;
    }
    else break;
  }
}

void Heap::Insert(long long x) {
  if (size + 2 > buffer_size){
    GrowBuffer();
  }
  if (iter + 2 > size_two) {
    GrowQuery();
  }
  size++;
  iter++;
  buffer[size] = x;
  point[iter] = size;
  node[size] = iter;
  SiftUp(size);
}

long long Heap::GetMin() {
  if (iter + 2 > size_two) {
    GrowQuery();
  }
  iter++;
  return buffer[1];
}

void Heap::ExtractMin() {
  if (iter + 1 >= size_two) {
    GrowQuery();
  }
  iter++;
  long long first = node[1];
  long long second = node[size];
  point[first] = size;
  point[second] = 1;
  node[1] = second;
  node[size] = first;
  std::swap(buffer[1], buffer[size]);
  //buffer[size] = 1e10;
  size--;
  SiftDown(1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr); std::cout.tie(nullptr);
  int q;
  std::cin >> q;
  Heap lol;
  while(q--) {
    std::string s;
    std::cin >> s;
    if (s == "insert") {
      long long x;
      std::cin >> x;
      lol.Insert(x);
    }
    if (s == "getMin") {
      std::cout << lol.GetMin() << "\n";
    }
    if (s == "extractMin") {
      lol.ExtractMin();
    }
    if (s == "decreaseKey") {
      long long i;
      long long triangle;
      std::cin >> i >> triangle;
      lol.DecreaseKey(i, triangle);
    }
  }
  return 0;
}