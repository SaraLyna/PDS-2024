#include <unistd.h>

int main(void) {
  execl("/usr/bin/ls","ls",NULL);

    return 0;
}
