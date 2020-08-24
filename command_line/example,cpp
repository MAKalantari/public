#include "commandline.h"

using namespace std;

//you can define as many as functions you want for a command class
void helloworld_function_part1()
{cout << "Hello ";}

void helloworld_function_part2()
{cout << "word!";}

void quit_function(){exit(0);}

int main()
{
    command helloworld, quit;
    helloworld  >> helloworld_function_part1
                >> helloworld_function_part2
                >> "hello world" >> "print"
                >> "whatever";
                //gets syntaxes and functions for this(helloworld) command
                
    quit        >> "exit" >> quit_function >> "quit" >> "escape";
                //you can also mess with order of syntaxes and functions, it doesnt matter

    commandLineLoop(); //this function should be called after definig commands
    
    /...
    
    return 0;
}
