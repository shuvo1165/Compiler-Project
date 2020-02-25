/* ----------------COMPILE DESIGN LAB PROJECT------------



===== ALL KIND OF COMMENTS ELIMINATION
===== WHITE SPACE ELIMINATION FROM A STATEMENT
===== TOKENIZE AND SAVE THE CODE IN FINAL FILE
===== IDENTIFY THE TOKEN


This CODE is fully combined by MD NYMUR RAHMAN SHUVO
ID: 171-15-1165
SECTION: F

!!!!!!!ONLY ONE LINE OF STATEMENT CAN EXECUTE BY THIS PROJECT!!!!!!

*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 1000

//This function eliminates the comments

void commentDelete()
{

    FILE *file1,*file2;
    char ch;

    file1 = fopen("input.txt","r");
    file2 = fopen("temp1.txt","w");

    while((ch=fgetc(file1))!=EOF)
    {
        if(ch=='/')
        {
            ch = fgetc(file1);
            if(ch=='/')
            {
                while(ch=fgetc(file1)!='\n');
            }
            else if(ch=='*')
            {
                while((ch=fgetc(file1))!=EOF)
                {
                    if((ch=fgetc(file1))=='*' && (ch=fgetc(file1))=='/')
                    {
                        ch='\n';
                        break;
                    }
                }
            }
            else
                fputc('/',file2);
        }
        fputc(ch,file2);               //Save the comment free code in a temporary file.
    }
    fclose(file1);
    fclose(file2);
    return ;

}


/* This function will remove extra white space from a statement
!!!!This function is not able to remove extra blank line!!!! */
void whiteSpace()
{
    FILE *fp,*fp2;
    char str[MAXCHAR];
    char blank[100];
    int c=0,d=0;
    fp=fopen("temp1.txt","r");
    fp2=fopen("temp2.txt","w");

    while(fgets(str,MAXCHAR,fp)!=NULL);
        //printf("%s\n",str);

    while(str[c]!='\0')
    {
        if(!(str[c]==' '&& str[c+1]==' '))
        {
            blank[d] =str[c];
            d++;
        }
        c++;
    }
    blank[d]='\0';
    fputs(blank,fp2);                  //Save code in temporary file
    fclose(fp);
    fclose(fp2);
}


//Tokenize the statement base on space
void token()
{

    FILE *fp,*fp2;
    char str[MAXCHAR];
    fp = fopen("temp2.txt","r");
    fp2 = fopen("output.txt","w");
    char *token;
    while(fgets(str,MAXCHAR,fp)!=NULL)
    {
        token = strtok(str," ");
        while(token!=NULL)
        {
            fputs(token,fp2);
            fputs("\n",fp2);
            token = strtok(NULL," ");
        }
    }
    fclose(fp);
    fclose(fp2);
    return ;


}



bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
            ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
            ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '>' || ch == '<' ||
            ch == '=')
        return (true);
    return (false);
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
            str[0] == '3' || str[0] == '4' || str[0] == '5' ||
            str[0] == '6' || str[0] == '7' || str[0] == '8' ||
            str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
            !strcmp(str, "while") || !strcmp(str, "do") ||
            !strcmp(str, "break") ||
            !strcmp(str, "continue") || !strcmp(str, "int")
            || !strcmp(str, "double") || !strcmp(str, "float")
            || !strcmp(str, "return") || !strcmp(str, "char")
            || !strcmp(str, "case") || !strcmp(str, "char"))
        return (true);
    return (false);
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char* str)
{
    int i, len = strlen(str);

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
                && str[i] != '3' && str[i] != '4' && str[i] != '5'
                && str[i] != '6' && str[i] != '7' && str[i] != '8'
                && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char* str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
                && str[i] != '3' && str[i] != '4' && str[i] != '5'
                && str[i] != '6' && str[i] != '7' && str[i] != '8'
                && str[i] != '9' && str[i] != '.' ||
                (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

// Extracts the SUBSTRING.
char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                       sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

// Parsing the input STRING.
void identify(char* str)
{
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right)
    {
        if (isDelimiter(str[right]) == false)
            right++;

        if (isDelimiter(str[right]) == true && left == right)
        {
            if (isOperator(str[right]) == true)
                printf("'%c' IS AN OPERATOR\n", str[right]);

            right++;
            left = right;
        }
        else if (isDelimiter(str[right]) == true && left != right
                 || (right == len && left != right))
        {
            char* subStr = subString(str, left, right - 1);

            if (isKeyword(subStr) == true)
                printf("'%s' IS A KEYWORD\n", subStr);

            else if (isInteger(subStr) == true)
                printf("'%s' IS AN INTEGER\n", subStr);

            else if (isRealNumber(subStr) == true)
                printf("'%s' IS A REAL NUMBER\n", subStr);

            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false)
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);

            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false)
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            left = right;
        }
    }
    return;
}


// Driver function
int main()
{
    printf("---------------------------------------\n");
    printf("---------- Simple Compilation ---------\n");
    printf("---------------------------------------\n\n");
    printf("Final outcome is saved is output.txt file\n\n\n");

    commentDelete(); // calling commentDelete function
    whiteSpace();  // calling space removal function
    token();      // calling tokenization function
    FILE *fp;
    char str[MAXCHAR];

    fp=fopen("temp2.txt","r");

    while(fgets(str,MAXCHAR,fp)!=NULL);

    fclose(fp);
    identify(str); // calling the identify function

    return (0);
}

