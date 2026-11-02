
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Check C keywords
int isKeyword(char s[]) {
    char *kw[] = {
        "int", "float", "char", "double", "if", "else",
        "while", "for", "do", "return", "void", "break",
        "continue", "switch", "case", "default", "long",
        "short", "signed", "unsigned", "const", "static",
        "struct", "sizeof", "enum", "union", "typedef",
        "extern", "auto", "register", "volatile", "goto"
    };

    for (int i = 0; i < 32; i++) {
        if (strcmp(s, kw[i]) == 0)
            return 1;
    }

    return 0;
}

// Display token type and lexeme
void display(char type[], char word[]) {
    printf("%s\t%s\n", type, word);
}

int main() {
    FILE *fp = stdin;

    int ch, next, i;
    char word[100];

    while ((ch = fgetc(fp)) != EOF) {

        // Ignore whitespace
        if (isspace(ch))
            continue;

        // Keywords and Identifiers
        if (isalpha(ch) || ch == '_') {
            i = 0;
            word[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_')) {
                if (i < 99)
                    word[i++] = ch;
            }

            word[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            if (isKeyword(word))
                display("Keyword", word);
            else
                display("Identifier", word);
        }

        // Numeric Constants
        else if (isdigit(ch)) {
            i = 0;
            word[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit(ch) || ch == '.')) {
                if (i < 99)
                    word[i++] = ch;
            }

            word[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            display("Constant", word);
        }

        // String and Character Constants
        else if (ch == '"' || ch == '\'') {
            int quote = ch;
            i = 0;
            word[i++] = ch;

            while ((ch = fgetc(fp)) != EOF) {
                if (i < 98)
                    word[i++] = ch;

                if (ch == '\\') {
                    ch = fgetc(fp);

                    if (ch == EOF)
                        break;

                    if (i < 98)
                        word[i++] = ch;
                }
                else if (ch == quote) {
                    break;
                }
            }

            word[i] = '\0';

            if (quote == '"')
                display("String Literal", word);
            else
                display("Constant", word);
        }

        // Comments and Division Operators
        else if (ch == '/') {
            next = fgetc(fp);

            // Single-line comment
            if (next == '/') {
                while ((ch = fgetc(fp)) != EOF && ch != '\n');
            }

            // Multi-line comment
            else if (next == '*') {
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '*' && (next = fgetc(fp)) == '/')
                        break;
                    else if (ch == '*' && next != EOF)
                        ungetc(next, fp);
                }
            }

            // Division or division assignment
            else {
                if (next == '=') {
                    display("Operator", "/=");
                }
                else {
                    if (next != EOF)
                        ungetc(next, fp);

                    display("Operator", "/");
                }
            }
        }

        // Other Operators
        else if (strchr("+-*=<>!%&|^~", ch)) {
            word[0] = ch;
            word[1] = '\0';

            next = fgetc(fp);

            if (next == '=' ||
                (next == ch && (ch == '+' || ch == '-' ||
                                ch == '&' || ch == '|')) ||
                ((ch == '<' || ch == '>') && next == ch) ||
                (ch == '-' && next == '>')) {

                word[1] = next;
                word[2] = '\0';

                // Three-character operators
                if ((ch == '<' || ch == '>') && next == ch) {
                    int third = fgetc(fp);

                    if (third == '=') {
                        word[2] = third;
                        word[3] = '\0';
                    }
                    else if (third != EOF) {
                        ungetc(third, fp);
                    }
                }
            }
            else if (next != EOF) {
                ungetc(next, fp);
            }

            display("Operator", word);
        }

        // Special Symbols
        else if (strchr("(){}[];,.:?#", ch)) {
            word[0] = ch;
            word[1] = '\0';

            display("Special Symbol", word);
        }

        // Unknown Characters
        else {
            word[0] = ch;
            word[1] = '\0';

            display("Unknown Token", word);
        }
    }

    return 0;
}
