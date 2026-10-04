#ifndef UTILS_H
#define UTILS_H

/* Shared input/validation helpers used by every module. */

#define MAX_NAME 50
#define MAX_TEXT 30

void readLine(const char *prompt, char *buf, int size);
void readNonEmpty(const char *prompt, char *buf, int size);
int readInt(const char *prompt, int min, int max);
double readDouble(const char *prompt, double min);
int containsIgnoreCase(const char *text, const char *pattern);
int isValidEmail(const char *email);
int isValidPhone(const char *phone);
void printLine(char c, int n);
void pauseScreen(void);

#endif
