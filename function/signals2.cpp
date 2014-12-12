// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/signals2.hpp>
using namespace boost::signals2;

//////////////////////////////////////////
#include <boost/random.hpp>
using namespace boost;

class ring
{
public:
    typedef signal<void()> signal_t;
    typedef signal_t::slot_type slot_t;

    connection connect(const slot_t& s)
    {   return alarm.connect(s);    }
    void press()
    {
        cout << "Ring alarm..." << endl;
        alarm();
    }
private:
    signal_t alarm;
};

typedef variate_generator<rand48, uniform_smallint<> > bool_rand;
bool_rand g_rand(rand48(time(0)), uniform_smallint<>(0,100));

extern char const  nurse1[] = "Mary";
extern char const  nurse2[] = "Kate";

template<char const *name>
class nurse
{
private:
    bool_rand &rand;
public:
    nurse():rand(g_rand){}

    void action()
    {
        cout << name;
        if (rand() > 30)
        {   cout << " wakeup and open door." << endl;}
        else
        {   cout << " is sleeping..." << endl;}
    }
};

extern char const  baby1[] = "Tom";
extern char const  baby2[] = "Jerry";

template<char const *name>
class baby
{
private:
    bool_rand &rand;
public:
    baby():rand(g_rand){}

    void action()
    {
        cout << "Baby " << name;
        if (rand() > 50)
        {   cout << " wakeup and crying loudly..." << endl; }
        else
        {   cout << " is sleeping sweetly..." << endl;  }
    }
};

class guest
{
public:
    void press(ring &r)
    {
        cout << "A guest press the ring." << endl;
        r.press();
    }
};

void case1()
{
    ring r;
    nurse<nurse1> n1;
    nurse<nurse2> n2;
    baby<baby1> b1;
    baby<baby2> b2;
    guest g;


    r.connect(bind(&nurse<nurse1>::action, n1));
    r.connect(bind(&nurse<nurse2>::action, n2));
    r.connect(bind(&baby<baby1>::action, b1));
    r.connect(bind(&baby<baby2>::action, b2));

    g.press(r);
}

//////////////////////////////////////////
class demo_class
{
public:
    typedef signal<void()> signal_t;
    boost::shared_ptr<signal_t> sig;

    int x;
    demo_class():sig(new signal_t), x(10){}
};

void print()
{   cout << "hello sig." << endl;}

void case2()
{
    demo_class obj;
    assert(obj.sig.use_count() == 1);
    demo_class obj2(obj);
    assert(obj.sig.use_count() == 2);

    obj.sig->connect(&print);
    (*obj2.sig)();
}

//////////////////////////////////////////

class combiner
{
public:
    typedef bool result_type;
    template<typename InputIterator> 
    result_type operator()(InputIterator begin, InputIterator end) const
    {
        while(begin != end)
        {
            if(*begin > 100)
                return true;
        }
        return false;
    }
};


template<int N>
struct slots
{
    int operator()(const connection &conn, int x)
    {
        cout << "conn="<< conn.connected()  << endl;
        return x *N;
    }

};

void case3()
{
    typedef signal<int(int) > signal_t;
    typedef signal_t::extended_slot_type slot_t;
    signal_t sig;


    sig.connect_extended(slot_t(&slots<10>::operator(), slots<10>(), _1, _2));
    sig.connect_extended(slot_t(&slots<20>::operator(), slots<20>(), _1, _2));
    sig(5);
}

//////////////////////////////////////////
void f()
{   cout << "func called" << endl;}

void case4()
{
    boost::function<void()> func;
    func = f;
    func();
    signal<void()> sig;
    sig.connect(&f);
    sig();
}

//////////////////////////////////////////

template<typename Signature>
class sig_ex
{
public:
    typedef signal<Signature> signal_type;
    typedef typename signal_type::slot_type slot_type;

    connection connect(const slot_type& s)
    {   return sig.connect(s);  }

    connection operator+=(const slot_type& s)
    {   return connect(s);  }

    template<typename ... Args>
    typename signal_type::result_type
    operator()(Args&& ... args)
    {   return sig(std::forward<Args>(args)...); }

private:
    signal_type sig;
};

template<int N>
struct slots_ex
{
    int operator()(int x)
    {
        cout << "slot"<< N <<" called" << endl;
        return x *N;
    }

};

void case5()
{
    sig_ex<int(int)> sig;

    sig += slots_ex<10>();
    sig += slots_ex<5>();

    sig(2);
}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
}


