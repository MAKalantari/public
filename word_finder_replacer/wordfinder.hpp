//written by: cppdev.blog.ir
int     find (const char*, const char*),
        length (const char*);

void    replace (char*&, const char*),
        putString (char*&, const char*);

class array
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

void array::add (int element)
{
    int temp[size];

    for (int i = 0; size > 0 && i < size; i++)
        temp[i] = mainArr[i];

    size++;
    mainArr = new int [size];

    if (size > 1)
        for (int i = 0; i < size-1; i++)
            mainArr[i] = temp[i];
    if (size > 0)
        mainArr[size-1] = element;
}

int find (const char* str, const char* word)
{
    highlight.size = 0;
    highlight.mainArr = new int;

    int count = 0,
        check = 0,

        strLength = length(str),
        wordLength = length(word);

    for (int i = 0; i < length(str); i++)
    {
        if (str[i] == word[check])
            check++;
        else
            check = 0;

        if (check == length(word))
        {
            highlight.add(i-check+1);
            highlight.add(i);
            check = 0;
            count++;
        }
    }
    return count;
}

int length (const char* str)
{
    int i = 0;
    for (; str[i] != 0; i++);
    return i;
}


void replace(char *&str, const char *word)
{
    int newSize, tempSize, difference = 0, count = 0;
    char *temp;

    for (int i = 0; i < highlight.size; i+=2)
        difference += highlight.mainArr[i+1] - highlight.mainArr[i] + 1;
    difference = (length(word) * highlight.size/2) - difference;

    tempSize = length(str);
    newSize = length(str) + difference;

    temp = new char [tempSize+1];

    for (int i = 0; i < length(str); i++)
        temp[i] = str[i];

    str = new char [newSize+1];

    for (int str_i = 0, temp_i = 0; str_i < newSize+1;)
    {
        if (highlight.mainArr[count] == temp_i)
        {
            for (int i = 0; i < length(word); i++, str_i++)
                str[str_i] = word[i];

            temp_i += highlight.mainArr[count+1] - highlight.mainArr[count] + 1;
            count += 2;
        }
        else
        {
            str[str_i] = temp[temp_i];
            str_i++;
            temp_i++;
        }

    }
    str[newSize] = 0;
}
//cppdev.blog.ir
