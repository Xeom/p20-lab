#include "serial.h"
#include "b64.h"

#include <string>
#include <iostream>

#if !defined(NO_UART)
# include <wiringPi.h>
# include <wiringSerial.h>
#endif

extern int serialfd;

Serial::Serial(Board *brd)
{
    b = brd;
}

void Serial::wait(void)
{
    vector<char> buf;

    int c = '\0';
    string line;

    do
    {
#if !defined(NO_UART)
        c = serialGetchar(serialfd);
#else
        c = getchar();
#endif
        if (c < 0) continue;

        buf.push_back(c);
    } while (c != '\n' && c != '\r');

    line = string(buf.begin(), buf.end());

    cout << line;

    handle_line(line);
}

void Serial::handle_line(string line)
{
    stringstream stream(line);
    char type;

    stream >> type;
    
    switch (type)
    {
    case 'n':
        handle_new(stream);
        break;
    case 'd':
        handle_del(stream);
        break;
    case 'c':
        handle_clr(stream);
        break;
    case 's':
        handle_sync(stream);
        break;
    }
}

void Serial::handle_new(stringstream &cmd)
{
    int id;
    Line l;
    string info;
    vector<char> data;
    
    cmd >> id >> info;

    b64_to_mem(data, info);
    
    l.deserialize(data);

    pthread_mutex_lock(&(b->lock));

    b->new_line(l, id);

    pthread_mutex_unlock(&(b->lock));

    b->update();
}

void Serial::handle_del(stringstream &cmd)
{
    int id;

    cmd >> id;

    pthread_mutex_lock(&(b->lock));

    b->del_line(id);

    pthread_mutex_unlock(&(b->lock));

    b->update();
}

void Serial::handle_clr(stringstream &cmd)
{
    pthread_mutex_lock(&(b->lock));

    b->clear();

    pthread_mutex_unlock(&(b->lock));

    b->update();
}

void Serial::handle_sync(stringstream &cmd)
{
    b->sync();
}
