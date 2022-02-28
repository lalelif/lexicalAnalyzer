#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

 
bool isDelimiter(char ch);
bool isOperator(char ch);
bool isEndOfLine(char ch);
bool isSeperator(char ch);
bool isEndOfLine(char ch) ;
bool isBlock(char ch);
bool validIdentifier(char* str);
bool isKeyword(char* str);
bool isInteger(char* str);
bool isStringConstant(char *str);
int subString(char *source, int from, int n, char *target);
void parse(char* code,FILE *file);
void isComment(char* str,FILE *file);


bool isDelimiter(char ch)
{
    if (ch == '+' || ch == '-'
        || ch == ',' 
        || ch == '=' || ch == '(' || ch == ')' 
        || ch == '[' || ch == ']'|| ch=='.' )
    {
        return (true);
    }
    return (false);
}

bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '=')
        return (true);
    return (false);
}  
bool isEndOfLine(char ch) 
{
    if (ch=='.')
        return (true);
    return (false);    
 } 
bool isSeperator(char ch)
{
    if(ch==',')
        return (true);
    return(false);        
}
bool isBlock(char ch) 
{
    if (ch=='['|| ch==']')
    {    
        return(true) ;
    }
    return (false);
}
    
bool validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' || 
        str[0] == '6' || str[0] == '7' || str[0] == '8' || 
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}
  
bool isKeyword(char* str)
{
    if (!strcmp(str, "move") || !strcmp(str, "to") ||
        !strcmp(str, "out") || !strcmp(str, "add") || 
        !strcmp(str, "loop") || 
         !strcmp(str, "times") || !strcmp(str, "out")
        || !strcmp(str, "sub") || !strcmp(str, "from")||!strcmp(str, "int"))

        return (true);
    return (false);
}
  
bool isInteger(char* str)
{
    int i;
    int len = strlen(str);
  
    if (len == 0 || len >100)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}
bool isStringConstant(char *str)
{
    int len=strlen(str);
    if (str[0]=='"'&&str[len-1]=='"')
        return (true);
    return(false);
}

int subString(char *source, int from, int n, char *target) 
{
    int i;
    char k;
    for (i = 0; i <= n; i++) {
        k=source[from + i];
        target[i]=k;
    }
    target[i] = '\0';
    return (0);
}
void parse(char* code,FILE *file)
{
    int lineCount = 0;
    char *line[1000];
    char *splitCode = strtok(code, "\n\r");
    while (splitCode != NULL) {
        line[lineCount++] = splitCode;
        splitCode = strtok(NULL, "\n\r");
    }
    int i;
    int wordCount = 0;
    char *word[1000];
    for (i = 0; i < lineCount; i++) {

        char *splitLine = strtok(line[i], " ");
        while (splitLine != NULL) {
            word[wordCount++] = splitLine;
            splitLine = strtok(NULL, " ");
        }
        if (wordCount == 0) 
        {
            break; 
        }
    }

    int j;
    for (j=0; j<wordCount;j++)
    {
        int left = 0, right = 0;
        
        int len = strlen(word[j]);
        char *str=word[j];            
        char *subStr=malloc(sizeof(word[j]));  
        while (right < len && left <= right) { 
            if(isDelimiter(str[right])==false)
            {  
                right++;  
            }    
            if (isDelimiter(str[right]) == true && left == right) {
                if (isOperator(str[right]) == true)
                    fprintf(file,"Operator\n", str[right]);
                else if (isEndOfLine(str[right]) == true)
                    fprintf(file,"EndOfline\n");
                else if(isSeperator(str[right]) == true)
                    fprintf(file,"Seperator\n");
                else if (isBlock(str[right]) == true)
                    if (str[right]=='[')
                    {                   
                        fprintf(file,"OpenBlock\n");
                        
                    }
                    else
                        fprintf(file,"CloseBlock\n");   
                else 
                {
                    fprintf(file,"UnknownCharacter\n");
                }    
                right++;
                left = right;
                }
            else if (isDelimiter(str[right]) == true && left != right
                        || (right == len && left != right)) 
            {
                subString(str, left, right-1,subStr);
        
                if (isKeyword(subStr) == true )
                    fprintf(file,"'%s'Keyword\n" ,subStr);
                else if (isStringConstant(subStr) == true)
                {
                    fprintf(file,"'%s'StringConstant\n" ,subStr);
                }    
                else if (isInteger(subStr) == true)
                    fprintf(file,"'%s'Integer\n" ,subStr);
        
                else if (validIdentifier(subStr) == true
                            && isDelimiter(str[right - 1]) == false)
                    fprintf(file,"'%s'Identifier\n" ,subStr);
        
                else if (validIdentifier(subStr) == false
                            && isDelimiter(str[right - 1]) == false)
                    fprintf(file,"'%s'InvalidIdentifier\n",subStr);
                left = right;
                
            }    
        }
    }
    
}

 
char a[100]; char b[100];
void isComment(char* str,FILE *file) {   
    bool trueComment = false;
    int j;
    int i;
    for (i = 0; i < strlen(str)-j; i++) {
        if (str[i] == '{') {
            for (j = i; j < strlen(str); j++) {
                if (str[j] == '}') {
                    subString(str, 0, i-1,a);
                    subString(str, j+1 , strlen(str)-j,b);
					strcat(a, b);
					strcpy(str, a);
                    trueComment = true;
                    isComment(str,file);
                    return;

                }

            }
            if (!trueComment) 
                fprintf(file,"Comment Line is not completed error.\n");
                exit(0);
            
        }
    }
}

int main()
{
    FILE *fp;
    FILE *file;
    long lSize;
    char *code;
    fp = fopen("myscript.ba.txt", "rb");
    file= fopen("myscript.lx.txt","w");
    if (!fp) 
        perror("myscript.ba.txt"), exit(1);
    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);
    code = calloc(1, lSize + 1);
    if (!code) 
        (fclose(fp), fputs("memory alloc fails", stderr), exit(1));
    if (1 != fread(code, lSize, 1, fp)) {
        (fclose(fp), free(code), fputs("entire read fails", stderr), exit(1));
    }
    isComment(code,file);
    parse(code,file);
    
}