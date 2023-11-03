## Object
* 和 C Struct 一样，c++ 中 function 虽然在类的声明中，但却不在 object 中，每一个 non-inline 函数只会诞生一个实例。   
* 一个 object 包含一系列的 slot，每个 slot 对应着一个成员
* C++ 对象模型成员的存放
  - 对象的 non-static data members 存放在每一个 object 文件中
  - 对象的 static data members 存放在某一个 object 文件中
  - 对象的 static 和 non-static functions 存放在某一个 object 文件中
* virtual table
  - 只有包含 虚函数 的对象才会有 vt
  - 类的每个对象有自己的 vt
  - vt 包括一系列指向虚函数的指针 和 type_info 信息
  - vt 对程序员不可见，由编译器在 construct/destructor/copy construct 中赋值
* 指向不同类型的指针差异不在地址，而在于如何解释这个地址中内存的内容