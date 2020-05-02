#include <functional>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace vehlwn {

template<class...>
class Function;

template<class R, class... Args>
class Function<R(Args...)>
{
public:
    using result_type = R;

    Function() = default;

    template<class F>
    Function(F f)
    {
        static_assert(
            std::is_invocable_v<F, Args...>, "Parameter f is not invocable with Args...");
        m_f = makeFuncHolderPtr(std::move(f));
    }

    Function(const Function& rhs)
        : m_f{rhs.m_f->clone()}
    {
    }

    Function(Function&& rhs) noexcept
    {
        swap(rhs);
    }

    Function& operator=(const Function& rhs)
    {
        if(this == &rhs)
            return *this;
        Function(rhs).swap(*this);
        return *this;
    }

    Function& operator=(Function&& rhs) noexcept
    {
        swap(rhs);
        return *this;
    }

    ~Function() = default;

    void swap(Function& rhs) noexcept
    {
        using std::swap;
        swap(m_f, rhs.m_f);
    }

    R operator()(Args&&... args)
    {
        return (*m_f)(std::forward<Args>(args)...);
    }

    explicit operator bool() const noexcept
    {
        return m_f;
    }

private:
    struct BaseFuncHolder;
    using BaseFuncPtr_t = std::unique_ptr<BaseFuncHolder>;

    struct BaseFuncHolder
    {
        virtual ~BaseFuncHolder() = default;
        virtual R operator()(Args&&... agrs) = 0;
        virtual BaseFuncPtr_t clone() = 0;
    };

    template<class F>
    struct FuncHolder : BaseFuncHolder
    {
        F f;
        FuncHolder(F f)
            : f(std::move(f))
        {
        }
        virtual R operator()(Args&&... args) override
        {
            return std::invoke(f, std::forward<Args>(args)...);
        }
        virtual BaseFuncPtr_t clone() override
        {
            return std::make_unique<FuncHolder>(f);
        }
    };

    template<class F>
    static BaseFuncPtr_t makeFuncHolderPtr(F f)
    {
        return std::make_unique<FuncHolder<F>>(std::move(f));
    }

    BaseFuncPtr_t m_f;
};

template<class R, class... Args>
void swap(Function<R(Args...)>& lhs, Function<R(Args...)>& rhs) noexcept
{
    lhs.swap(rhs);
}

} // namespace vehlwn
