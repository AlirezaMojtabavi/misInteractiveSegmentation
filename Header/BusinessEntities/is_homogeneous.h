#pragma once

namespace parcast
{

    // The is_homogeneous class template is a genelization of std::is_same. It can be used with parameter packs. It takes zero or 
    // more types and defines a static member variable `value` and a member type `type`.
    // const static member variable `value` is true if all the types are the same and false otherwise.
    // the `type` member type is equivalent to the first type or void if no type is given.
    // 
    // Example:
    // using homogeneity1 = is_homogeneous<std::string, std::string, std::string, std::string>;
    // homogeneity1::value is true, homogeneity1::type is std::string
    // 
    // using homogeneity2 = is_homogeneous<int, std::string, std::string, std::string>;
    // homogeneity2::value is false, homogeneity2::type is int
    // 
    // using homogeneity3 = is_homogeneous<int>;
    // homogeneity3::value is true, homogeneity3::type is int
    // 
    // using homogeneity4 = is_homogeneous<>;
    // homogeneity4::value is true, homogeneity4::type is void

    template<typename T = void, typename U = T, typename... V>
    struct is_homogeneous
    {
        static const bool value = is_homogeneous<T, U>::value && is_homogeneous<U, V...>::value;
        using type = T;
    };

    template<typename T, typename U>
    struct is_homogeneous<T, U>
    {
        static const bool value = false;
        using type = T;
    };

    template<typename T>
    struct is_homogeneous<T, T>
    {
        static const bool value = true;
        using type = T;
    };

}
