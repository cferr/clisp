#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "env.h"
#include "common.h"

int main(int argc, char* argv[])
{
    char testbuf[] = "((((a = 0))(b = 0)(c = 1)))";
    
    bufword* newbuf = new_bufword();
    env* testenv = create_environment();
    unsigned int seek = 0;
    
    bufword* wd = newbuf;
    
    parse(testbuf, testenv, &newbuf, strlen(testbuf), &seek);
    
    
    
    while(wd)
    {
        printf("word : %s\n", wd->wd);
        wd = wd->next;
    }
    
    // if it doesn't crash then we're almost done
    
    return 0;
}
