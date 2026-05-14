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
                if (c == 'a') { state = 0; break; }
                if (c == 'b') { state = 1; break; }
                if (c == 'c') { state = 2; break; }
                state = -1;
                break;
            case 1:
                if (c == 'a') { state = 3; break; }
                if (c == 'b') { state = 2; break; }
                if (c == 'c') { state = 0; break; }
                state = -1;
                break;
            case 2:
                if (c == 'a') { state = 2; break; }
                if (c == 'b') { state = 2; break; }
                if (c == 'c') { state = 2; break; }
                state = -1;
                break;
            case 3:
                if (c == 'a') { state = 2; break; }
                if (c == 'b') { state = 4; break; }
                if (c == 'c') { state = 4; break; }
                state = -1;
                break;
            case 4:
                if (c == 'a') { state = 5; break; }
                if (c == 'b') { state = 2; break; }
                if (c == 'c') { state = 2; break; }
                state = -1;
                break;
            case 5:
                if (c == 'a') { state = 2; break; }
                if (c == 'b') { state = 2; break; }
                if (c == 'c') { state = 2; break; }
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

    if (state == 5 || 0) {
        printf("%s appartient au langage rationnel defini par e.\n", word);
    } else {
        printf("%s n'appartient pas au langage rationnel defini par e.\n", word);
    }

    return 0;
}
