## data
* 即使是空的类如 `class X {};` 其 size 也不为空，编译器会安插一个 char 在类的 object 中，这样类不同的 object 才能有唯一的地址。
* 类 size 的大小不一定是全部成员 size 之和，也可能会有 alignment 的长度（通常 32 位的机器上 alignment 为 4 bytes（32位），以使 bus 的运输量达到最大）