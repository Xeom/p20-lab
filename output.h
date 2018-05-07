#if !defined(OUTPUT_H)
# define OUTPUT_H
# include <string>
# include "line.h"

using namespace std;

class Output
{
protected:
    int fds[2];
    int serialfd;

public:
    void send(char cmd, int id, Line *l);
    void wait(void);
    Output(int fd);
};

#endif
