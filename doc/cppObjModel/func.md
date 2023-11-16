* 类的 nonstatic 成员函数会被隐式地传入一个 this 指针。比如：
  ```
  void Point3d::magnitude() {} 
  扩张为
  void Point3d::magnitude(Point3d *const this) {}
  
  void Point3d::magnitude() const() {}
  扩张为
  void Point3d::magnitude() const(const Point3d *const this) {}

  ```
  实际上，类的成员函数最终会被内化成非成员函数，成员函数的函数名会经过 "mangling" 处理成一个外部函数，像这样：
  ```
  extern magnitude__7Point3dFv(register Point3d *const this) {}
  ```
  于是 `obj.magnitude()` 最终变成了 `magnitude__7Point3dFv(&obj)`，`ptr->magnitude()` 变成了 `magnitude__7Point3dFv(ptr)`

  对于类的 nonstatic virtual 成员函数，`ptr->virtual_func()` 将被内化为 `(*ptr->vptr[1])(ptr)`。
  其中 1 表示 virtual_func 的 slot（类的每一个 nonstatic virtual 成员函数都配一个 slot）
* 想要支持多态，就必须有“执行期判断类型（runtime type resolution）”的能力，也就是说，当调用`ptr->z()`时，需要知道 ptr 的类型和`z()`的地址。
  一般实现上把 类型和地址信息放在 object 中，即给多态 object 添加 2 个成员：***表示类型的一个字符或数字*** 和 ***一个指向 virtual function 的 table***