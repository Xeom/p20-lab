#include "b64.h"
#include <bitset>
#include <algorithm>

using namespace std;

char alphabet[] = "+-0123456789"
                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  "abcdefghijklmnopqrstuvwxyz";

void mem_to_b64(vector<char> &mem, stringstream &ss)
{
    int bit, len, outpos, inpos, inind;
    bitset<6> chr;

    len = 8 * mem.size();
    
    for (bit = 0; bit < len; bit++)
    {
        outpos = bit % 6;
        inpos  = bit % 8;
        inind  = bit / 8;

        char in = mem[inind];

        chr[outpos] = (bool)(in & (1 << inpos));

        if (outpos == 5 || bit == len - 1)
            ss << alphabet[chr.to_ulong()];
    }
}

int b64_char_to_mem(char c)
{
    if (c == '+') return  0;
    if (c == '-') return  1;
    if (c <= '9') return  2 + (c - '0');
    if (c <= 'Z') return 12 + (c - 'A');

    return 38 + (c - 'a');
    
}

void b64_to_mem(vector<char> &mem, string b64)
{
    int bit, len, outpos, inpos, inind, in;

    bitset<8> chr;

    b64.erase(std::remove(b64.begin(), b64.end(), ' '), b64.end());
    
    len = b64.length() * 6;

    for (bit = 0; bit < len; bit++)
    {
        outpos = bit % 8;
        inpos  = bit % 6;
        inind  = bit / 6;

        if (inpos == 0)
            in = b64_char_to_mem(b64[inind]);

        chr[outpos] = (bool)(in & (1 << inpos));
        
        if (outpos == 7)
            mem.push_back((char)chr.to_ulong());
    }

}
