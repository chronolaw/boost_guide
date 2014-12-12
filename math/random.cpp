// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/random.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    mt19937 rng(time(0));

    std::cout << mt19937::min() << "<->"
        << mt19937::max() << std::endl;

    for (int i = 0;i < 100;++i)
    {
        std::cout << rng() << ",";
    }

    rng.discard(5);
    std::vector<int> vec(10);
    rng.generate(vec.begin(), vec.end());

}

//////////////////////////////////////////

void case2()
{
    mt19937 rng(time(0));
    std::cout <<  rng() << std::endl;

    mt19937 rng2(rng);

    for (int i = 0;i < 10;++i)
    {   assert(rng() == rng2());    }
}

//////////////////////////////////////////

void case3()
{
    //using namespace boost::random;
    mt19937 rng(time(0));

    random::uniform_int_distribution<> ui(0, 255);
    for (int i = 0;i < 10;++i)
    {   std::cout << ui(rng) << ","; }
    std::cout << std::endl;

    uniform_01<> u01;
    for (int i = 0;i < 10;++i)
    {   std::cout << u01(rng) << ",";    }
    std::cout << std::endl;

    normal_distribution<> nd(1, 2);
    int count = 0;
    for (int i = 0;i < 10000;++i)
    {
        if (abs(nd(rng) - 1) <= 2.0)
        {   ++count;    }
    }
    std::cout << 1.0 * count / 10000 << std::endl;
}

//////////////////////////////////////////

void case4()
{
    mt19937 rng((int32_t)time(0));
    uniform_smallint<>  us(1,100);

    variate_generator<mt19937&, uniform_smallint<>> gen(rng, us);
    for (int i = 0; i < 10 ; ++i)
    {       std::cout << gen() << std::endl;  }

}

template<typename Rng >
void rand_bytes(unsigned char *buf, int buf_len)
{
    typedef variate_generator<Rng, uniform_smallint<>> var_gen_t;
    static var_gen_t
        gen(Rng((typename Rng::result_type)time(0)),
                uniform_smallint<>(1,255));

    generate_n(buf, buf_len, std::ref(gen));
    //for (int i = 0; i < buf_len; ++i)
    //{   buf[i] = gen();}
}

void case5()
{
    unsigned char buf[10];

    rand_bytes<mt19937>(buf, 10);
    for (int i = 0;i < 10 ;++i)
    {       std::cout << (short)buf[i] << ",";   }
    std::cout << std::endl;

    rand_bytes<rand48>(buf, 10);
    for (int i = 0;i < 10 ;++i)
    {       std::cout << (short)buf[i] << ",";   }

    std::cout << std::endl;
}

//////////////////////////////////////////

#include <boost/nondet_random.hpp>

class boost::random_device::impl
{
    private:
        rand48 rng;
    public:
        impl():rng(time(0))
    {   std::cout << "random_device::impl ctor\n";   }

    ~impl() 
    {   std::cout << "random_device::impl dtor\n";   }

    unsigned int operator()()
    {   return rng();   }
};

boost::random_device::random_device()
: pimpl(new impl)
{}

boost::random_device::~random_device()
{   delete pimpl;}

double boost::random_device::entropy() const
{   return 10;}

unsigned int boost::random_device::operator()()
{   return (*pimpl)();}

void case6()
{
    random_device rng;
    for (int i = 0 ;i < 10 ; ++i)
    {   std::cout << rng() << ",";   }
    std::cout << std::endl;

    uniform_real<> ur(1.0, 2.0);
    for (int i = 0 ;i < 10 ; ++i)
    {   std::cout << ur(rng) << ","; }
    std::cout << std::endl;

    variate_generator<random_device&, uniform_smallint<>> 
        gen(rng, uniform_smallint<>(0,255));
    for (int i = 0 ;i < 10 ; ++i)
    {   std::cout << gen() << ",";   }
    std::cout << std::endl;
}


int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
}

