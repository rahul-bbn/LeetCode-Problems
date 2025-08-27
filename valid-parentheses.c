#include <stdio.h>
#include <stdbool.h>

#define MAX 10000

int isMaching(char open,char close)
{
    return (open=='(' && close==')') || (open=='{' && close=='}') || (open=='[' && close==']');
}
bool isValid(char* s) {
    char stack[MAX];
    int top =-1;

    for(int i=0;s[i]!='\0';i++){
        char ch=s[i];
        if(ch=='(' || ch=='{' || ch=='['){
            stack[++top]=ch;
        }
        else{
            if(top==-1) return false;
            char last = stack[top--];

            if(!isMaching(last,ch)){
                return false;
            }
        }
    }
    return (top==-1);
}