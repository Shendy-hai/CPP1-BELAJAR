#include <iostream>
using namespace std;

int main() {
    int nilai[5] = {10, 20, 30, 40, 50};

    cout << "Isi Array:" << endl;

    for (int i = 0; i < 5; i++) {
        cout << "Nilai ke-" << i + 1 << " = " << nilai[i] << endl;
    }

    return 0;
}