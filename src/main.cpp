#include <type_traits>
#include <iostream>
#include <vector>
#include <format>
#include <algorithm>
#include <ranges>
#include <span>
#include <map>
#include <unordered_map>
#include <array>
#include <set>
#include <list>
#include "print.hpp"

using namespace wei_utils;

template <typename... Args>
auto func(Args... args)
{
    using T=std::common_type_t<Args...>;
    return std::array<T, sizeof...(Args)>{static_cast<T>(args)...};
}

struct A
{
    int x;
    double y;

    // 重载 << 操作符，以便可以打印 A 类的对象
    friend std::ostream& operator<<(std::ostream& os, const A& a) {
        os << "A(x=" << a.x << ", y=" << a.y << ")";
        return os;
    }

    /* data */
};


int main()
{
    int x = 42;
    double pi = 3.14159;
    std::string name = "Alice";

    // 使用可变参数模板函数
    wei_utils::print("a={},b={},c={}\n", x, pi, name); // 输出: 42 3.14159 Alice

    std::vector<int> vec = {1, 2, 3, 4, 5};
    print(vec); // 输出: 1 2 3 4 5

    std::array<int, 5> arr = {11, 21, 13, 14, 15};
    print(arr); // 输出: 1 2 3 4 5

    std::set<int> s = {12, 22, 32, 42, 52};
    print(s); // 输出: 1 2 3 4 5

    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    wei_utils::print(m); // 输出: 1=one 2=two 3=three

    // std::pair<int, std::string> p = {42, "answer"};
    // print(p); // 输出: 42 answer

    std::list<int> l = {1, 2, 3, 4, 5};
    print(l); // 输出: 1 2 3 4 5

    std::vector<A> v = {{1, 1.1}, {2, 2.2}, {3, 3.3}};
    print(v); // 输出: A(x=1, y=1.1) A(x=2, y=2.2) A(x=3, y=3.3)

    return 0;
}