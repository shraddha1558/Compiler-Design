#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack for parentheses checking
char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
}

char pop() {
    if (top >= 0)
        return stack[top--];
    else
        return '\0';
}

int isMatchingPair(char opening, char closing) {
    return ((opening == '(' && closing == ')') ||
            (opening == '{' && closing == '}') ||
            (opening == '[' && closing == ']'));
}

// Function to check if the statement ends with a semicolon
int checkSemicolon(char* expr) {
    int len = strlen(expr);
    // Check if the last non-whitespace character is a semicolon
    while (len > 0 && isspace(expr[len - 1])) {
        len--;
    }
    return (expr[len - 1] == ';');
}

// Function to check if if-else syntax is correct
int checkIfElse(char* expr) {
    int i;
    int if_count = 0, else_count = 0;
    
    for (i = 0; expr[i] != '\0'; i++) {
        if (strncmp(&expr[i], "if", 2) == 0) {
            if_count++;
        } else if (strncmp(&expr[i], "else", 4) == 0) {
            else_count++;
        }
    }

    // Simple check: the number of 'if' should match 'else' 
    return (if_count == else_count);
}

void syntaxAnalyzer(char* expr) {
    int i, flag = 0;
    char popped;

    for (i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[') {
            push(expr[i]);
        } else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']') {
            popped = pop();
            if (!isMatchingPair(popped, expr[i])) {
                flag = 1;
                break;
            }
        }
    }

    // Check for mismatched parentheses
    if (top != -1 || flag) {
        printf("Syntax Error: Mismatched symbols\n");
        return;
    }

    // Check for missing semicolon
    if (!checkSemicolon(expr)) {
        printf("Syntax Error: Missing semicolon at the end of the statement\n");
    } else {
        printf("Syntax Correct: Semicolon is present\n");
    }

    // Check if-else syntax
    if (!checkIfElse(expr)) {
        printf("Syntax Error: Mismatched if-else blocks\n");
    } else {
        printf("Syntax Correct: if-else syntax is valid\n");
    }

    printf("Syntax Analysis Complete.\n");
}

int main() {
    char expression[MAX];

    printf("Enter the expression: ");
    fgets(expression, sizeof(expression), stdin);

    // Remove newline character
    expression[strcspn(expression, "\n")] = '\0';

    syntaxAnalyzer(expression);

    return 0;
}
