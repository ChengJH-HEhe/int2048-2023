#include "int2048.h"

namespace sjtu {

int2048::int2048() { f = 1;}
int2048::int2048(long long x) {
  f = 1;
  if(x) {
    if(x < 0) {
      f = -1;
      x = -x;
    }
    while(x) {
      v.push_back(x % 1000);
      x /= 1000;
    }
  }
}
int2048::int2048(const std::string &c) {
  int cnt = 0, va = 0, sz = c.size();
  f = 1;
  for(int i = sz - 1; ~i; i--) {
    if(c[i] == '-') f = -1;
    else {
      if ((++cnt) == 4) {
        v.push_back(va);
        va = c[i]-'0', cnt = 1;
      } else {
        va +=(c[i]^48) * pw[cnt-1];
      } 
    }
  }
  if(cnt) v.push_back(va);
  // for(auto va : v)
  //   std::cout << va << std::endl;
}
int2048::int2048(const int2048 &b) {
  f = b.f, v = b.v;
}

  // 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
  // 如果需要，可以自行增加其他所需的函数
  // ===================================
  // Integer1
  // ===================================

  // 读入一个大整数
void int2048::read(const std::string &b) {
  int2048 tmp = int2048(b);
  f = tmp.f, v = tmp.v;
}
  // 输出储存的大整数，无需换行
void int2048::print() {
  if(f == -1) std::cout << '-';
  for(auto it = --v.end(); ; --it) {
    std::cout << *it ;
    if(it == v.begin()) {
      return;
    }
  }
}

int int2048::cmp(std::vector<int> a, std::vector<int> b) {
  int sza = a.size(), szb = b.size();
  if(sza != szb) {
    return (sza<szb) ? -1:1;
  }
  for(int i = sza-1; ~i; --i) 
    if(a[i]!=b[i]) 
      return (a[i]<b[i]) ? -1:1;
  return 0;
}
  // 加上一个大整数
int2048 &int2048::uadd(const int2048 &a) {
  //符号不同，变减法，大的减小的符号是大的， *this换成大的，
  v.resize(std::max(v.size(), a.v.size()));
  //*this.print();
  return *this;
}

int2048 &int2048::add(const int2048 &a) {
  //符号不同，变减法，大的减小的符号是大的， *this换成大的，
  int sz1 = v.size(), sz2 = a.v.size();
  if(f != a.f) {
    int pd = cmp(v,a.v);
    if(!pd) {
      f = 1;
      return *this;
    }
    if(pd == -1) {
      int2048 c(*this);
      v = a.v, f = a.f;
    } else if(pd) {
      
    }
  }
  return *this;
}
  // 返回两个大整数之和
int2048 add(int2048 a, const int2048 &b) {
  return a.add(b);
}

  // 减去一个大整数
int2048 &int2048::minus(const int2048 &a) {
  
  return *this;
}
  // 返回两个大整数之差
int2048 minus(int2048 a, const int2048 &b) {
  return a.minus(b);
}
} // namespace sjtu

int main() {
  std::ios::sync_with_stdio(false);
  std::string a;
  std::cin >> a;
  sjtu::int2048 b; 
  b.read(a);
  b.print();
}