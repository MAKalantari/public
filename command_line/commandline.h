#include <iostream> //for cout and cin
#include <vector>
#include <windows.h> //for system() and keyboard events
#include <conio.h> //for getch()

int getLength(char*); //gets the length of char*
bool compareStr(char*, char*); //compares the characters and size of to char*
char* guess (char*); //guesses the word being typed by user by comparing the input with commands_context array
void addCharToStr (char*&, char); //ads a character to the end of a char*
void shrinkStrFromEnd (char*&, int); //removes character(s) from the end of a char*
void commandLineLoop(char*);
///main function to run the command line interface and getting commands from user in a loop
///this function should be called after all the commands defined
///you can change the syntax for exiting the loop

class command; //predefined to make a vector of commands
std::vector <command*> commands; //an array of all the commands
std::vector <char*> commands_context; //an array of all the syntaxes from commands

class command
{
private:
    std::vector <char*> context; //syntaxes that call this command
    std::vector <void(*)()> functions; //functions that should run after being called

public:
    command() //construct
    {
        commands.push_back(this);
        //adding this command to the array of commands
    }

    command &operator >> (char* setContext)
    {
        context.push_back(setContext);
        commands_context.push_back(setContext);
        return *this;
    }

    command &operator >> (void setFunction (void))
    {
        functions.push_back(setFunction);
        return *this;
    }

    bool isThisComamnd (char* syntax) //checks if the syntax matches with this command's syntax(es)
    {
        for (int i = 0; i < context.size(); i++)
        if (compareStr(context[i], syntax))
            return true;
        return false;
    }

    bool operator == (char* syntax) //checks if the syntax matches with this command's syntax(es) same as isThisCommand
    {
        isThisComamnd (syntax);
    }

    bool operator != (char* withContext) //checks if the syntax matches with this command's syntax(es) if it does, returns false
    {
        bool result = true;
        for (int i = 0; i < context.size(); i++)
        if (context[i] == withContext)
            result = false;
        return result;
    }

    void run(); // runs all functions
}incorrectCommand; //default command to return if no command matched the input that the user entered

void incorrectCommand_function() {std::cout << "incorrect command";};

void command::run()
{
    for (int i = 0; i < functions.size(); i++)
        functions[i]();
}

command* returnCommand (char* context)
//gets a certain syntax (context) and checks if any command owns that context (from commands array),
//returns the first one that does
{
    for (int i = 0; i < commands.size(); i++)
    if (commands[i]->isThisComamnd(context))
        return commands[i];
    command* incorrectCommandPtr = &incorrectCommand;
    return incorrectCommandPtr;
}

void commandLineLoop(char* exit_command = "exit loop") //this function should be called to use commandline's default interface
{
    incorrectCommand >> incorrectCommand_function; //setting up the default object with it's function
    char* lastCommand; //the last input by user, witch can be accessed with pressing UP key
    std::cout << "HINT: " << "enter commands (LCTRL+SPACE: AUTO  COMPLETE | UP: LAST COMMAND)" << std::endl << "------------------------------" << std::endl;

    while (true)//start of the main loop
    {
        char *input; //saves the user's input
        input = new char [1]; //set the size of the string to one and the only element to zero to define the strings end
        input[0] = 0;

        while (true) //this loop gets every character that being received from the keyboard and only pressing ENTER key breaks it
        {
            char tempChar;
            tempChar = getch();

            if (GetAsyncKeyState(VK_RETURN)) //if input is ENTER key
            {
                system("cls"); //clears all the screen
                std::cout << "HINT: " << "enter next command (LCTRL+SPACE: AUTO  COMPLETE | UP: LAST COMMAND)" << std::endl << "------------------------------" << std::endl;
                break; //breaks this loop
            }
            else if (GetAsyncKeyState(VK_BACK)) //if input is BACKSPACE key
                shrinkStrFromEnd(input, 1); //removes one character from the input
            else if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_SPACE)) //if LCONTROL and SPACE are being pressed together
                input = guess(input); //guess the rest of the word and make the input string as same as the guessed syntax is
            else if (GetAsyncKeyState(VK_UP))
                input = lastCommand; //with pressing up shoes the latest command entered by user
            else addCharToStr(input, tempChar);

            system("cls");
            std::cout << "HINT: " << guess(input) << " (LCTRL+SPACE: AUTO  COMPLETE | UP: LAST COMMAND)" << std::endl << "------------------------------" << std::endl;
            std::cout << input;
        }
        lastCommand = input;
        if (compareStr(input, exit_command)) //breaks the commandLineLoop
            break;
        else //if its not the syntax for breaking the loop
            returnCommand(input)->run(); //gets the input and if it matches any command it runs that commands function
    }
}

int getLength(char* str) //explained in definition
{
    int length = 0;
    for (; str[length] != 0; length++);
    return length;
}

bool compareStr (char* left, char* right) //explained in definition
{
    int leftLength, rightLength;
    leftLength = getLength(left);
    rightLength = getLength(right);
    if (leftLength == rightLength)
    {
        for (int i = 0; i < leftLength; i++)
            if (left[i] != right[i])
                return false;
    }
    else return false;
    return true;
}

void addCharToStr (char *&str, char add) //explained in definition
{
    int strSize = getLength(str);
    char *tempStr = new char [strSize];
    for (int i = 0; i < strSize; i++)
        tempStr[i] = str[i];
    strSize++;
    str = new char [strSize+1];
    for (int i = 0; i < strSize-1; i++)
        str[i] = tempStr[i];
    str[strSize-1] = add;
    str[strSize] = 0;
}

void shrinkStrFromEnd (char *&str, int value) //explained in definition
{
    int newStrSize = getLength(str) - value;
    if (newStrSize < 0)
        newStrSize = 0;
    char *tempStr = new char [newStrSize];
    for (int i = 0; i < newStrSize; i++)
        tempStr[i] = str[i];
    str = new char [newStrSize+1];
    for (int i = 0; i < newStrSize; i++)
        str[i] = tempStr[i];
    str[newStrSize] = 0;
}

char* guess(char* input)
{
    int numberOfCommands = commands_context.size();
    for (int commandNumber = 0; commandNumber < numberOfCommands; commandNumber++)
    {
        for (int pos = 0; pos < getLength(input); pos++)
        {
            if (commands_context[commandNumber][pos] != input[pos])
                break;
            else
            {
                if (pos == getLength(input)-1)
                    return commands_context[commandNumber];
            }
        }
    }
    return (char*)"no match found";
}
