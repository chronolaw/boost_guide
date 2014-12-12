// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
using namespace boost::uuids;

//////////////////////////////////////////
void case1()
{
    uuid u ;
    assert(uuid::static_size() == 16);
    assert(u.size() == 16);

    vector<unsigned char> v(16, 7);
    std::copy(v.begin(), v.end(), u.begin());
    assert(u.data[0] == u.data[1]
            && u.data[15] == 7);

    cout << u << endl;
    std::fill_n(u.data+ 10,6, 8);

    cout << u << endl;
}

//////////////////////////////////////////
void case2()
{
    uuid u ;

    std::fill_n(u.begin(), u.size(), 0xab);
    assert(!u.is_nil());
    assert(u.variant() == u.variant_rfc_4122);
    assert(u.version() == u.version_unknown);
    cout << u << endl;

    std::memset(u.data, 0, 16);
    assert(u.is_nil());
    uuid u1 ,u2;

    std::fill_n(u1.begin(), u1.size(), 0xab);
    std::fill_n(u2.begin(), u2.size(), 0x10);
    assert(u1 != u2 && u1 > u2);

    u2.data[0] = 0xff;
    assert( u1 < u2);

    std::memset(u1.data, 0, 16);
    std::memset(u2.data, 0, 16);
    assert(u1 == u2);

}

//////////////////////////////////////////
void case3()
{
    uuid u = nil_generator()();
    assert(u.is_nil());

    u = nil_uuid();
    assert(u.is_nil());

    string_generator sgen;

    uuid u1 = sgen("0123456789abcdef0123456789abcdef");
    cout << u1 << endl;
    uuid u2 = sgen("01234567-89ab-cdef-0123-456789abcdef");
    cout << u2 << endl;
    uuid u3 = sgen(L"{01234567-89ab-cdef-0123-456789abcdef}");
    cout << u3 << endl;
}

//////////////////////////////////////////
void case4()
{
    uuid www_xxx_com= string_generator()
        ("{0123456789abcdef0123456789abcdef}");
    name_generator ngen(www_xxx_com);

    uuid u1 = ngen("mario");
    assert(!u1.is_nil() &&
            u1.version() == uuid::version_name_based_sha1);

    uuid u2 = ngen("link");
    cout << u2 << endl;

    random_generator rgen;

    uuid u = rgen();
    assert(u.version()== uuid::version_random_number_based);
    cout << u << endl;

}

//////////////////////////////////////////
class uuid_t : public uuid
{
private:
    static random_generator& rand_uuid()
    {
        static random_generator gen;
        return gen;
    }
    static string_generator& string_uuid()
    {
        static string_generator gen;
        return gen;
    }

public:
    uuid_t(): uuid(rand_uuid()()){}
    uuid_t(int): uuid(nil_uuid()){}
    uuid_t(const char* str): uuid(string_uuid()(str)) {}
    uuid_t(const uuid& u, const char* str):
        uuid(name_generator(u)(str))    {}
    explicit uuid_t(const uuid& u): uuid(u){}

    operator uuid()
    {   return static_cast<uuid&>(*this);   }
    operator uuid() const
    {   return static_cast< const uuid&>(*this);}
};

void case5()
{
    uuid_t u0 = 0;
    assert(u0.is_nil());

    uuid_t u1,u2;
    cout << u1 << endl;
    cout << u2 << endl;

    uuid_t u3("{01234567-89ab-cdef-0123-456789abcdef}");
    cout << u3 << endl;

    cout << uuid_t(u3, "test name gen") << endl;

}

//////////////////////////////////////////
#include <boost/lexical_cast.hpp>
using namespace boost;

void case6()
{
    uuid u = string_generator()
        ("01234567-89ab-cdef-0123-456789abcdef");

    string str = to_string(u);
    cout << str << endl;

    {
        uuid u = lexical_cast<uuid>
            ("01234567-89ab-cdef-0123-456789abcdef");
        cout << u << endl;
        string str = lexical_cast<string>(u);
        cout << str << endl;

    }
}

//////////////////////////////////////////
#include <boost/uuid/sha1.hpp>
using namespace boost::uuids::detail;

void case7()
{
    sha1 sha;

    const char *szMsg = "a short message";
    sha.process_byte(0x10);
    sha.process_bytes(szMsg, strlen(szMsg));
    sha.process_block(szMsg, szMsg + strlen(szMsg));

    unsigned int digest[5];
    sha.get_digest(digest);
    for (int i = 0; i < 5 ; ++i)
    {
        cout << hex << digest[i];
    }
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
}
