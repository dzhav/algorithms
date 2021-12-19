#include <iostream>
#include <string>

using std::cout;
using std::cin;

class AVL_tree {
 public:
  explicit AVL_tree(int k) : size(1), height(1), key(k), left(nullptr), right(nullptr) {}
  AVL_tree *insert(AVL_tree *p, int k);
  AVL_tree *remove(AVL_tree *p, int k);
  int get_k_static(AVL_tree* p, int k);
 private:
  static int true_height(AVL_tree *p);
  static int bifactor(AVL_tree *p);
  void fixheight(AVL_tree *p);
  AVL_tree *rotateright(AVL_tree *p);
  AVL_tree *rotateleft(AVL_tree *q);
  AVL_tree *balance(AVL_tree *p);
  AVL_tree *findmin(AVL_tree *p);
  AVL_tree *removemin(AVL_tree *p);
  static int true_size(AVL_tree *p);
  void fixsize(AVL_tree *p);
  int size;
  int height;
  int key;
  AVL_tree *left;
  AVL_tree *right;
  ~AVL_tree();
};

int AVL_tree::get_k_static(AVL_tree *p, int k) {
  if (k == true_size(p->right) + 1){
    return p->key;
  }
  if ( k > true_size(p->right) + 1 ){
    return get_k_static(p->left, k - true_size(p->right) - 1);
  }
  if (k < true_size(p->right) + 1){
    return get_k_static(p->right, k);
  }
  //return 0;
}

int AVL_tree::true_height(AVL_tree *p) {
  if (p != nullptr) {
    return p->height;
  }
  return 0;
}

int AVL_tree::true_size(AVL_tree *p){
  if (p != nullptr) {
    return p->size;
  }
  return 0;
}

int AVL_tree::bifactor(AVL_tree *p) {
  return AVL_tree::true_height(p->right) - AVL_tree::true_height(p->left);
}

void AVL_tree::fixheight(AVL_tree *p) {
  int hl = true_height(p->left);
  int hr = true_height(p->right);
  p->height = std::max(hl, hr) + 1;
}

void AVL_tree::fixsize(AVL_tree *p){
  int hl = true_size(p->left);
  int hr = true_size(p->right);
  p->size = hl + hr + 1;
}

AVL_tree *AVL_tree::rotateright(AVL_tree *p) {
  AVL_tree *q = p->left;
  p->left = q->right;
  q->right = p;
  fixheight(p);
  fixsize(p);
  fixheight(q);

  fixsize(q);
  return q;
}

AVL_tree *AVL_tree::rotateleft(AVL_tree *q) {
  AVL_tree *p = q->right;
  q->right = p->left;
  p->left = q;
  fixheight(q);
  fixsize(q);
  fixheight(p);

  fixsize(p);
  return p;
}

AVL_tree *AVL_tree::balance(AVL_tree *p) {
  fixheight(p);
  fixsize(p);
  if (bifactor(p) == 2) {
    if (bifactor(p->right) < 0) {
      p->right = rotateright(p->right);
    }
    return rotateleft(p);
  }
  if (bifactor(p) == -2) {
    if (bifactor(p->left) > 0) {
      p->left = rotateleft(p->left);
    }
    return rotateright(p);
  }
  return p;
}

AVL_tree *AVL_tree::insert(AVL_tree *p, int k) {
  if (p == nullptr) return new AVL_tree(k);
  if (k < p->key)
    p->left = insert(p->left, k);
  else
    p->right = insert(p->right, k);
  return balance(p);
}

AVL_tree *AVL_tree::findmin(AVL_tree *p) {
  if (p->left != nullptr) {
    return findmin(p->left);
  } else return p;
}


AVL_tree *AVL_tree::removemin(AVL_tree *p) {
  if (p->left == nullptr) {
    return p->right;
  }
  p->left = removemin(p->left);
  return balance(p);
}

AVL_tree *AVL_tree::remove(AVL_tree *p, int k) {
  if (p == nullptr) {
    return nullptr;
  }
  if (k < p->key) {
    p->left = remove(p->left, k);
  } else {
    if (k > p->key) {
      p->right = remove(p->right, k);
    } else {
      AVL_tree *q = p->left;
      AVL_tree *r = p->right;
      delete p;
      if (r == nullptr) return q;
      AVL_tree *min = findmin(r);
      min->right = removemin(r);
      min->left = q;
      return balance(min);
    }
  }
  return balance(p);
}
AVL_tree::~AVL_tree() {
  left = nullptr;
  right = nullptr;
  height = 0;
  key = 0;
  size = 0;
}

int main() {
  AVL_tree *L = nullptr;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++){
    std::string c;
    cin >> c;
    int k;
    cin >> k;
    if (c == "+1" or c == "1"){
      L = L->insert(L, k);
    }
    if (c == "-1"){
      L = L->remove(L, k);
    }
    if (c == "0"){
      cout<<L->get_k_static(L, k)<<"\n";
    }
  }
}