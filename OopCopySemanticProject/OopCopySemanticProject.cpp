#include <iostream>

template <typename T>
class SmartPointer
{
    T* pointer;
public:
    SmartPointer(T* pointer) : pointer{ pointer } {}
    SmartPointer(const SmartPointer& obj)
    {
        pointer = new T;
        *pointer = *obj.pointer;
    }

    SmartPointer(SmartPointer&& obj) noexcept
        : pointer{ obj.pointer } 
    {
        obj.pointer = nullptr;
    }


    SmartPointer& operator=(const SmartPointer& obj)
    {
        if (&obj == this)
            return *this;
        
        delete pointer;

        pointer = new T;
        *pointer = *obj.pointer;

        return *this;
    }

    SmartPointer& operator=(SmartPointer&& obj) noexcept
    {
        if (&obj == this)
            return *this;

        delete pointer;

        pointer = obj.pointer;
        obj.pointer = nullptr;

        return *this;
    }

    ~SmartPointer()
    {
        delete pointer;
    }

    T& operator*() const { return *pointer; }
    T* operator->() const { return pointer; }
};

class MyClass
{
    int* pointer;
    int value;
public:
    MyClass() : value{ 10 }, pointer{ new int[value] } 
    {
        std::cout << this << "Object Construct\n";
    }

    MyClass(const MyClass& obj) : value{ obj.value }
    {
        std::cout << this << "Object Copy Construct\n";
        pointer = new int[value];
        for (int i = 0; i < value; i++)
            pointer[i] = obj.pointer[i];
    }

    ~MyClass()
    {
        delete[] pointer;
        std::cout << this << "Object Destruct\n";
    }

    void Print() { std::cout << "Value = " << value << "\n"; }

    MyClass ReturnThis()
    {
        return *this;
    }

};


void Func(const int& a)
{
    std::cout << "l-value " << a << "\n";
}
void Func(const int&& a)
{
    std::cout << "r-value " << a << "\n";
}


int main()
{
    MyClass* obj = new MyClass();
    /*
    SmartPointer<MyClass> obj(new MyClass());
    obj->Print();

    SmartPointer<MyClass> obj2(obj);

    std::cout << "other code\n";
    */
    int a = 10;
    Func(a);
    Func(20);

    int&& b = 30;
    Func(b);

    MyClass&& obj3 = obj->ReturnThis();
}
