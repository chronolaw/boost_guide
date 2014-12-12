// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/array.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    array<int, 10> ar;

    ar[0] = 1;
    ar.back() = 10;
    assert(ar[ar.max_size() - 1] == 10);

    ar.assign(777);
    for (auto x : ar)
    {   std::cout << x << ",";   }

    int *p = ar.c_array();
    *(p + 5) = 253;
    std::cout << ar[5] << std::endl;

    ar.at(8) = 666;
    std::sort(ar.begin(), ar.end());

}

//////////////////////////////////////////
#include <boost/assign.hpp>

void case2()
{
    array<std::string, 3> ar = {"alice","bob", "carl"};

    int a[10] = {0};
    array<int, 10> ar1 = {0};
    assert(std::equal(ar1.begin(), ar1.end(), a));

    array<std::string, 3> ar2 = {"racer"};
    assert(ar2.at(1).empty());

    using namespace boost::assign;
    array<int, 3> arr(list_of(2)(4)(6)) ;

    for (int i = 0;i< arr.size() ;++i)
    {   std::cout << arr[i] << ",";}

}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
}
