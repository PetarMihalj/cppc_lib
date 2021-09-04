#include <type_traits>

namespace rule_traits {

namespace internals {

template<typename T>
using negation = typename std::conditional<T::value, std::false_type, std::true_type>::type;

template<typename ...T> struct bool_pack {};

template<typename ...T>
using conjunction = typename std::is_same<bool_pack<std::true_type, T...>, bool_pack<T..., std::true_type>>::type;

} // namespace internals



template <typename T>
using is_zero = internals::conjunction<typename std::is_trivially_destructible<T>::type,
                                       typename std::is_trivially_constructible<T>::type,
                                       typename std::is_trivially_copy_constructible<T>::type,
                                       typename std::is_trivially_copy_assignable<T>::type,
                                       typename std::is_trivially_move_constructible<T>::type,
                                       typename std::is_trivially_move_assignable<T>::type>;

template <typename T>
using is_three_copy = internals::conjunction<
    internals::negation<typename std::is_trivially_destructible<T>::type>,
    internals::negation<typename std::is_trivially_constructible<T>::type>,
    internals::negation<typename std::is_trivially_copy_constructible<T>::type>,
    internals::negation<typename std::is_trivially_copy_assignable<T>::type>,

    typename std::is_destructible<T>::type, typename std::is_copy_constructible<T>::type,
    typename std::is_copy_assignable<T>::type,

    internals::negation<typename std::is_move_constructible<T>::type>,
    internals::negation<typename std::is_move_assignable<T>::type>>;

template <typename T>
using is_three_move = internals::conjunction<
    internals::negation<typename std::is_trivially_destructible<T>::type>,
    internals::negation<typename std::is_trivially_constructible<T>::type>,
    internals::negation<typename std::is_trivially_move_constructible<T>::type>,
    internals::negation<typename std::is_trivially_move_assignable<T>::type>,

    typename std::is_destructible<T>::type, typename std::is_move_constructible<T>::type,
    typename std::is_move_assignable<T>::type,

    internals::negation<typename std::is_copy_constructible<T>::type>,
    internals::negation<typename std::is_copy_assignable<T>::type>>;

template <typename T>
using is_five = internals::conjunction<
    internals::negation<typename std::is_trivially_destructible<T>::type>,
    internals::negation<typename std::is_trivially_constructible<T>::type>,
    internals::negation<typename std::is_trivially_copy_constructible<T>::type>,
    internals::negation<typename std::is_trivially_copy_assignable<T>::type>,
    internals::negation<typename std::is_trivially_move_constructible<T>::type>,
    internals::negation<typename std::is_trivially_move_assignable<T>::type>,

    typename std::is_destructible<T>::type, typename std::is_copy_constructible<T>::type,
    typename std::is_copy_assignable<T>::type, typename std::is_move_constructible<T>::type,
    typename std::is_move_assignable<T>::type>;

template <typename T>
using is_no_copy_move =
    internals::conjunction<internals::negation<typename std::is_copy_constructible<T>::type>,
                           internals::negation<typename std::is_copy_assignable<T>::type>,
                           internals::negation<typename std::is_move_constructible<T>::type>,
                           internals::negation<typename std::is_move_assignable<T>::type>>;

} // namespace rule_traits
