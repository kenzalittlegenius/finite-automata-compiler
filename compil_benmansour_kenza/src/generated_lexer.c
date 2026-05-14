#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int state = 0;
    int i;
    char *word;

    if (argc != 2) {
        printf("Usage: %s <word>\n", argv[0]);
        return 1;
    }

    word = argv[1];

    for (i = 0; word[i] != '\0'; i++) {
        char c = word[i];

        switch (state) {
            case 0:
                if (c == 'a') { state = 1; break; }
                if (c == 'b') { state = 0; break; }
                state = -1;
                break;
            case 1:
                if (c == 'a') { state = 1; break; }
                if (c == 'b') { state = 2; break; }
                state = -1;
                break;
            case 2:
                if (c == 'a') { state = 1; break; }
                if (c == 'b') { state = 0; break; }
                state = -1;
                break;
            default:
                state = -1;
                break;
        }

        if (state == -1) {
            break;
        }
    }

    if (state == 2 || 0) {
        printf("%s appartient au langage rationnel defini par e.\n", word);
    } else {
        printf("%s n'appartient pas au langage rationnel defini par e.\n", word);
    }

    return 0;
}
