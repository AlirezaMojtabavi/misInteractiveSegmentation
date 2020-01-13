#pragma once

#include "is_homogeneous.h"

namespace parcast
{

    // A generic parameter capturer that can be used in the `calls` clause of mock expectations in order to capture parameters
    // passed to a mock function and optionally forward the call to another function.
    // The template parameters specify the function signature: the first parameter is the return type and the subsequent ones are
    // parameter types. Its instances overload `operator()` with the same signature as that of the mock function. 
    // It captures the call parameters into a capturing structure (either a vector or tuple) and optionally forwards the call
    // to another function.
    // If the parameter types are homogeneous (all of the same type), the parameters are captured to a std::vector of that type. 
    // If the parameter types are heterogeneous, they are captured to a std::tuple consisting of fields that matches the parameter 
    // types.
    // There are two constructors both of which receive a reference to the capturing structure.
    // The second overload also receives a funtion which is called after the parameters are captured.
    // 
    // Examples:
    // std::vector<int> params1;
    // ParameterPackCapturer<void, int, int, int> cap1(params1);
    // cap1(123, 456, 789);
    // `cap1` is a function object of signature `void(int, int, int)` that captures the parameters into `params1`.
    //
    // std::tuple<int, bool, std::string> params2;
    // ParameterPackCapturer<int, int, bool, std::string> cap2(params2);
    // auto ret1 = cap2(123, false, "abc");
    // `cap2` is a function object of signature `int(int, bool, std::string)` that captures the parameters into `params2` and 
    // ret1 will contain default int (zero).
    //
    // int func3(int, bool, std::string)
    // {
    //     return 200;
    // }
    // std::tuple<int, bool, std::string> params3;
    // ParameterPackCapturer<void, int, bool, std::string> cap3(params3, &func3);
    // auto ret3 = cap2(123, false, "abc");
    // `cap2` is a function object of signature `int(int, bool, std::string)` that captures the parameters into `params2` and 
    // calls func3 afterwards. ret3 will contain the return value of func3 which is 200.
    template<typename RetT, typename... T>
    class ParameterPackCapturer
    {
    public:
        static const bool IsHomogeneous = is_homogeneous<T...>::value;
        using HomogeneousType = typename is_homogeneous<T...>::type;
        using ParameterPackType = std::conditional_t<IsHomogeneous, std::vector<HomogeneousType>, std::tuple<T...> >;
        using FunctionType = RetT(T...);

        ParameterPackCapturer(ParameterPackType& params)
            : m_Params(params),
            m_CallFuncAfter(false)
        {
        }

        explicit ParameterPackCapturer(ParameterPackType& params, FunctionType funcToCallAfter)
            : m_Params(params),
            m_CallFuncAfter(true),
            m_FuncToCallAfter(funcToCallAfter)
        {
        }

        RetT operator()(const T&... args)
        {
            m_Params = ParameterPackType{ args... };
            if (m_CallFuncAfter)
                return m_FuncToCallAfter(args...);
        }

    private:
        ParameterPackType& m_Params;
        std::function<FunctionType> m_FuncToCallAfter;
        bool m_CallFuncAfter = false;
    };

}
