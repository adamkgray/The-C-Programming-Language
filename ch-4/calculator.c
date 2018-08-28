/* Reverse Polish Calculator */

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

/* Reverse Polish Calculator */
int main() {
    int type;
    double op1, op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            op2 = pop();
            op1 = pop();
            push(op1 + op2);
            break;
        case '*':
            op2 = pop();
            op1 = pop();
            push(op1 * op2);
            break;
        case '-':
            op2 = pop();
            op1 = pop();
            push(op1 - op2);
            break;
        case '/':
            op2 = pop();
            op1 = pop();
            if (op2 != 0.0) {
                push(op1 / op2);
            } else {
                printf("error: zero divisor\n");
            }
            break;
        case '%':
            op2 = pop();
            op1 = pop();
            if (op2 != 0.0) {
                push((int)op1 % (int)op2);
            } else {
                printf("error: zero divisor\n");
            }
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

/* push a value onto the queue */
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

/* Pop a value from the queue */
double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* Get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    /* Read through whitespace */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    /* Return any character that is not a number, negative sign or decimal point */
    if (!isdigit(c) && c != '.') {
        return c;
    }

    i = 0;
    /* collect integer part */
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    /* collect part after decimal */
    if (c == '.') {
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    s[i] = '\0';

    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

/* Get a (possibly pushed back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push a character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
