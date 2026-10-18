#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    int tabel[8][8];

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            tabel[x][y] = rand() % 100 + 1;
        }
    }

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            cout << tabel[x][y] << "\t";
        }
        cout << "\n";
    }

    return 0;
}
