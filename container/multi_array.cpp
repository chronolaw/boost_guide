// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/multi_array.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    multi_array<int, 3> ma(extents[2][3][4]);

    auto shape = ma.shape();
    for (size_t i = 0; i < ma.num_dimensions(); ++i)
    {
        cout << shape[i] << ",";
    }
    cout << endl << ma.num_elements() << endl;

    for (int i = 0,  v = 0; i < 2; ++i)
        for (int j = 0; j < 3;++j)
            for (int k = 0;k < 4;++k)
            {
                ma[i][j][k] = v++;
            }

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3;++j)
        {
            for (int k = 0;k < 4;++k)
            {
                cout << ma[i][j][k] << ",";
            }
            cout << endl;
        }
        cout << endl;
    }

    //cout << ma[2][3][4];

    std::array<size_t, 3> idx = {0,1,2};
    ma(idx) = 10;
    cout << ma(idx) << endl;
}

//////////////////////////////////////////
void case2()
{
    multi_array<int, 3> ma(extents[2][3][4]);
    assert(ma.shape()[0] == 2);

    std::array<std::size_t, 3> arr = {4,3,2};
    ma.reshape(arr);
    assert(ma.shape()[0] == 4);

    ma.resize(extents[2][9][9]);
    assert(ma.num_elements() == 2*9*9);
    assert(ma.shape()[1] == 9);
}

//////////////////////////////////////////
void case3()
{
    typedef multi_array<int, 2> ma_type;
    multi_array<int, 2> ma(extents[3][4]) ;

    typedef ma_type::index_range range;
    //indices[range(0,2)][range(0,2)];

    auto view = ma[indices[range(0,2)][range(0,2)] ];

    cout << view.num_elements() << endl;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2;++j)
        {
            cout << view[i][j] << ",";
        }
        cout << endl;
    }
    cout << *view.shape() << endl;

}

//////////////////////////////////////////
void case4()
{
    int arr[12];
    for (int i = 0;i < 12;++i)
    {   arr[i] = i; }

    multi_array_ref<int, 2> mar(arr, extents[3][4]);

    for (size_t i = 0; i < 3; ++i)
    {
        cout << "(";
        for(size_t j = 0;j < 4;++j)
        {
            cout << mar[i][j]++;
            cout << (j!=3?',':' ');
        }
        cout << ")" << endl;
    }

    const_multi_array_ref<int, 2> cmar(arr, extents[2][6]);

    for (size_t i = 0; i < 2; ++i)
    {
        cout << "(";
        for(size_t j = 0;j < 6;++j)
        {
            cout << cmar[i][j];
            cout << (j!=5?',':' ');
        }
        cout << ")" << endl;
    }

}

//////////////////////////////////////////
void case5()
{
    //multi_array<int, 3> ma(vector<int>(assign::list_of(2)(2)));
    multi_array<int, 3> ma(vector<int>{2,2,2});
    auto shape = ma.shape();
    for (size_t i = 0; i < ma.num_dimensions(); ++i)
    {
        cout << shape[i] << ",";
    }

}

//////////////////////////////////////////
void case6()
{
    typedef multi_array<int, 3> ma_type;
    typedef ma_type::extent_range range;
    ma_type ma(extents [range(1,5)][4][range(-2,2)]);
    ma[1][0][-2] = 10;

    ma.reindex(1);
    assert(ma[1][1][1] == 10);
    ma.reindex(std::array<int,3>{1,0,-4});
    assert(ma[1][0][-4] == 10);

    cout << *ma.index_bases() << endl;
}
//////////////////////////////////////////
void case7()
{
    using namespace boost::detail::multi_array;

    typedef multi_array<int, 3> ma_type;
    typedef ma_type::index_range range;
    ma_type ma(extents[9][8][7]);

    auto view = ma[indices[range()< 3L][2L<=range()<= 5L][range()] ];
    cout << *view.shape() << endl;

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
