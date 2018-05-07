#if !defined(SERIAL_H)
# define SERIAL_H

# include "board.h"

# include <sstream>

class Serial
{
private:
    Board *b;

    void handle_line(string line);
    void handle_del(stringstream &cmd);
    void handle_new(stringstream &cmd);
    void handle_clr(stringstream &cmd);
    void handle_sync(stringstream &cmd);
public:
    void wait(void);
    Serial(Board *brd);
};

#endif
