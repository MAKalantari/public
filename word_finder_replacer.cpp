/**
this is not licensed, you can use or change it freely.
project name: word finder/replacer
written by: cppdev.blog.ir
telegram: @greatmak
**/

int     find (const char*, const char*), //find a specific word in the string.
        length (const char*); //find strings length.

void    replace (char*&, const char*), //replace highlighted characters with a new word in the string.
        putString (char*&, const char*); //filling "char*" with characters one by one.

class array //it kind of does work like vector but only with push_back option (8 bytes of memory occupies).
{
public:
    array();
    int *mainArr, size;
    void add(int);
}highlight;

array::array()
{
    size = 0;
}

///any thing in main section is not necessary to the main code.
/*it's only for making the visual content.
if you don't want it just remove the codes, in that case
"windows.h" library will be useless and you can exclude it.*/
int main()
{
    char    *word = new char [100], *newWord = new char[100], *str = new char [100];


    putString(str, "this is the string");
    putString(word, "the");
    putString(newWord, "a");
    find (str, word);
    replace (str, newWord);
    //final result will be "this is a string".

    return 0;
}

int find (const char* str, const char* word)
{
    //reseting highlight.
    highlight.size = 0;
    highlight.mainArr = new int;


    int count = 0, //count of that how many "word"s are in "str". also will be used as return.
        check = 0,

        strLength = length(str),
        wordLength = length(word);

    for (int i = 0; i < length(str); i++)
    {

        if (str[i] == word[check]) //comparing str with word character by character.
            check++;
        else //if some character doesn't match up.
            check = 0;

        //if all the characters were the same, check is going to be same number as the word's length.
        if (check == length(word))
        {
            highlight.add(i-check+1); //adding position of the first character in string to the highlight array.
            highlight.add(i); //adding position of the last character in string to the highlight array.
            check = 0;
            count++;
        }
    }
    return count;
}

//using this function is optional.
//it's a safe way to fill a char* whit characters.
void putString (char *&_char, const char *_input)
{
    const int _length = length(_input);
    _char = new char [_length+1];
    for (int i = 0; i < _length; i++)
        _char[i] = _input[i];
    _char[_length] = 0;
}

//does the string.length() work
int length (const char* str)
{
    int i = 0;
    for (; str[i] != 0; i++);
    return i;
}

void array::add (int element)
{
    int temp[size];

    //copying mainArr to temp
    for (int i = 0; size > 0 && i < size; i++)
        temp[i] = mainArr[i];

    size++; //size adds up because we are adding an new element.
    mainArr = new int [size]; //giving mainArr the new size to add an new element.

    if (size > 1)
        for (int i = 0; i < size-1; i++) //copying old values from temp to mainArr.
            mainArr[i] = temp[i];
    if (size > 0) //just in case checks that mainArr size is bigger then 0.
        mainArr[size-1] = element; //adding the element at the end.
}

//this function only works if "find" function was used before. if not, it will do nothing.
void replace(char *&str, const char *word)
{
    /*"count" is going to be used for finding out that which highlighted part of string we are in.
    if its 0, we are in first one, if its 2 we are in second one, 6 is third and so on.*/
    int newSize, tempSize, difference = 0, count = 0;
    char *temp; //temp for saving str old characters.

    /* finding out the total difference between the current string's length
    and the string that we are going to have after replace it's highlighted
    parts with the "word". in other word, size of the str after the changes.*/
    for (int i = 0; i < highlight.size; i+=2)
        difference += highlight.mainArr[i+1] - highlight.mainArr[i] + 1;
    difference = (length(word) * highlight.size/2) - difference;

    tempSize = length(str);
    newSize = length(str) + difference; //the size of the string after changes

    temp = new char [tempSize+1];
    //copying str to temp
    for (int i = 0; i < length(str); i++)
        temp[i] = str[i];

    str = new char [newSize+1]; //giving str the new size.

    //runs a loop till the end of the str with it's new size.
    for (int str_i = 0, temp_i = 0; str_i < newSize+1;)
    {
        /* checks that if current position of "temp" equals to
        the current highlighted part of it or "not".
        the reason to this is that if we are in highlighted part
        of temp, instead of writing it in the str we should skip
        it and write the new "word".*/
        if (highlight.mainArr[count] == temp_i)
        {
            for (int i = 0; i < length(word); i++, str_i++)
                str[str_i] = word[i];

            temp_i += highlight.mainArr[count+1] - highlight.mainArr[count] + 1; //jumps the highlighted part
            count += 2; /*goes to the next highlighted part
                        (plus two because every part takes two element
                         of position, the start one the end).*/
        }
        else /*if "not" just copy "temp"'s current character to "str"
             and go to the next character in the next round.*/
        {
            str[str_i] = temp[temp_i];
            str_i++;
            temp_i++;
        }

    }
    str[newSize] = 0;
}

//cppdev.blog.ir
