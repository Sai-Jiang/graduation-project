#include <stdio.h>

#include "UDPRawClient.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "./UDPRawClient <sender ip> <receiver ip>\n");
        return -1;
    } else {
        UDPRawClient client(argv[1], argv[2]);
        client.run();
    }
    return 0;
}
