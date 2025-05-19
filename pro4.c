#include <stdio.h>
#include <string.h>

int modInv(int a) {
    for (int i = 1; i < 26; i++)
        if ((a * i) % 26 == 1) return i;
    return -1;
}

void getKey(int k[3][3], char *s) {
    for (int i = 0; i < 9; i++) k[i/3][i%3] = s[i] - 'A';
}

void mult(int k[3][3], int m[3], int r[3]) {
    for (int i = 0; i < 3; i++) {
        r[i] = 0;
        for (int j = 0; j < 3; j++) r[i] += k[i][j] * m[j];
        r[i] = (r[i] % 26 + 26) % 26;
    }
}

void invKey(int k[3][3], int inv[3][3]) {
    int a = k[0][0], b = k[0][1], c = k[0][2];
    int d = k[1][0], e = k[1][1], f = k[1][2];
    int g = k[2][0], h = k[2][1], i = k[2][2];

    int det = a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
    det = (det % 26 + 26) % 26;
    int invDet = modInv(det);
    if (invDet == -1) { printf("No inverse.\n"); return; }

    inv[0][0] = (e*i - f*h) * invDet;
    inv[0][1] = (c*h - b*i) * invDet;
    inv[0][2] = (b*f - c*e) * invDet;
    inv[1][0] = (f*g - d*i) * invDet;
    inv[1][1] = (a*i - c*g) * invDet;
    inv[1][2] = (c*d - a*f) * invDet;
    inv[2][0] = (d*h - e*g) * invDet;
    inv[2][1] = (b*g - a*h) * invDet;
    inv[2][2] = (a*e - b*d) * invDet;

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            inv[r][c] = (inv[r][c] % 26 + 26) % 26;
}

int main() {
    char msg[4], keyStr[10]; int k[3][3], ik[3][3], vec[3], res[3];
    printf("Enter 3-letter msg (A-Z): "); scanf("%s", msg);
    printf("Enter 9-letter key: "); scanf("%s", keyStr);

    getKey(k, keyStr);
    for (int i = 0; i < 3; i++) vec[i] = msg[i] - 'A';

    mult(k, vec, res);
    printf("Encrypted: %c%c%c\n", res[0]+'A', res[1]+'A', res[2]+'A');

    invKey(k, ik);
    mult(ik, res, vec);
    printf("Decrypted: %c%c%c\n", vec[0]+'A', vec[1]+'A', vec[2]+'A');

    return 0;
}

