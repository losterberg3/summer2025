#include "header.h"
#include <iostream>

int main()
{
    writeAnswer( readNumber() + readNumber() );
 
    return 0;
}

/*
cmake ..
make
./io
*/