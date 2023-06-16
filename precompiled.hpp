#include <functional>
#include <typeinfo>

namespace boost_fake
{

struct stl_type_index1
{
    const std::type_info *data_;

    stl_type_index1(const std::type_info &data) : data_(&data)
    {
    }
};

inline bool operator==(const std::type_info &lhs, const stl_type_index1 &rhs)
{
    stl_type_index1{lhs};
    return true;
}

template <class T> inline stl_type_index1 type_id1()
{
    return typeid(T);
}

struct value_semantic1
{
    virtual void notify() = 0;
};

template <class T> struct typed_value1 : public value_semantic1
{
    void notify();
};

template <class T> void typed_value1<T>::notify()
{
    *stl_type_index1{typeid(void)}.data_ == type_id1<T>();
}

} // namespace boost_fake