#include <type_traits>

#include "pack.h"

int main() {
    static_assert(pack_detail::packSize<int, double, char> == 3);
    static_assert(std::is_same_v<pack_detail::packIndexToType<1, int, double, char>, double>);
    static_assert(pack_detail::packTypeToIndex<char, int, double, char> == 2);
    static_assert(pack_detail::packTypeToIndex<float, int, double, char> == -1);

    using TestPack = Pack<int, double, char, int>;

    static_assert(TestPack::size == 4);
    static_assert(std::is_same_v<TestPack::type<0>, int>);
    static_assert(std::is_same_v<TestPack::type<1>, double>);
    static_assert(std::is_same_v<TestPack::type<2>, char>);
    static_assert(TestPack::index<int> == 0);
    static_assert(TestPack::index<char> == 2);
    static_assert(TestPack::index<float> == -1);

    return 0;
}
