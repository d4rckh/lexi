#include <unistd.h>

int main() {
    // store characters here
    char c;
    // read stdin
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');    // exit cleanly
    return 0;
}