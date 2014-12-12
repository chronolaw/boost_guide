// Copyright (c) 2015
// Author: Chrono Law
#include <fstream>
#include <sstream>
#include <std.hpp>
using namespace std;

#include <boost/program_options.hpp>
using namespace boost::program_options;

//////////////////////////////////////////
int case1(int argc, char* argv[])
{
    options_description opts("demo options");

    opts.add_options()
        ("help", "just a help info")
        ("filename", value<string>(), "to find a file")
        ;
    variables_map vm;
    store(parse_command_line(argc, argv, opts), vm);


    if (vm.count("help"))
    {
        cout << opts << endl;
        return 0;
    }

    if (vm.count("filename"))
    {   cout << "find " << vm["filename"].as<string>() << endl;}

    if (vm.empty())
    {   cout << "no options" << endl;   }

    return 0;
}

//////////////////////////////////////////

void case2()
{
    value<string>();

    value<int>()->default_value(10)
        ->implicit_value(1);

    double x;
    value<double>(&x)->zero_tokens()
        ->multitoken()->required();

}

//////////////////////////////////////////
void print_vm(options_description &opts, variables_map &vm)
{
    if (vm.empty())
    {
        cout << opts << endl;
        return;
    }

    if (vm.count("help"))
    {
        cout << opts << endl;
    }

    //输出查找文件名，因为它有缺省值，故总存在
    cout << "find opt:" << vm["filename"].as<string>() << endl;

    if (vm.count("dir"))
    {
        cout << "dir opt:";
        for(auto& str:
                vm["dir"].as<vector<string> >())
        {   cout << str << ","; }
        cout << endl;
    }

    if (vm.count("depth"))
    {   cout << "depth opt:" << vm["depth"].as<int>() << endl;}
}

void case3(int argc, char* argv[])
{
    options_description opts("demo options");

    string filename;
    opts.add_options()

        ("help,h", "help message\n   a bit of long text")

        ("filename,f",
         value<string>(&filename)->default_value("test"), "to find a file")

        ("dir,D", value<vector<string> >()->multitoken(), "search dir")

        ("depth,d", value<int>()->implicit_value(5), "search depth")
        ;

    variables_map vm;
    store(parse_command_line(argc, argv, opts), vm);
    notify(vm);

    print_vm(opts, vm);

    stringstream ss;
    ss << "filename=a.cpp\ndir=/usr/bin\ndepth=10";
    store(parse_config_file(ss, opts), vm);

    ifstream ifs("config.ini");
    store(parse_config_file(ifs, opts, true), vm);

    const char *str = "config.ini";
    store(parse_config_file<char>(str, opts, true), vm);

}

//////////////////////////////////////////
void case4(int argc, char* argv[])
{
    options_description opts("demo options");

    string filename;
    opts.add_options()

        ("help,h", "help message\n   a bit of long text")

        ("filename,f",
         value<string>(&filename)->default_value("test"), "to find a file")

        ("dir,D", value<vector<string> >()->multitoken(), "search dir")

        ("depth,d", value<int>()->implicit_value(5), "search depth")
        ;

    variables_map vm;

    positional_options_description pod;
    pod.add("filename", 1).add("dir", 2).add("depth", -1);
    auto pr =
        command_line_parser(argc, argv).
            options(opts).
                positional(pod).
                    run();
                    store(pr, vm );

    notify(vm);
    print_vm(opts, vm);
}

//////////////////////////////////////////
string name_mapper(const string& env_name)
{
    static map<string, string> nm =
        {{"HOME", "home"},{"USER", "uname"}};

    return nm[env_name];
}

void case5(int argc, char* argv[])
{
    options_description opts("demo options");

    string filename;
    opts.add_options()

        ("help,h", "help message\n   a bit of long text")

        ("filename,f",
         value<string>(&filename)->default_value("test"), "to find a file")

        ("dir,D", value<vector<string> >()->multitoken(), "search dir")

        ("depth,d", value<int>()->implicit_value(5), "search depth")
        ("home", value<string>(), "home dir")
        ("uname", value<string>(), "user's name")

        ;

    variables_map vm;

    store(parse_environment(opts, name_mapper),vm);
    cout << vm["home"].as<string> ()<< endl;
    cout << vm["uname"].as<string> ()<< endl;

    notify(vm);
    print_vm(opts, vm);
}

//////////////////////////////////////////
void case6(int argc, char* argv[])
{
    options_description opts1("group 1");
    opts1.add_options()
        ("help,h", "help message");

    options_description opts2("group 2(hide)");
    opts2.add_options()
        ("filename,f", value<string>(), "to find a file");

    options_description opts3("group 3");
    opts3.add_options()
        ("dir,D", value<vector<string> >()->composing(), "search dir")
        ("depth,d", value<int>(), "search depth");

    options_description opts_all;
    opts_all.add(opts1).add(opts2).add(opts3);

    options_description opts_cfgfile;
    opts_cfgfile.add(opts2).add(opts3);

    options_description opts_showhelp("demo options");
    opts_showhelp.add(opts1).add(opts3);

    variables_map vm;

    store(parse_command_line(argc, argv, opts_all), vm);
    store(parse_config_file<char>("config.ini", opts_cfgfile, true), vm);

    if (vm.count("help") || vm.empty())
    {
        cout << opts_showhelp << endl;
        return;
    }

    notify(vm);
    print_vm(opts_all, vm);
}


//////////////////////////////////////////

int main(int argc, char* argv[])
{
    //case1(argc, argv);
    case2();
    //case3(argc, argv);
    //case4(argc, argv);
    //case5(argc, argv);
    case6(argc, argv);
}

