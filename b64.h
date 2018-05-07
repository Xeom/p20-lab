#if !defined(B64_H)
# define B64_H
# include <sstream>
# include <vector>

using namespace std;

void mem_to_b64(vector<char> &mem, stringstream &ss);

int b64_char_to_mem(char c);

void b64_to_mem(vector<char> &mem, string b64);

#endif