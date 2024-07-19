//TODO: Add gtests and benchmarks to try to make it faster and smaller than std::function

#include <functional>
#include <iostream>

namespace farra
{
    template<typename Return_t, typename... Params_t>
    struct const_function{};

    template<typename Return_t, typename... Params_t>
    struct const_function<Return_t(Params_t...)>
    {
        using fn_pointer_t = Return_t(*)(Params_t...);

        static constexpr fn_pointer_t func_{};

        constexpr const_function(fn_pointer_t&& fn)
            : func_(std::forward<fn_pointer_t>(fn))
        {}

        constexpr Return_t operator()()
        {
            func_();
        }
    };
}

inline void foo()
{
    std::cout << "Hey wassap \n";
}

int main()
{
    farra::const_function<void()> f = foo;

    f();

    std::cout << sizeof(f);
    //farra::const_function<void()> myFunction{};
}
