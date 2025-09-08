#include <stdlib.h>
#include <stdint.h>

int main() {
    char* alphabet = calloc(26, sizeof(char));

    for(uint8_t i = 0; i < 26; i++) {
        *(alphabet + i) = 'A' + i;
    }
    *(alphabet + 26) = '\0'; //null-terminate the string?

    free(alphabet);
    return 0;
}
