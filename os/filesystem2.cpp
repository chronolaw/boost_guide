// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/optional.hpp>
#include <boost/utility/string_ref.hpp>

#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
using namespace boost;
using namespace boost::filesystem;
namespace fs = boost::filesystem;

typedef recursive_directory_iterator rd_iterator;
//////////////////////////////////////////
optional<path>
find_file(const path& dir, const string& filename)
{
    typedef optional<path> result_type;
    if (!exists(dir) ||!is_directory(dir))
    {   return result_type();   }

    rd_iterator end;
    for (rd_iterator pos(dir);pos != end; ++pos)
    {
        if(!is_directory(*pos) &&
                pos->path().filename() == filename)
        {   return result_type(pos->path());    }
    }

    return result_type();
}

void case1()
{
    auto r = find_file("/usr/local/include/boost", "version.hpp");

    if (r)
    {   cout << *r << endl; }
    else
    {   cout << "file not found." << endl;  }
}

//////////////////////////////////////////
#include <boost/xpressive/xpressive_dynamic.hpp>
#include <boost/algorithm/string.hpp>
using namespace boost::xpressive;

vector<path> find_files(const path& dir, const string& filename)
{
    static xpressive::sregex_compiler rc;
    if (!rc[filename].regex_id())
    {
        string str = replace_all_copy(
                replace_all_copy(filename, ".", "\\."),
                "*", ".*");
        rc[filename] = rc.compile(str);
    }

    typedef vector<path> result_type;
    result_type v;

    if (!exists(dir) || !is_directory(dir))
    {   return v;    }

    rd_iterator end;
    for (rd_iterator pos(dir);pos != end; ++pos)
    {
        if(!is_directory(*pos) &&
                regex_match(pos->path().filename().string(), rc[filename]))
        {
            v.push_back(pos->path());
        }
    }

    return v;
}

void case2()
{
    auto v = find_files("/usr/local/include/boost/timer", "*.hpp");
    cout << v.size() << endl;

    for(path &p : v)
    {   cout << p << endl;  }

}

//////////////////////////////////////////
#include <boost/progress.hpp>

size_t copy_files(const path& from_dir, const path& to_dir ,
                    const string& filename = "*")
{
    if (!is_directory(from_dir))
    {
        cout << "args is not a dir." << endl;
        return 0;
    }

    cout << "prepare for copy, please wait..." << endl;

    auto v = find_files(from_dir, filename);
    if (v.empty())
    {
        cout << "0 file copied." << endl;
        return 0;
    }

    cout << "now begin copy files ..." << endl;
    path tmp;
    progress_display pd(v.size());

    for(auto& p : v)
    {
        tmp = to_dir / p.string().substr(from_dir.string().length());
        if (!exists(tmp.parent_path()))
        {
            create_directories(tmp.parent_path());
        }
        copy_file(p, tmp);
        ++pd;
    }

    cout << v.size() << " file copied." << endl;
    return v.size();
}

void case3()
{
    copy_files("/usr/local/include/boost/timer", "./t");
}

//////////////////////////////////////////
#include <boost/filesystem/fstream.hpp>
namespace newfs = boost::filesystem;

void case4()
{
    path p("./test.txt");
    newfs::ifstream ifs(p);
    assert(ifs.is_open());
    cout << ifs.rdbuf();
}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
}

