#include "output.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>
#include "b64.h"

#if !defined(NO_UART)
# include <wiringPi.h>
# include <wiringSerial.h>
#endif

Output::Output(int fd)
{
    serialfd = fd;

    if (pipe(fds) != 0)
        cout << "Could not open output pipe" << endl;
}

void Output::send(char cmd, int id, Line *l)
{
    ssize_t len;
    string msg;
    stringstream ss;

    ss << cmd << " " << id << " ";

    if (l)
    {
        vector<char> data;
        l->serialize(data);
        mem_to_b64(data, ss);
    }

    ss << endl;
    
    msg = ss.str();
    len = msg.length();
    
    write(fds[1], msg.c_str(), len);
}

void Output::wait(void)
{
    vector<char> buf;

    char c = '\0';
    string str;

    do
    {
        read(fds[0], &c, 1);
        buf.push_back(c);
    } while (c != '\n');

    str = string(buf.begin(), buf.end());

#if !defined(NO_UART)    
    serialPuts(serialfd, str.c_str());
#endif

    cout << str;
}
