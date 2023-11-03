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

  效率高不高取决于 x 的地址获取快不快，而 x 的地址 = object 的起始地址 + x 的 offset。`origin.x` 中，origin 的类型明确，x.offset 在编译期就确定了。
  对于 `pt->x`，如果 pt 的类型可以明确，那么 `pt->x`的存取效率和 `origin.x`是一样的，但是如果 pt->x 是从 virtual base class 继承过来的成员，
  这个时候 pt 的类型在编译期不能确定，需要延迟到运行期才能确定，这种情况下获取 x 的地址效率更低。
