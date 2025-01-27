#include <stdio.h>
#include "input.h"

int main()
{
    start_input();
    while(1)
    {
        printf("%c", get_key());
        fflush(stdout);
    }
    end_input();
}