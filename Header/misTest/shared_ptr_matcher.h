#pragma once

namespace parcast
{

    // Use shared_ptr_matcher in mock expectations to match arguments of type std::shared_ptr with the owned raw pointer.
    template <typename T>
    class shared_ptr_matcher
    {
    public:
        shared_ptr_matcher(T* expectedPtr)
            : m_ExpectedPtr(expectedPtr)
        {
        }

        bool operator()(const std::shared_ptr<T>& receivedPtr)
        {
            return m_ExpectedPtr == receivedPtr.get();
        }

    private:
        T* m_ExpectedPtr;
    };

}
