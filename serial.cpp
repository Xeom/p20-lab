#include "serial.h"

#include <string>

Serial::Serial(Board *brd, istream *file)
{
    b = brd;
    stream = file;
}

void Serial::wait(void)
{
    string line;

    while (1)
    {
        getline(*stream, line);
        handle_line(line);
    }
    
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
    case 'd':
        handle_del(stream);
    }   
}

void Serial::handle_new(stringstream &cmd)
{
    int id;
    Line l;

    cmd >> id;
    l.deserialize(cmd);

    pthread_mutex_lock(&(b->lock));

    b->new_line(l, id);

    pthread_mutex_unlock(&(b->lock));
}

void Serial::handle_del(stringstream &cmd)
{
    int id;

    cmd >> id;

    pthread_mutex_lock(&(b->lock));
    
    b->del_line(id);

    pthread_mutex_unlock(&(b->lock));
}