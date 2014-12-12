// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/lightweight_test.hpp>
#include <boost/utility.hpp>
#include <boost/dynamic_bitset.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    dynamic_bitset<> db1;
    dynamic_bitset<> db2(10);
    dynamic_bitset<> db3(0x16,
    BOOST_BINARY(10101));       //注意这里
    dynamic_bitset<> db4(string("0100"));
    dynamic_bitset<> db5(db3);

    dynamic_bitset<> db6;
    db6 = db4;

    cout << hex << db5.to_ulong() << endl;
    cout << db4[0] << db4[1] << db4[2] << endl;

}

//////////////////////////////////////////
void case2()
{
    dynamic_bitset<> db;

    db.resize(10, true);
    cout << db << endl;

    db.resize(5);
    cout << db << endl;

    {
        dynamic_bitset<> db(5,BOOST_BINARY(01110));

        cout << db << endl;
        assert(db.size() == 5);

        db.clear();
        assert(db.empty()&& db.size()==0);

    }

    assert(dynamic_bitset<>(64).num_blocks()==1);
    assert(dynamic_bitset<>(65).num_blocks()==2);

    {
        dynamic_bitset<> db(5,BOOST_BINARY(01001));
        db.push_back(true);
        assert(db.to_ulong() == BOOST_BINARY_UL(101001));

    }

    {
        dynamic_bitset<> db(5,BOOST_BINARY(01001));
        db.append(BOOST_BINARY(101));
        assert(db.size() == sizeof(unsigned long)*8 + 5);
        cout << db << endl;             //0000000000000000000000000000010101001

    }
}

//////////////////////////////////////////
void case3()
{
    dynamic_bitset<> db1(4, BOOST_BINARY(1010));

    db1[0] &= 1;
    db1[1] ^= 1;
    cout << db1 << endl;

    dynamic_bitset<> db2(4, BOOST_BINARY(0101));
    assert(db1 > db2);

    cout << (db1 ^ db2) << endl;
    cout << (db1 | db2) << endl;

}

//////////////////////////////////////////
void case4()
{
    dynamic_bitset<> db(4, BOOST_BINARY(0101));

    assert(db.test(0) && !db.test(1));
    assert(db.any() && !db.none());
    assert(db.count() == 2);

    {
        dynamic_bitset<> db(4, BOOST_BINARY(0101));

        db.flip();
        assert(db.to_ulong() == BOOST_BINARY(1010));

        db.set();
        assert(!db.none());

        db.reset();
        assert(!db.any() );

        db.set(1, 1);
        assert(db.count() == 1);

    }

    {
        dynamic_bitset<> db(5, BOOST_BINARY(00101));

        auto pos = db.find_first();
        assert(pos == 0);

        pos = db.find_next(pos);
        assert(pos == 2);

    }
}

//////////////////////////////////////////
void case5()
{
    dynamic_bitset<> db(10, BOOST_BINARY(1010101));
    cout << db.to_ulong() << endl;      //85

    db.append(10);
    cout << db.to_ulong() << endl;

    db.push_back(1);
    //cout << db.to_ulong() << endl;
    BOOST_TEST_THROWS(db.to_ulong(), std::overflow_error);

    string str;
    to_string(db, str);
    cout << str << endl;

}

//////////////////////////////////////////
void case6()
{
    dynamic_bitset<> db1(5, BOOST_BINARY(10101));
    dynamic_bitset<> db2(5, BOOST_BINARY(10010));

    cout << (db1 | db2) << endl;
    cout << (db1 & db2) << endl;
    cout << (db1 - db2) << endl;

    dynamic_bitset<> db3(5, BOOST_BINARY(101));
    assert(db3.is_proper_subset_of(db1));

    dynamic_bitset<> db4(db2);
    assert(db4.is_subset_of(db2));
    assert(!db4.is_proper_subset_of(db2));
}

//////////////////////////////////////////
void func(int n)
{
    //cout << "test " << n << endl;

    dynamic_bitset<> db(n);
    db.set();
    //cout << db.size() << endl;

    for (dynamic_bitset<>::size_type i = db.find_next(1);
            i != dynamic_bitset<>::npos ;
            i = db.find_next(i ) )
    {
        for (dynamic_bitset<>::size_type j = db.find_next(i);
                j != dynamic_bitset<>::npos ;
                j = db.find_next(j ))
        {
            if ( j % i == 0)
            {
                db[j] = 0;
            }
        }
    }

    for (dynamic_bitset<>::size_type i = db.find_next(2);
            i != dynamic_bitset<>::npos ;
            i = db.find_next(i) )
    {
        cout << i << ", ";
    }

}

void case7()
{
    func(10);
    func(50);
}

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
