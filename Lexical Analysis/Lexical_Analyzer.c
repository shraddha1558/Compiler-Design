#include <stdio.h>
#include <ctype.h>

void lexicalAnalyzer(const char *input) {
    int i = 0, line = 1;
    char ch;

    printf("Starting Lexical Analysis...\n\n");

    while ((ch = input[i]) != '\0') {
        if (ch == '\n') {
            line++;
            i++;
            continue;
        }
        else if (isspace(ch)) {
            i++;
            continue;
        }
        else if (isalpha(ch) || ch == '_') {
            // Identifier or Keyword
            printf("Line %d: Identifier: ", line);
            while (isalnum(input[i]) || input[i] == '_') {
                printf("%c", input[i]);
                i++;
            }
            printf("\n");
        }
        else if (isdigit(ch)) {
            // Number
            printf("Line %d: Number: ", line);
            while (isdigit(input[i])) {
                printf("%c", input[i]);
                i++;
            }
            printf("\n");
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Operator
            printf("Line %d: Operator: %c\n", line, ch);
            i++;
        }
        else if (ch == '=' || ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '.' || ch == '@') {
            // Special symbols
            printf("Line %d: Special Symbol: %c\n", line, ch);
            i++;
        }
        else {
            // Invalid character
            printf("Line %d: ERROR: Invalid Character '%c'\n", line, ch);
            i++;
        }
    }
}

int main() {
    const char *code = "Hii My Name is Shraddha Sahu.;\n My Email Id is shraddha.2201134cs@iiitbh.ac.in .;\n $invalid";
    lexicalAnalyzer(code);
    return 0;
}
