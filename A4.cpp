#include <iostream>
#include <string>

using std::cout;
using std::cin;

class AVL_tree {
 public:
  explicit AVL_tree(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
  AVL_tree *insert(AVL_tree *p, int k);
  bool findkey(AVL_tree *p, int key);
  static std::string next(AVL_tree *p, int k);
  std::string prev(AVL_tree *p, int k);
  AVL_tree *remove(AVL_tree *p, int k);
  ~AVL_tree();
 private:
  static int true_height(AVL_tree *p);
  static int bifactor(AVL_tree *p);
  void fixheight(AVL_tree *p);
  AVL_tree *rotateright(AVL_tree *p);
  AVL_tree *rotateleft(AVL_tree *q);
  AVL_tree *balance(AVL_tree *p);
  AVL_tree *findmin(AVL_tree *p);
  AVL_tree *removemin(AVL_tree *p);
  int height;
  AVL_tree *left;
  AVL_tree *right;
  int key;
};

int AVL_tree::true_height(AVL_tree *p) {
  if (p != nullptr) {
    return p->height;
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

AVL_tree *AVL_tree::rotateright(AVL_tree *p) {
  AVL_tree *q = p->left;
  p->left = q->right;
  q->right = p;
  fixheight(p);
  fixheight(q);
  return q;
}

AVL_tree *AVL_tree::rotateleft(AVL_tree *q) {
  AVL_tree *p = q->right;
  q->right = p->left;
  p->left = q;
  fixheight(q);
  fixheight(p);
  return p;
}

AVL_tree *AVL_tree::balance(AVL_tree *p) {
  fixheight(p);
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
  if (p->left) {
    return findmin(p->left);
  } else return p;
}

bool AVL_tree::findkey(AVL_tree *p, int key) {
  if (p == nullptr) {
    return false;
  }
  if (key < p->key) {
    findkey(p->left, key);
  } else {
    if (key == p->key) {
      return true;
    } else {
      findkey(p->right, key);
    }
  }
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

std::string AVL_tree::next(AVL_tree *p, int k) {
  if (p == nullptr) {
    return "none";
  }
  AVL_tree *pip = p;
  AVL_tree *otv = nullptr;
  while (pip != nullptr) {
    if (pip->key > k) {
      otv = pip;
      pip = pip->left;
    } else {
      pip = pip->right;
    }
  }
  if (otv == nullptr) {
    return "none";
  } else {
    return std::to_string(otv->key);
  }
}

std::string AVL_tree::prev(AVL_tree *p, int k) {
  if (p == nullptr) {
    return "none";
  }
  AVL_tree *pip = p;
  AVL_tree *otv = nullptr;
  while (pip != nullptr) {
    if (pip->key >= k) {
      pip = pip->left;
    } else {
      otv = pip;
      pip = pip->right;
    }
  }
  if (otv == nullptr) {
    return "none";
  } else {
    return std::to_string(otv->key);
  }
}
AVL_tree::~AVL_tree() {
  left = nullptr;
  right = nullptr;
  height = 0;
  key = 0;
}

int main() {
  AVL_tree *L = nullptr;
  std::string s;
  while (cin >> s) {
    int k;
    cin >> k;
    if (s == "insert") {
      if (!L->findkey(L, k)) {
        L = L->insert(L, k);
      }
    }
    if (s == "exists") {
      if (L->findkey(L, k)) {
        cout << "true\n";
      } else {
        cout << "false\n";
      }
    }
    if (s == "delete") {
      if (L->findkey(L, k)) {
        L = L->remove(L, k);
      }
    }
    if (s == "next") {
      cout << L->next(L, k) << "\n";
    }
    if (s == "prev") {
      cout << L->prev(L, k) << "\n";
    }
  }
}