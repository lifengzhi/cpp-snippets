// http://www.nuonsoft.com/blog/2017/08/10/implementing-a-thread-safe-singleton-with-c11-using-magic-statics/
// http://blog.mbedded.ninja/programming/languages/c-plus-plus/magic-statics

#include <iostream>

class CSingleton final {
 public:
  static CSingleton& GetInstance();
  int getValue() const { return mValue; }

 private:
  CSingleton() = default;
  ~CSingleton() = default;

  CSingleton(const CSingleton&) = delete;
  CSingleton& operator=(const CSingleton&) = delete;
  CSingleton(CSingleton&&) = delete;
  CSingleton& operator=(CSingleton&&) = delete;

  int mValue = 0;
};

CSingleton& CSingleton::GetInstance() {
  static CSingleton instance;
  return instance;
}

int main() {
  auto const value{CSingleton::GetInstance().getValue()};
  std::cout << value << '\n';
}
