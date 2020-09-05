#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

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
    // disable Ctrl-S and Ctrl-Q. Ctrl-M
    raw.c_iflag &= ~(IXON | IXON);
    // disable output processing
    raw.c_oflag &= ~(OPOST);
    // disable echo, canocical mode, and ctrl+c,ctrl+z, disable ctrl+o
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);    
    // save attrs
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    // enable raw mode
    enableRawMode();
    // store characters here
    char c;
    // read stdin until "q"
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }
    }
    return 0;
}