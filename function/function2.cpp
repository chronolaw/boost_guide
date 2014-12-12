// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/bind.hpp>
#include <boost/function.hpp>
using namespace boost;

//////////////////////////////////////////

class demo_class
{
private:
    typedef function<void(int)> func_t;
    func_t func;
    int n;
public:
    demo_class(int i):n(i){}

    template<typename CallBack>
    void accept(CallBack f)
    {   func = f;   }

    void run()
    {   func(n);    }
};

void call_back_func(int i)
{
    using namespace std;
    cout << "call_back_func:";
    cout << i * 2 << endl;
}

void case1()
{
    demo_class dc(10);
    dc.accept(call_back_func);
    dc.run();

}

//////////////////////////////////////////
class call_back_obj
{
private:
    int x;
public:
    call_back_obj(int i):x(i){}

    void operator()(int i)
    {
        using namespace std;
        cout << "call_back_obj:";
        cout << i * x++ << endl;
    }
};

void case2()
{
    demo_class dc(10);
    call_back_obj cbo(2);

    dc.accept(ref(cbo));

    dc.run();
    dc.run();
}

//////////////////////////////////////////

class call_back_factory
{
public:
    void call_back_func1(int i)
    {
        using namespace std;
        cout << "call_back_factory1:";
        cout << i * 2 << endl;
    }
    void call_back_func2(int i, int j)
    {
        using namespace std;
        cout << "call_back_factory2:";
        cout << i *j * 2 << endl;
    }
};

void case3()
{
    demo_class dc(10);
    call_back_factory cbf;

    dc.accept(bind(&call_back_factory::call_back_func1, cbf, _1));
    dc.run();

    dc.accept(bind(&call_back_factory::call_back_func2, cbf, _1, 5));
    dc.run();
}

//////////////////////////////////////////

bool case4()
{
    std::function<void(int)> func;

    func = call_back_func;

    //func.clear();
    //func.empty();

    return !!func;
}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
}


