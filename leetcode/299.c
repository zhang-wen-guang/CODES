#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* getHint(char* secret, char* guess) {
    int len = strlen(secret);
    int secret_set[10] = {0};
    int guess_set[10] = {0};
    int i, a = 0, b = 0;
    char *res;

    res = malloc(10 * sizeof(char));

    for (i = 0; i < len; ++i) {
        if (secret[i] == guess[i]) {
            a++;
            continue;
        }
        guess_set[guess[i] - '0']++;
        secret_set[secret[i] - '0']++;
    }
    for (i = 0; i < 10; ++i) {
        if (secret_set[i] && guess_set[i]) 
            b += (secret_set[i] > guess_set[i] ? guess_set[i] : secret_set[i]);
    }
    sprintf(res, "%dA%dB", a, b);
    return res;
}

int main()
{
    char secret[100];
    char guess[100];
    char *res;

    scanf("%s", secret);
    scanf("%s", guess);
    res = getHint(secret, guess);
    printf("%s\n", res);
    return 0;
}
