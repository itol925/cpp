## constructor
* 如果程序员没有定义任何构造函数，那么会有一个隐式的默认构造函数定义出来，注意这个隐式的构造函数是无用的（trivial）,它不会帮你初始化成员
* global objects 会在程序启动时候被清 0；local objects 在堆或栈中，不会被清 0，而是上一次内存使用后的值
* 编译器在以下 4 种情况下会合成一个有用的默认构造函数（_注：有用是指对编译器有用，非程序员_）
  - 成员有 default constructor 时
  - 基类有 default constructor 时
  - 有 virtual functions 时
  - 有 virtual base class 时
  
  _注：不属于上述 4 种情况，且没有显式声明任何 constructor 的类，只能说它拥有 隐式无用的
  默认构造函数（implicit trivial default constructor），实际上并不会被合成出来_
  
  _注：在合成的 default constructor 中，只有 base class subobjects 和 member class objects 会被初始化，
  其他非静态成员（如int，指针）都不会被初始化_
* 有 3 种情况会触发 copy 操作
  - 当一个对象以值传递的方式传入函数时。如：
  ```
  void func(X x) { }
  ```
  - 当一个对象以值传递的方式从函数返回时。如：
  ```
  X getObj() {
      X x; 
      return x; 
  } // 如果X实现了 copy constructor 的话会被 返回值优化 掉
  ```
  - 当一个对象需要通过另一个对象进行初始化时。如:
  ```
  X x = xx; 
  X x(xx);
  ```
* 有 4 种情况不能够被位逐次拷贝（Bitwise Copy Semantics）
  - 类有 copy constructor 时（不论是显式声明的还是编译器合成的）
  - 基类有 copy constructor 时
  - 有 virtual functions 时
  - 有 virtual base class 时
* 如果类声明了 virtual function，那么在编译期间，编译器会为类增加 2 件东西：
  - 一张 vtbl(virtual function table)。注：vtbl 只有一份
  - 为每一个类的 object 增加一个 vtbl 指针
* 构造函数中初始化成员的陷阱
  ```
  class Word {
  private:
      String name;
      int cnt;
  public:
      Word() {
          name = 0;
          cnt = 0;
      }
  };
  ```
  上面的代码虽然编译没有问题，但是 name 成员在赋值的时候会产生一个临时对象！展开后的代码如下：
  ```
  class Word {
  private:
      String name;
      int cnt;
  public:
      Word() {
          name.String::String(); // 调用 String 的 default constructor
          String temp = String(0); // 产生临时对象
          name.String::operator=(temp); // copy
          temp.String::~String(); // 析构
          cnt = 0;
      }
  };
  ```
  如果使用初始化成员列表（member initialization list）的话，则不会有上面的问题
  ```
  class Word {
  private:
      String name;
      int cnt;
  public:
      Word() : name(0) {
          // name 赋值展开后的代码为：
          // name.String::String(0);
          cnt = 0;
      }
  };
  ```
  注：member initialization list 成员顺序需要和 成员在类中声明的顺序一致
* 对于类 X 和类 Y，Y 的析构函数最后会被编译器扩充加上 X 的析构函数的调用，如下：
  ```
  class X {
  public:
    X() {
      str = new char[1024];
    }
    ~X() {
      delete str;
    }
  private:
      char* str;
  };
  class Y : public X {
  public:
    Y() {
      str1 = new char[1024];
    }
    ~Y() {
      delete str1;
      // X::~X(); 注：这里编译器会在 Y 的析构函数后 加上父类 X 析构函数的调用
    }
  private:
      char* str1;
  };
  ```
  