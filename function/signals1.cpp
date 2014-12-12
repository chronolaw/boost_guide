// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/signals2.hpp>
using namespace boost::signals2;

//////////////////////////////////////////

void slots1()
{   cout << "slot1 called" << endl;}
void slots2()
{   cout << "slot2 called" << endl;}

//template<int N>
//struct slots
//{
//    void operator()()
//    {   cout << "slot"<< N <<" called" << endl; }
//};

template<int N>
struct slots
{
    int operator()(int x)
    {
        cout << "slot"<< N <<" called" << endl;
        return x *N;
    }

};

template<int N>
bool operator==(const slots<N>&, const slots<N>&)
{   return true;}

//////////////////////////////////////////

void case1()
{
    signal<void()> sig;

    sig.connect(&slots1);
    sig.connect(&slots2, at_front);

    sig();
}

//////////////////////////////////////////

void case2()
{
    //signal<void()> sig;
    signal<int(int)> sig;

    sig.connect(slots<1>(),at_back);
    sig.connect(slots<100>(), at_front);

    sig.connect(5,slots<51>(), at_back);
    sig.connect(5,slots<55>(), at_front);

    sig.connect(3,slots<30>(), at_front);
    sig.connect(3,slots<33>(), at_back);

    sig.connect(10,slots<10>());

    sig(2);
}

//////////////////////////////////////////

void case3()
{
    signal<int(int)> sig;

    sig.connect(slots<10>());
    sig.connect(slots<20>());
    sig.connect(slots<50>());

    cout << *sig(2) << endl;
}

//////////////////////////////////////////

template<typename T>
class combiner
{
    T v;
public:
    typedef std::pair<T, T> result_type;

    combiner(T t = T()):v(t){}

    template<typename InputIterator>
    result_type operator()(InputIterator begin, InputIterator end) const
    {
        if (begin == end)
        {   return result_type();       }

        vector<T> vec(begin, end);

        T sum = std::accumulate(vec.begin(), vec.end(), v);
        T max = *std::max_element(vec.begin(), vec.end());

        return result_type(sum, max);
    }
};

void case4()
{
    //signal<int(int), combiner<int> > sig;
    signal<int(int), combiner<int> > sig(combiner<int>(100));

    sig.connect(slots<10>());
    sig.connect(slots<20>());
    sig.connect(slots<30>(), at_front);

    auto x = sig(2);
    cout << x.first << "," << x.second;
}

//////////////////////////////////////////

void case5()
{
    signal<int(int) > sig;
    assert(sig.empty());

    sig.connect(0,slots<10>());
    sig.connect(0,slots<20>());
    sig.connect(1,slots<30>());
    assert(sig.num_slots() == 3);

    sig.disconnect(0);
    assert(sig.num_slots() == 1);

    sig.disconnect(slots<30>());
    assert(sig.empty());
}

//////////////////////////////////////////

void case6()
{
    signal<int(int) > sig;

    connection c1 = sig.connect(0,slots<10>());
    connection c2 = sig.connect(0,slots<20>());
    connection c3 = sig.connect(1,slots<30>());

    c1.disconnect();
    assert(sig.num_slots() == 2);
    assert(!c1.connected());
    assert(c2.connected());

    sig.disconnect_all_slots();

    sig.connect(0,slots<10>());
    assert(sig.num_slots() == 1);

    {
        scoped_connection sc = sig.connect(0,slots<20>());
        assert(sig.num_slots() == 2);
    }

    assert(sig.num_slots() == 1);
}

//////////////////////////////////////////
void case7()
{
    signal<int(int) > sig;

    connection c1 = sig.connect(0,slots<10>());
    connection c2 = sig.connect(0,slots<20>());
    assert(sig.num_slots() == 2);

    sig(2);

    cout << "begin blocking..." << endl;
    {
        shared_connection_block block(c1);
        assert(sig.num_slots() == 2);
        assert(c1.blocked());
        sig(2);
    }

    cout << "end   blocking..." << endl;
    assert(!c1.blocked());
    sig(2);
}

//////////////////////////////////////////
#include <boost/smart_ptr.hpp>

void case8()
{
    typedef signal<int(int) > signal_t;
    signal_t sig;

    sig.connect(slots<10>());
    //boost::shared_ptr<slots<20> > p(new slots<20>);
    auto p = boost::make_shared<slots<20>>();

    sig.connect(signal_t::slot_type(ref(*p)).track(p));
    p.reset();
    assert(sig.num_slots() == 1);
    sig(1);
}


//////////////////////////////////////////

void case9()
{
    typedef signal<int(int) > signal_t;
    typedef signal_t::slot_type slot_t;
    signal_t sig;

    auto p1 = boost::make_shared<slots<10>>();
    auto p2 = boost::make_shared<slots<20>>();

    function<int(int)> func = ref(*p1);

    sig.connect(slot_t(func).track(p1));

    sig.connect(slot_t(&slots<20>::operator(), p2.get(), _1).track(p2));

    p1.reset();
    p2.reset();
    assert( sig.num_slots() == 0);
    sig(1);
}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
    case7();
    case8();
    case9();
}

