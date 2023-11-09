#include <iostream>

namespace stl {
    namespace members {
        class Point {
        public:
            virtual ~Point() {}
            int x, y, z;
        };

        void test() {
            printf("sizeof(int) = %d \n", sizeof(int));
            printf("sizeof(int*) = %d \n", sizeof(int*));
            printf("x.offset = %p\n", &Point::x);
            printf("y.offset = %p\n", &Point::y);
            printf("z.offset = %p\n", &Point::z);

            int Point::*p1 = 0;  // 注：Point::* 表示指向 Point 数据成员的指针类型；等于 0 表示没有指向任何成员
            int Point::*p2 = &Point::x; // 注：指向 Point 类的成员 x，返回 x 在对象中的 offset

            printf("p1 = %p \n", p1);
            printf("p2 = %p \n", p2);
        }
    }
}