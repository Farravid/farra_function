//TODO: Add gtests and benchmarks to try to make it faster and smaller than std::function

#include <concepts>
#include <functional>
#include <iostream>
#include <memory>

namespace farra
{
    template<typename T>
    struct const_function;

    template<typename Return_t, typename... Params_t>
    struct const_function<Return_t(Params_t...)>
    {
        public:

            template<typename FunctionObject_t>
            const_function(FunctionObject_t fn)
                : function_(std::make_unique<callable_impl<FunctionObject_t>>(fn))
            {}

            constexpr inline Return_t operator()(Params_t... params) { return function_->call(params...); } 
        
        private:
            struct callable_base
            {
                //void call() { static_cast<CRTP_t&>(&this).call(); }
                virtual Return_t call(Params_t...) { return Return_t{}; };
                virtual ~callable_base() = default;
            };

            template<typename Callable>
            struct callable_impl : callable_base
            {
                callable_impl(Callable c)
                    : callable(std::move(c))
                {}

                Callable callable{};

                virtual Return_t call(Params_t... params) { return callable(params...); }
            };

            std::unique_ptr<callable_base> function_ {};
    };
}

struct S
{
    int x { 2 };
    int y { 10 };

    int getValue()
    {
        return x + y;
    }
};

int main()
{
    S s{};
    farra::const_function<int()> f2 = std::bind(&S::getValue, &s);

    //std::cout << f2() << "\n";
    return 0;
}
