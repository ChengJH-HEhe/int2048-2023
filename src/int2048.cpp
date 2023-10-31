#include "int2048.h"


namespace sjtu {



int2048::int2048() {f = 1;v.clear();}
int2048::int2048(long long x) {
  f = 1;v.clear();
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
  f = 1; v.clear();
  for(int i = sz - 1; i >= 0; i--) {
    if(c[i] == '-') f = -1;
    else {
      if ((++cnt) == bit + 1) {
        v.push_back(va);
        va = c[i]-'0', cnt = 1;
      } else {
        va +=(c[i]^48) * pw[cnt-1];
      } 
    }
  }
  if(cnt) v.push_back(va);
  if(!(*v.begin()) && int(v.size()) == 1)
    v.resize(0);
}
int2048::int2048(const int2048 &b) {
  f = b.f, v = b.v;
}

int2048 &int2048::uadd(const int2048 &a) {
  if(a.v.empty()) {
    return *this;
  }
  int sz = v.size(), sza = a.v.size(), tmp = 0;
  if(sz < sza)v.resize(sza), sz = sza;

  for(int i = 0; i < sz-1; ++i) {
    (i<sza) && (v[i] += a.v[i]);
    v[i]+=tmp; 
    tmp = v[i]/base;
    v[i] %= base;
  }
  int pos = sz-1;
  (sz-1<sza)&&(v[sz-1] += a.v[sz-1]);
  v[sz-1]+=tmp;
  while(v[pos] >= base) {
    v.push_back(v[pos]/base);
    v[pos] %= base;
    ++pos;
  }
  return *this;
}

int2048 &int2048::uminus(const int2048 &a) {
  if(a.v.empty() ) {
    return *this;
  }
  int sz = v.size(), sza = a.v.size(), tmp = 0;
  for(int i = 0; i < sz; ++i) {
    (i < sza) && (v[i] -= a.v[i]);
    if(v[i]<0){
      v[i]+=base;
      v[i+1]--;
    }
  }
  sz = v.size();
  while(v[sz-1] == 0 && sz) --sz;
  v.resize(sz);
  return *this;
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
  //std::assert(v.empty());
  if(v.empty()) {
    std::cout << '0'; 
    return;
  }
  if(f == -1) std::cout << '-';
  std::cout << *(--v.end());
  if(v.size() == 1) return;
  for(auto it = --(--v.end()); ; --it) {
    if(*it<10) std::cout << '0';
    if(*it<100) std::cout << '0';
    if(*it<1000) std::cout << '0';
    std::cout << *it;
    if(it == v.begin()) return;
  }
}
void fft(std::vector<int> &a, std::vector<int> b) {

}
int cmp(std::vector<int> a, std::vector<int> b) {
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

int2048 &int2048::add(const int2048 &a) {
  //符号不同，变减法，大的减小的符号是大的， *this换成大的，
  if(f != a.f) {
    int pd = cmp(v,a.v);
    if(!pd) {
      f = 1;
      v.resize(0);
      return *this;
    } 
    if(pd == -1) {
      int2048 c(*this);
      v = a.v, f = a.f;
      (*this).uminus(c);
    } else {
      (*this).uminus(a);
    } 
  } else {
    (*this).uadd(a);

  }
  return *this;
}
  // 返回两个大整数之和
int2048 add(int2048 a, const int2048 &b) {
  return a.add(b);
}

  // 减去一个大整数
int2048 &int2048::minus(const int2048 &a) {
  if(f == a.f) {
    int pd = cmp(v,a.v);
    if(!pd) {
      f = 1;
      v.resize(0);
      return *this;
    } 
    if(pd == -1) {
      
      int2048 c(*this);
      v = a.v, f = -f;
      (*this).uminus(c);
    } else {
      (*this).uminus(a);
    } 
  } else {
    
    (*this).uadd(a);
  }
  return *this;
}
  // 返回两个大整数之差
int2048 minus(int2048 a, const int2048 &b) {
  return a.minus(b);
}

//重载运算符

int2048 int2048::operator+() const {
  return *this;
}
int2048 int2048::operator-() const {
  int2048 c(*this);
  c.f = -c.f;
  return c;
}

int2048& int2048::operator=(const int2048 &b) {
  return (*this = b);
}

int2048& int2048::operator+=(const int2048 &b) {
  return (*this).add(b);
}
int2048 operator+(int2048 a, const int2048 &b) {
  a += b;
  return a;
}

int2048& int2048::operator-=(const int2048 &b) {
  return this->minus(b);
}
int2048 operator-(int2048 a, const int2048 &b) {
  a -= b;
  return a;
}

int2048& int2048::operator*=(const int2048 &b) {
  fft((*this).v,b.v);
  this->f *= b.f;
  return *this;
}
int2048 operator*(int2048 a, const int2048 &b) {
  a *= b;
  return a;
}

int2048& int2048::operator/=(const int2048 &b){
  return *this;
}
int2048 operator/(int2048 a, const int2048 &b){
  return a /= b;
}

int2048& int2048::operator%=(const int2048 &b) {
  return a -= (a/b) * b;
}
int2048 operator%(int2048 a, const int2048 &b) {
  return a %= b;
}

std::istream &operator>>(std::istream &in, int2048 &b) {
  std::string s;
  in >> s;
  b = int2048(s);
  return in;
}
std::ostream &operator<<(std::ostream &out, const int2048 &b) {
  if(b.v.empty()) {
    out << '0'; 
  } else {
    if(b.f == -1) out << '-';
    out << *(--b.v.end());
    if(b.v.size() != 1)
      for(auto it = --(--b.v.end()); ; --it) {
        if(*it<10) out << '0';
        if(*it<100) out << '0';
        out << *it;
        if(it == b.v.begin()) break;
      }
  }
  return out;
}

bool operator<(const int2048 &a, const int2048 &b) {
  if(a.f != b.f) {
    return a.f < b.f;
  } else {
    return (cmp(a.v, b.v) * a.f == -1)? 1 : 0;
  }
}
bool operator==(const int2048 &a, const int2048 &b) {
  if(a.f != b.f || a.v.size() != b.v.size()) 
    return false;
  return (cmp(a.v,b.v) == 0) ? 1:0;
}
bool operator!=(const int2048 &a, const int2048 &b) {
  return !(a == b);
}
bool operator>(const int2048 &a, const int2048 &b) {
  if(a.f != b.f) {
    return a.f > b.f;
  } else {
    return (cmp(a.v, b.v) * a.f == 1)? 1 : 0;
  }
}
bool operator<=(const int2048 &a, const int2048 &b) {
  return (a < b || a == b);
}
bool operator>=(const int2048 &a, const int2048 &b) {
  return (a > b || a == b);
}

}
std::string s1, s2;sjtu::int2048 a, b;
int main()
{
    std::ios::sync_with_stdio(0);
      freopen("3.in","r",stdin);
      freopen("1.txt","w",stdout);
    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> s1 >> s2;
        a.read(s1); b.read(s2);
        minus(a, b).print(); std::cout<<std::endl;
        a.minus(b).print(); std::cout<<std::endl;
        (add(a, b)).minus(a.add(b).minus(a).add(b)).print(); std::cout<<std::endl;
    }
}