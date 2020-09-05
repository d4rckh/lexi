#include <unistd.h>

int main() {
    // store characters here
    char c;
    // read stdin
    while (read(STDIN_FILENO, &c, 1) == 1);
    // exit cleanly
    return 0;
}