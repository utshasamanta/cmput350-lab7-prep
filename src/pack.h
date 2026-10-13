#ifndef PACK_H
#define PACK_H

#include <type_traits>

namespace pack_detail {

template <typename... Args>
constexpr int packSize = sizeof...(Args);

template <int QueryIndex, typename... Args>
struct _packIndexToType {
    static_assert(QueryIndex >= 0 && QueryIndex < packSize<Args...>, "Pack index is out of bounds");
};

template <typename First, typename... Rest>
struct _packIndexToType<0, First, Rest...> {
    using type = First;
};

template <int QueryIndex, typename First, typename... Rest>
struct _packIndexToType<QueryIndex, First, Rest...> {
    static_assert(QueryIndex > 0 && QueryIndex < 1 + sizeof...(Rest),
                  "Pack index is out of bounds");
    using type = typename _packIndexToType<QueryIndex - 1, Rest...>::type;
};

template <int QueryIndex, typename... Args>
using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;

template <int Accumulated, typename QueryType, typename... Args>
constexpr int _packTypeToIndex = -1;

template <int Accumulated, typename QueryType, typename First, typename... Rest>
constexpr int _packTypeToIndex<Accumulated, QueryType, First, Rest...> =
    std::is_same_v<QueryType, First> ? Accumulated
                                     : _packTypeToIndex<Accumulated + 1, QueryType, Rest...>;

template <typename QueryType, typename... Args>
constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;

}  // namespace pack_detail

template <typename... Args>
struct Pack {
    constexpr static int size = pack_detail::packSize<Args...>;

    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    template <typename QueryType>
    constexpr static int index = pack_detail::packTypeToIndex<QueryType, Args...>;
};

#endif  // PACK_H
