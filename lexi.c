#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

// struct for original terminal attrs
struct termios orig_termios;


void disableRawMode() {
    // set old attrs
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode() {
    // get attrs
    tcgetattr(STDIN_FILENO, &orig_termios);
    // set disableRawMode at exit
    atexit(disableRawMode);
    // create a copy of the attrs
    struct termios raw = orig_termios;
    // disable echo and canocical mode
    raw.c_lflag &= ~(ECHO | ICANON);    
    // save attrs
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    // enable raw mode
    enableRawMode();
    // store characters here
    char c;
    // read stdin
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');    // exit cleanly
    return 0;
}