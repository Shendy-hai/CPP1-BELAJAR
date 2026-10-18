#include <iostream>
using namespace std;

int main() {
    int tabel[3][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15}
    };

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 5; y++) {
            cout << tabel[x][y] << " ";
        }
        cout << endl;
    }

    return 0;
}