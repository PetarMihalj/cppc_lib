#include <type_traits>

namespace rule_traits{
    
template<typename T>
using is_zero = typename std::conjunction<
    std::is_trivially_destructible<T>,
    std::is_trivially_constructible<T>,
    std::is_trivially_copy_constructible<T>,
    std::is_trivially_copy_assignable<T>,
    std::is_trivially_move_constructible<T>,
    std::is_trivially_move_assignable<T>
>;

template<typename T>
using is_three_copy = typename std::conjunction<
    std::negation<std::is_trivially_destructible<T>>,
    std::negation<std::is_trivially_constructible<T>>,
    std::negation<std::is_trivially_copy_constructible<T>>,
    std::negation<std::is_trivially_copy_assignable<T>>,

    std::is_destructible<T>,
    std::is_copy_constructible<T>,
    std::is_copy_assignable<T>,

    std::negation<std::is_move_constructible<T>>,
    std::negation<std::is_move_assignable<T>>
>;

template<typename T>
using is_three_move = typename std::conjunction<
    std::negation<std::is_trivially_destructible<T>>,
    std::negation<std::is_trivially_constructible<T>>,
    std::negation<std::is_trivially_move_constructible<T>>,
    std::negation<std::is_trivially_move_assignable<T>>,

    std::is_destructible<T>,
    std::is_move_constructible<T>,
    std::is_move_assignable<T>,

    std::negation<std::is_copy_constructible<T>>,
    std::negation<std::is_copy_assignable<T>>
>;

template<typename T>
using is_five = typename std::conjunction<
    std::negation<std::is_trivially_destructible<T>>,
    std::negation<std::is_trivially_constructible<T>>,
    std::negation<std::is_trivially_copy_constructible<T>>,
    std::negation<std::is_trivially_copy_assignable<T>>,
    std::negation<std::is_trivially_move_constructible<T>>,
    std::negation<std::is_trivially_move_assignable<T>>,

    std::is_destructible<T>,
    std::is_copy_constructible<T>,
    std::is_copy_assignable<T>,
    std::is_move_constructible<T>,
    std::is_move_assignable<T>
>;

template<typename T>
using is_no_copy_move = typename std::conjunction<
    std::negation<std::is_copy_constructible<T>>,
    std::negation<std::is_copy_assignable<T>>,
    std::negation<std::is_move_constructible<T>>,
    std::negation<std::is_move_assignable<T>>
>;

}

