## data
* 即使是空的类如 `class X {};` 其 size 也不为空，编译器会安插一个 char 在类的 object 中，这样类不同的 object 才能有唯一的地址。
* 类 size 的大小不一定是全部成员 size 之和，也可能会有 alignment 的长度（通常 32 位的机器上 alignment 为 4 bytes（32位），以使 bus 的运输量达到最大）
* 任意一个类的 non-static data member 的存取都必须经过该类的 object，否则无法存取它们。如：
  ```
  void Point3D::translate(const Point3D& pt) {
      x += pt.x;
      y += pt.y;
      z += pt.z;
  }
  ```
  上面代码中，x, y, z 的获取都是经过 this 指针获取的，实际扩展代码为：
  ```
  void Point3D::translate(Point3D *const this, const Point3D& pt) {
      this->x += pt.x;
      this->y += pt.y;
      this->z += pt.z;
  }
  ```
  实际上编译器对每一个成员函数都传了 this 指针，因为获取 non-static data member 的原理是 this 的地址 + 成员的 offset，
  因此 取一个 non-static data member 的效率和取一个 c struct 的 data member 的效率是一样的
* `origin.x = 0` 和 `pt->x = 0` 在效率上有什么区别？

  效率高不高取决于 x 的地址获取快不快，而 x 的地址 = object 的起始地址 + x 的 offset。

  因此，在`origin.x` 中，origin 的类型明确，object 地址也明确，x.offset 在编译期就确定了，其存取效率是固定的。

  对于 `pt->x` 而言，需要先通过`->`找到 object，再通过 offset 计算 x 的地址。但是如果 pt->x 是从 virtual base class 继承过来的成员，
  这个时候 pt 的类型在编译期不能确定，需要延迟到运行期才能确定，这种情况下获取 x 的地址效率更低。
* 如果 Class 内含一个或多个 virtual base class subobjects，那么 Class 对象将被分为两部分：***不变区域*** 和 ***共享区域***
* 通过`&Point::x`可以获得 x 在对象中的 offset，其取出来的值***可能***会被 +1，使用的时候再 -1。***注：我本地测试没有复现***