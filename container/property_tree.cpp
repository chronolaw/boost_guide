// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
using namespace boost::property_tree;

//////////////////////////////////////////
void case1()
{
    ptree pt;
    read_xml("conf.xml", pt);

    pt.get<string>("conf.theme");
    pt.get<int>("conf.clock_style");
    pt.get("conf.no_prop", 100);

    cout << pt.get<string>("conf.theme") << endl;
    cout << pt.get<int>("conf.clock_style") << endl;
    cout << pt.get<long>("conf.gui")<< endl;
    cout << pt.get("conf.no_prop", 100)<< endl;

    auto child = pt.get_child("conf.urls");
    for (auto& x : child)
    {   cout <<  x.second.get_value<string>() << ",";   }
    cout << endl;

    for(auto& x : pt.get_child("conf.urls"))
    {
        cout <<  x.second.data() << ",";
    }
    cout << endl;

}

//////////////////////////////////////////
void case2()
{
    ptree pt;
    read_xml("conf.xml", pt);

    pt.put("conf.theme", "Matrix Reloaded");
    pt.put("conf.clock_style", 12);
    pt.put("conf.gui", 0);
    //pt.put("conf.urls.url", "http://www.url4.org");
    pt.add("conf.urls.url", "http://www.url4.org");

    write_xml(cout , pt);
}

//////////////////////////////////////////
void case3()
{
    ptree pt;
    read_xml("conf.xml", pt);
    cout << pt.get<string>("conf.<xmlcomment>") << endl;
    cout << pt.get<string>("conf.clock_style.<xmlattr>.name") << endl;
    cout << pt.get<long>("conf.theme.<xmlattr>.id")<< endl;
    cout << pt.get<string>("conf.urls.<xmlcomment>")<< endl;

}
//////////////////////////////////////////
#include <boost/property_tree/json_parser.hpp>
void case4()
{
    ptree pt;
    read_json("conf.json", pt);

    cout << pt.get<string>("conf.theme") << endl;
    cout << pt.get<int>("conf.clock_style") << endl;
    cout << pt.get<long>("conf.gui")<< endl;
    cout << pt.get("conf.no_prop", 100)<< endl; 

    for (auto x : pt.get_child("conf.urls"))
    {   cout <<  x.second.data() << ",";    }

}
//////////////////////////////////////////
int main()
{
    case1();
    case2();
    case3();
    case4();
}
