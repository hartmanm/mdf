


// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0428r2.pdf

/*
auto f = [](auto&& ...args) {
return foo(std::forward<decltype(args)>(args)...);
};

*/
