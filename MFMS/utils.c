#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

/* Read one line safely, strip newline. Exits cleanly if input ends (EOF). */
void readLine(const char *prompt, char *buf, int size)
{
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        printf("\nInput ended. Exiting.\n");
        exit(0);
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        /* line was longer than buffer: discard the rest */
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

/* Keep asking until the user types something that is not blank. */
void readNonEmpty(const char *prompt, char *buf, int size)
{
    while (1) {
        readLine(prompt, buf, size);

        /* trim leading spaces */
        char *start = buf;
        while (*start != '\0' && isspace((unsigned char)*start))
            start++;
        if (start != buf)
            memmove(buf, start, strlen(start) + 1);

        /* trim trailing spaces */
        size_t len = strlen(buf);
        while (len > 0 && isspace((unsigned char)buf[len - 1]))
            buf[--len] = '\0';

        if (strlen(buf) > 0)
            return;
        printf("  Error: this field cannot be empty.\n");
    }
}

/* Read an integer between min and max (inclusive). */
int readInt(const char *prompt, int min, int max)
{
    char line[64];
    char *end;
    long value;

    while (1) {
        readLine(prompt, line, sizeof(line));
        value = strtol(line, &end, 10);
        if (end == line || *end != '\0') {
            printf("  Error: please enter a whole number.\n");
        } else if (value < min || value > max) {
            printf("  Error: value must be between %d and %d.\n", min, max);
        } else {
            return (int)value;
        }
    }
}

/* Read a decimal number that is at least min. */
double readDouble(const char *prompt, double min)
{
    char line[64];
    char *end;
    double value;

    while (1) {
        readLine(prompt, line, sizeof(line));
        value = strtod(line, &end);
        if (end == line || *end != '\0') {
            printf("  Error: please enter a valid number.\n");
        } else if (value < min) {
            printf("  Error: value cannot be less than %.2f.\n", min);
        } else {
            return value;
        }
    }
}

/* Case-insensitive substring search (used by all search functions). */
int containsIgnoreCase(const char *text, const char *pattern)
{
    char a[256], b[256];
    size_t i;

    strncpy(a, text, sizeof(a) - 1);
    a[sizeof(a) - 1] = '\0';
    strncpy(b, pattern, sizeof(b) - 1);
    b[sizeof(b) - 1] = '\0';

    for (i = 0; a[i] != '\0'; i++)
        a[i] = (char)tolower((unsigned char)a[i]);
    for (i = 0; b[i] != '\0'; i++)
        b[i] = (char)tolower((unsigned char)b[i]);

    return strstr(a, b) != NULL;
}

/* Very simple email check: something@something.something */
int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    const char *dot;

    if (at == NULL || at == email)
        return 0;
    dot = strrchr(at, '.');
    if (dot == NULL || dot == at + 1 || *(dot + 1) == '\0')
        return 0;
    if (strchr(email, ' ') != NULL)
        return 0;
    return 1;
}

/* Phone: 7 to 15 characters, digits with optional leading '+'. */
int isValidPhone(const char *phone)
{
    size_t i, len = strlen(phone);

    if (len < 7 || len > 15)
        return 0;
    for (i = 0; i < len; i++) {
        if (i == 0 && phone[i] == '+')
            continue;
        if (!isdigit((unsigned char)phone[i]))
            return 0;
    }
    return 1;
}

void printLine(char c, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(c);
    putchar('\n');
}

void pauseScreen(void)
{
    char tmp[8];
    readLine("\nPress ENTER to continue...", tmp, sizeof(tmp));
}
