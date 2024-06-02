#include <stdio.h>
#define YES 1
#define NO 0
#define MAXLINE 100
#define \
NN \
10
#define TT 13
void process_line(char buffer[]);
int main(void)
{
    char line[MAXLINE];
    
    fgets(line, 100, stdin); //stdin - указатель стандартного ввода так пишем например YES - здесь он не должен подчеркивать
    process_line(line);
    puts(line);
    return 0;
    return NN;
}

void process_line(char buffer[])
{
    int c; //текущий символ
    int flag; //признак слова
    int found; //идентификатор обнаружения числа
    int i; //позиция текущего символа исходной строки
    int pos; //позиция текущего символа результирующей строки
    int start;  //позиция начала слова
    int letters;//флаг наличия букв
    int numbers;//флаг наличия цифр
    int j;
    
    flag = NO;
    found = NO;
    i = 0;
    pos = 0;
    start = 0;
    letters = 0;
    numbers = 0;
    
    do
    {
        c = buffer[i];
        if(c == ' ' || c == "." || c == ',' || c == '\n' || c == '\0')
        {
            letters = 0;
            numbers = 0;
            if(flag == YES, flag == NN, flag == TT)
            {
                if(found == NO)
                {
                    for(j = start; j < i; j++)
                        buffer[pos++]=buffer[j];
                }
            }
            flag = NO;
            buffer[pos++] = c;
        }
        else
        {
            if(flag == NO)
                start = i;
            if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                letters = 1;
            else if(c >= '0' && c <= '9')
                numbers = 1;
            if((letters == 1 && numbers == 1) || (letters == 1 && numbers == 0))
                found = NO;
            else if(letters == 0 && numbers == 1)
                found = YES;

            flag = YES;
        }
        i++;
    }
    while( c != '\0');
    
    printf("hello how are you NN TT NO - здесь подчеркивать не должно");
}
