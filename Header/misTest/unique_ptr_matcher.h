#pragma once

namespace parcast
{

    // Use unique_ptr_matcher in mock expectations to match arguments of type std::unique_ptr with the owned raw pointer.
    template <typename T>
    class unique_ptr_matcher
    {
    public:
        unique_ptr_matcher(T* expectedPtr)
            : m_ExpectedPtr(expectedPtr)
        {
        }

        bool operator()(const std::unique_ptr<T>& receivedPtr)
        {
            return m_ExpectedPtr == receivedPtr.get();
        }

    private:
        T* m_ExpectedPtr;
    };

}