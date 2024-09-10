#pragma once

#include <print>
#include <format>
// #include <string>
#include <iostream>
#include <sstream>
namespace wei_utils
{
    // 打印多参数
    template <typename... Args>
    void print(std::format_string<Args...> fmt, Args &&...args)
    {
        std::print(stdout, fmt, std::forward<Args>(args)...);
    }

    // 打印map和unorder_map容器
    template <typename T>
    concept is_map_type = requires(T t) {
        typename T::key_type;
        typename T::mapped_type;
        { t.begin() } -> std::input_iterator;
    };

    template <is_map_type T>
    void print(const T &container)
    {
        std::ostringstream os;
        os << "{";
        for (const auto &[key, value] : container)
        {
            os << key << ": " << value << ", ";
        }
        if (!container.empty())
        {
            os.seekp(-2, std::ios_base::end); // 移除最后一个逗号和空格
        }
        os << "}\n";
        std::cout << os.str();
    }

    // 定义一个概念，用于限定可以迭代的容器类型
    // 定义一个概念，用于限定可以迭代的容器类型
    template <typename Rng>
    concept iterable_range = std::ranges::range<Rng> && !is_map_type<Rng>;

    // 打印任意可迭代容器
    template <iterable_range Rng>
    void print(const Rng &container)
    {
        std::ostringstream os;
        os << "[";
        std::ranges::copy(container, std::ostream_iterator<typename Rng::value_type>(os, ", "));
        if (!container.empty())
        {
            os.seekp(-2, std::ios_base::end); // 移除最后一个逗号和空格
        }
        os << "]\n";
        std::cout << os.str();
    }

}
