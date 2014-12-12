// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;
namespace fs = boost::filesystem;

//////////////////////////////////////////
void case1()
{
    path p1("./a_dir");
    path p2("/usr/local/lib");
    path p3("c:\\tmp\\test.text");
    path p4("d:/boost/boost/filesystem/");

    path p5;
    assert(p5.empty());

}

//////////////////////////////////////////
void case2()
{
    char str[] = "the path is (/root).";

    {
        path p(str + 13, str + 14);
        assert(!p.empty());

        p /= "etc";
        string filename = "xinetd.conf";
        p.append(filename.begin(), filename.end());
        cout << p << endl;
        cout << system_complete(p) << endl;
    }

    {
        path p(str + 13, str + 15);

        p += "etc";
        string filename = "xinetd.conf";
        p.concat(filename.begin(), filename.end());
        cout << p << endl;
    }

    path p("/::/*/?/<>");
}

//////////////////////////////////////////
void case3()
{
    string fname("w+abc.xxx");
    assert(!portable_posix_name(fname));
    assert(windows_name(fname));

    assert(!portable_name("w+()abc.txt")    && !portable_name("./abc"));
    assert(!portable_directory_name("a.txt") && portable_directory_name("abc"));
    assert( portable_file_name("a.bc") && !portable_file_name("y.conf"));

}

//////////////////////////////////////////
void case4()
{
    path p("/usr/local/include/xxx.hpp");

    cout << p.string() << endl;

    cout << p.parent_path() << endl;
    cout << p.stem() << endl;
    cout << p.filename() << endl;
    cout << p.extension() << endl;

    assert(p.is_absolute());
    assert(system_complete(p).is_absolute());

    cout << p.root_name() << endl;
    cout << p.root_directory() << endl;
    cout << p.root_path() << endl;

    assert(!p.has_root_name());
    assert( p.has_root_path());
    assert( p.has_parent_path());

    cout << p.replace_extension() << endl;
    cout << p.replace_extension("hxx") << endl;
    cout << p.remove_filename() << endl;

    path p1("/test/1.cpp");
    path p2("/TEST/1.cpp");
    path p3("/abc/1.cpp");

    assert(p1 != p2);
    assert(p2 < p3);

    p = "/boost/tools/libs";

    BOOST_FOREACH(auto& x , p)
    {
            cout << "["<< x << "]";
    }

}

//////////////////////////////////////////
void case5()
{
    path p("/test.txt");

    try
    {
        file_size(p);
    }
    catch(filesystem_error& e)
    {
        cout << e.path1() << endl;
        cout << e.what() << endl;
    }

}

//////////////////////////////////////////
void case6()
{
    assert(status("/dev/null").type()   == character_file);
    assert(status("/bin").type()    == directory_file);
    assert(status("/bin/sh").type()     == regular_file);

    assert((status("/bin/sh").permissions() & owner_exe) == owner_exe);

    path root = "/usr/local/include/boost";

    assert( is_directory(root));
    assert(!exists(root/"nofile"));
    assert(!is_symlink(root/"version.hpp"));
    assert(!is_other(root/"version.hpp"));
    assert( is_regular_file(root/"version.hpp"));
    assert(!fs::is_empty(root/"version.hpp"));

}

//////////////////////////////////////////
void case7()
{
    cout << initial_path() << endl;
    cout << current_path() << endl;

    //path p("/usr/local/include/boost/version.hpp");
    path p("./test.txt");
    cout << file_size(p) << endl;

    time_t t = last_write_time(p);
    last_write_time(p, time(0));

}

//////////////////////////////////////////
#include <boost/ratio.hpp>
void case8()
{
    using namespace boost;
    //const int GBYTES = 1000*1000*1000;          //GB，不是GiB
    space_info si = space("/home/chrono");
    cout << si.capacity / giga::num<< endl;
    cout << si.available / giga::num<< endl;
    cout << si.free / giga::num<< endl;
}

//////////////////////////////////////////
void case9()
{
    //namespace fs = boost::filesystem;

    path ptest = "./test";
    if (exists(ptest))
    {
        if (fs::is_empty(ptest))
        {
            remove(ptest) ;
        }
        else
        {
            remove_all(ptest);
        }
    }

    assert(!exists(ptest));
    create_directory(ptest) ;

    copy_file("/usr/local/include/boost/version.hpp", ptest / "a.txt");
    assert(exists(ptest / "a.txt"));

    rename(ptest / "a.txt", ptest / "b.txt");
    assert(exists(ptest / "b.txt"));

    create_directories(ptest / "sub_dir1" / "sub_dir1");
}

//////////////////////////////////////////
void case10()
{
    //directory_iterator end;
    //for (directory_iterator pos("/usr/local/lib/");pos != end; ++pos)
    //{       cout << *pos << endl;   }

    typedef std::pair<directory_iterator, directory_iterator> dir_range;
    dir_range dr(directory_iterator("/usr/local/lib/"),
    directory_iterator());

    BOOST_FOREACH(auto& x , dr)
    {      cout << x << endl;       }

    typedef recursive_directory_iterator rd_iterator;

    rd_iterator  end;
    for (rd_iterator pos("/usr/local/lib/");pos != end; ++pos)
    {
        cout << "level" << pos.level() << ":" <<*pos << endl;
    }


}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
    //case5();
    case6();
    case7();
    case8();
    //case9();
    case10();
}

