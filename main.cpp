#include <iostream>

class Example
{
public:
    Example() = default;

    explicit Example(std::size_t size): m_size(size)
    {
        m_data = new int[m_size]();
    }

    ~Example()
    {
        delete[] m_data;
    }

    Example(const Example &other): m_size(other.m_size)
    {
        std::cout << "Copy constructor\n";
        m_data = new int[m_size]();
        std::copy(other.m_data, other.m_data + m_size, m_data);
    }

    Example &operator=(const Example &other)
    {
        std::cout << "Assign operator, using also copy constructor\n";
        Example copy(other);
        swap(*this, copy);
        return *this;
    }

    Example(Example &&other) noexcept
    {
        std::cout << "Move constructor\n";
        swap(*this, other);
    }

    Example &operator=(Example &&other) noexcept
    {
        std::cout << "Assign move operator\n";
        swap(*this, other);
        return *this;
    }

    friend void swap(Example &lhs, Example &rhs) noexcept
    {
        std::swap(lhs.m_size, rhs.m_size);
        std::swap(lhs.m_data, rhs.m_data);
    }

private:
    int *m_data = nullptr;
    std::size_t m_size = 0;
};

int main()
{
    const std::size_t size = 100;
    
    Example example(size);

    Example exampleCopy(example);

    Example exampleAssign;
    exampleAssign = example;

    Example exampleMove(std::move(exampleCopy));

    Example exampleAssignMove;
    exampleAssignMove = std::move(exampleAssign);

    return 0;
}
