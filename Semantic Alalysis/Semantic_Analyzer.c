#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Data structure to store variable information
typedef struct {
    char name[MAX];
    char type[MAX];  // int, float, char, etc.
} Variable;

// Data structure to store function information
typedef struct {
    char name[MAX];
    char return_type[MAX];  // int, float, etc.
} Function;

Variable var_table[MAX];
Function func_table[MAX];

int var_count = 0, func_count = 0;

// Function to add variable to symbol table
void addVariable(char* name, char* type) {
    strcpy(var_table[var_count].name, name);
    strcpy(var_table[var_count].type, type);
    var_count++;
}

// Function to add function to symbol table
void addFunction(char* name, char* return_type) {
    strcpy(func_table[func_count].name, name);
    strcpy(func_table[func_count].return_type, return_type);
    func_count++;
}

// Function to check if variable is declared
int isVariableDeclared(char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0) {
            return 1;  // Variable is declared
        }
    }
    return 0;  // Variable is not declared
}

// Function to check if function is declared
int isFunctionDeclared(char* name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(func_table[i].name, name) == 0) {
            return 1;  // Function is declared
        }
    }
    return 0;  // Function is not declared
}

// Function to check variable type compatibility
int checkTypeCompatibility(char* var_name, char* expected_type) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, var_name) == 0) {
            if (strcmp(var_table[i].type, expected_type) == 0) {
                return 1;  // Types are compatible
            }
            return 0;  // Types are incompatible
        }
    }
    return 0;  // Variable not declared
}

// Function to perform semantic analysis
void semanticAnalyzer(char* expr) {
    char word[MAX], type[MAX];
    int i = 0, j = 0;

    while (expr[i] != '\0') {
        // Skip white spaces
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // Parse variable declarations (example: int a;)
        if (expr[i] == 'i' && expr[i+1] == 'n' && expr[i+2] == 't') {
            i += 3;
            while (isalnum(expr[i]) || expr[i] == '_') {  // Allow underscore in variable names
                word[j++] = expr[i++];
            }
            word[j] = '\0';
            addVariable(word, "int");
            printf("Declared variable: %s of type int\n", word);
            j = 0;
            continue;
        }

        // Parse function declarations (example: int func();)
        if ((expr[i] == 'i' && expr[i+1] == 'n' && expr[i+2] == 't') || 
            (expr[i] == 'v' && expr[i+1] == 'o' && expr[i+2] == 'i')) {  // Start with int or void
            i += 3;
            while (isalnum(expr[i]) || expr[i] == '_') {  // Allow underscore in function names
                word[j++] = expr[i++];
            }
            word[j] = '\0';
            if (expr[i] == '(' && expr[i+1] == ')') {
                if (strcmp(word, "main") == 0) {
                    addFunction(word, "int");
                    printf("Declared function: %s with return type int\n", word);
                } else {
                    addFunction(word, "int");
                    printf("Declared function: %s with return type int\n", word);
                }
                j = 0;
                continue;
            }
        }

        // Parse variable usage (example: a = 5;)
        if (isalnum(expr[i]) || expr[i] == '_') {  // Variable names can include underscores
            while (isalnum(expr[i]) || expr[i] == '_') {
                word[j++] = expr[i++];
            }
            word[j] = '\0';

            // Check if variable is declared
            if (!isVariableDeclared(word)) {
                printf("Error: Undeclared variable %s\n", word);
            } else {
                // Check type compatibility if needed
                // Example: check if the assignment is correct for an 'int'
                if (expr[i] == '=') {
                    if (!checkTypeCompatibility(word, "int")) {
                        printf("Error: Type mismatch for variable %s\n", word);
                    }
                }
            }
            j = 0;
            continue;
        }

        i++;
    }

    // Check for function calls
    if (!isFunctionDeclared("main")) {
        printf("Error: Function 'main' is undeclared\n");
    }
}

int main() {
    char expression[MAX];
    char full_expr[MAX * 10] = "";  // Store the full expression
    int running = 1;

    printf("Enter code line by line. Type 'execute' when ready to analyze.\n");

    // Loop to accept multiple lines of input
    while (running) {
        printf("Input: ");
        fgets(expression, sizeof(expression), stdin);

        // Remove newline character
        expression[strcspn(expression, "\n")] = '\0';

        // If user types "execute", perform semantic analysis
        if (strcmp(expression, "execute") == 0) {
            printf("Executing semantic analysis...\n");
            semanticAnalyzer(full_expr);
            running = 0;  // Stop loop after execution
        } else {
            // Append the line to full expression
            strcat(full_expr, expression);
            strcat(full_expr, " ");  // Add a space to separate lines
        }
    }

    return 0;
}
