#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <utility>

template<std::ranges::input_range C, std::integral ...Args>
consteval auto mergeSizes(const C rg, Args... vals)
{
    std::vector<std::ranges::range_value_t<C>>
        v{std::ranges::begin(rg), std::ranges::end(rg)};

    (..., v.push_back(vals));
    std::ranges::sort(v);
    constexpr auto maxSz{std::ranges::size(rg) + sizeof...(vals)};
    std::array<std::ranges::range_value_t<C>, maxSz> ret{};
    auto res = std::ranges::unique_copy(v, ret.begin());

    return std::pair{ret, res.out - ret.begin()};
}

int main(int argc, char* argv[])
{
    constexpr std::array sizes{sizeof(int), sizeof(std::string), sizeof(long)};
    auto [allSzs, length] = mergeSizes(sizes, sizeof(float));
    auto allSzVw{std::views::counted(allSzs.begin(), length)};
    for(const auto sz : allSzVw)
    {
        std::cout << sz << ' ';
    }
    std::cout << '\n';
}
