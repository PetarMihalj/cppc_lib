#include <type_traits>

namespace rule_traits {

namespace internals {
template <typename T> struct negation { static const bool value = true; };

template <> struct negation<std::true_type> {
    static const bool value = false;
};

template <typename T> struct type_to_value { static const bool value = true; };

template <> struct type_to_value<std::false_type> {
    static const bool value = false;
};

template <typename... T> struct conjunction { static const bool value = true; };

template <typename T1, typename... T> struct conjunction<T1, T...> {
    static const bool value = type_to_value<
        std::conditional<T1::value, conjunction<T...>, std::false_type>>::value;
};
} // namespace internals

template <typename T>
using is_zero = internals::conjunction<std::is_trivially_destructible<T>,
                                       std::is_trivially_constructible<T>,
                                       std::is_trivially_copy_constructible<T>,
                                       std::is_trivially_copy_assignable<T>,
                                       std::is_trivially_move_constructible<T>,
                                       std::is_trivially_move_assignable<T>>;

template <typename T>
using is_three_copy = internals::conjunction<
    internals::negation<std::is_trivially_destructible<T>>,
    internals::negation<std::is_trivially_constructible<T>>,
    internals::negation<std::is_trivially_copy_constructible<T>>,
    internals::negation<std::is_trivially_copy_assignable<T>>,

    std::is_destructible<T>, std::is_copy_constructible<T>,
    std::is_copy_assignable<T>,

    internals::negation<std::is_move_constructible<T>>,
    internals::negation<std::is_move_assignable<T>>>;

template <typename T>
using is_three_move = internals::conjunction<
    internals::negation<std::is_trivially_destructible<T>>,
    internals::negation<std::is_trivially_constructible<T>>,
    internals::negation<std::is_trivially_move_constructible<T>>,
    internals::negation<std::is_trivially_move_assignable<T>>,

    std::is_destructible<T>, std::is_move_constructible<T>,
    std::is_move_assignable<T>,

    internals::negation<std::is_copy_constructible<T>>,
    internals::negation<std::is_copy_assignable<T>>>;

template <typename T>
using is_five = internals::conjunction<
    internals::negation<std::is_trivially_destructible<T>>,
    internals::negation<std::is_trivially_constructible<T>>,
    internals::negation<std::is_trivially_copy_constructible<T>>,
    internals::negation<std::is_trivially_copy_assignable<T>>,
    internals::negation<std::is_trivially_move_constructible<T>>,
    internals::negation<std::is_trivially_move_assignable<T>>,

    std::is_destructible<T>, std::is_copy_constructible<T>,
    std::is_copy_assignable<T>, std::is_move_constructible<T>,
    std::is_move_assignable<T>>;

template <typename T>
using is_no_copy_move =
    internals::conjunction<internals::negation<std::is_copy_constructible<T>>,
                           internals::negation<std::is_copy_assignable<T>>,
                           internals::negation<std::is_move_constructible<T>>,
                           internals::negation<std::is_move_assignable<T>>>;

} // namespace rule_traits
