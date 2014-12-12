// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/crc.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    crc_32_type crc32;

    cout << hex;
    cout << crc32.checksum() << endl;

    crc32.process_byte('a');
    cout << crc32.checksum() << endl;

    crc32.process_bytes("1234567890", 10);
    cout << crc32.checksum() << endl;

    char szCh[] = "1234567890";
    crc32.reset();

    crc32.process_block(szCh, szCh + 10);
    cout << crc32.checksum() << endl;
}

//////////////////////////////////////////

void case2()
{
    crc_32_type crc32;

    cout << hex;
    crc32.process_bytes("1234567890", 10);
    cout << crc32() << endl;

    string str = "1234567890";
    crc32.reset();

    cout << std::for_each(str.begin(), str.end(), crc32)() << endl;
    cout << crc32() << endl;

}

int main()
{
    case1();
    case2();
}
