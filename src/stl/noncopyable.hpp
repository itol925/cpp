#include <iostream>

namespace stl::classes {
    class NonCopyable {
    public:
        NonCopyable() = default;

        // non copy
        NonCopyable(const NonCopyable&) noexcept = delete;
        NonCopyable& operator=(const NonCopyable&) noexcept = delete;

        // non move
        NonCopyable(NonCopyable&&) = delete;
        NonCopyable& operator=(NonCopyable&&) = delete;
    };

    class Ext : public NonCopyable {

    };

    void test_non_copy() {
        Ext e1;
        // Ext e2(e1); error. non copy!!
    }
}