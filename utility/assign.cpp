// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
//using namespace boost::assign;

//////////////////////////////////////////
void case1()
{
    using namespace boost::assign;
    vector<int> v;
    v += 1,2,3,4,5, 6*6;

    for(auto& x : v)
        cout << x << ",";
    cout << endl;

    set<string> s;
    s += "cpp", "java", "c#", "python";

    for(auto& x : s)
        cout << x << ",";
    cout << endl;

    map<int, string> m;
    m += make_pair(1, "one"),make_pair(2, "two");

}

//////////////////////////////////////////
#include <forward_list>
void case2()
{
    using namespace boost::assign;

    vector<int> v;
    push_back(v)(1)(2)(3)(4)(5);

    list<string> l;
    push_front(l)("cpp")("java")("c#")("python");

    forward_list<string> fl;
    push_front(l)("matrix")("reload");

    set<double> s;
    insert(s)(3.14)(0.618)(1.732);

    map<int, string> m;
    insert(m)(1, "one")(2, "two");
}

//////////////////////////////////////////
void case3()
{
    using namespace boost::assign;

    vector<int> v;
    push_back(v),1,2,3,4,5;
    push_back(v)(6),7,64 / 8,(9),10;

    for(auto& x : v)
        cout << x << ",";
    cout << endl;

    deque<string> d;
    push_front(d)() = "cpp","java","c#","python";
    assert(d.size()==5);

    for(auto& x : d)
        cout << x << ",";
    cout << endl;

}

//////////////////////////////////////////
void case4()
{
    using namespace boost::assign;

    vector<int> v = list_of(1)(2)(3)(4)(5);
    // v = [1, 2, 3, 4, 5]

    deque<string> d =
        (list_of("power")("bomb"),"phazon","suit");
    // d = [power bomb phazon suit]

    set<int> s = (list_of(10), 20,30,40,50);
    // s = {10 20 30 40 50}

    map<int, string> m = list_of(make_pair(1, "one"))(make_pair(2, "two"));
    // m = [(1, “one”) (2, “two”)]

    map<int, int> m1 = map_list_of(1, 2)(3, 4)(5, 6);
    //m1 = [(1, 2)(3, 4)(5, 6)]

    map<int, string> m2 = map_list_of(1, "one")(2, "two");
    //m2 = [(1, "one")(2, "two")]

}

//////////////////////////////////////////
#include <cstdlib>                          //for rand()

void case5()
{
    using namespace boost::assign;

    vector<int> v = list_of(1).repeat(3, 2)(3)(4)(5);
    //v = 1,2,2,2,3,4,5
    for(auto& x : v)
        cout << x << ",";
    cout << endl;


    multiset<int> ms ;
    insert(ms).repeat_fun(5, &rand).repeat(2, 1), 10;
    //ms = x,x,x,x,x,1,1,10
    for(auto& x : ms)
        cout << x << ",";
    cout << endl;


    deque<int> d;
    push_front(d).range(v.begin(), v.begin() + 5);
    //d = 3,2,2,2,1
    for(auto& x : d)
        cout << x << ",";
    cout << endl;

}


//////////////////////////////////////////
#include <stack>
#include <queue>

void case6()
{
    using namespace boost::assign;

    stack<int> stk = (list_of(1), 2, 3).to_adapter();
    stk += 4, 5, 6;
    for(;!stk.empty();)
    {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;

    queue<string> q = (list_of("china")("us")("uk")).
        repeat(2, "russia").to_adapter();
    push(q)("germany");
    for(;!q.empty();)
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    priority_queue<double> pq = (list_of(1.414), 1.732, 2.236).to_adapter();
    push(pq),3.414,2.71828;
    for(;!pq.empty();)
    {
        cout << pq.top() << " " ;
        pq.pop();
    }

}


//////////////////////////////////////////
void case7()
{
    using namespace boost::assign;

    int a = 1, b = 2, c = 3;

    vector<int> v = ref_list_of<3>(a)(b)(c);
    assert(v.size() == 3);
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
