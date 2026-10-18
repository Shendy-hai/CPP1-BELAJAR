#include <iostream>
#include <string>
using namespace std;

struct Node {
    int nomor;
    string nama;
    Node* next;
};

Node* head = NULL;
Node* tail = NULL;

void tambah() {
    Node* baru = new Node;

    cout << "Nomor antrean : ";
    cin >> baru->nomor;
    cin.ignore(1000, '\n');

    cout << "Nama mahasiswa: ";
    getline(cin, baru->nama);

    baru->next = NULL;

    if (head == NULL) {
        head = tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }

    cout << "Antrean berhasil ditambahkan.\n";
}

void layani() {
    if (head == NULL) {
        cout << "Antrean kosong.\n";
        return;
    }

    Node* hapus = head;

    cout << "Melayani: " << hapus->nama
         << " (No. " << hapus->nomor << ")\n";

    head = head->next;

    if (head == NULL)
        tail = NULL;

    delete hapus;
}

void tampilkan() {
    Node* bantu = head;

    if (bantu == NULL) {
        cout << "Antrean kosong.\n";
        return;
    }

    cout << "\nDAFTAR ANTREAN\n";

    while (bantu != NULL) {
        cout << bantu->nomor << " - "
             << bantu->nama << endl;
        bantu = bantu->next;
    }
}

void cari() {
    int nomor;
    cout << "Nomor yang dicari: ";
    cin >> nomor;

    Node* bantu = head;

    while (bantu != NULL) {
        if (bantu->nomor == nomor) {
            cout << "Ditemukan: "
                 << bantu->nama << endl;
            return;
        }
        bantu = bantu->next;
    }

    cout << "Nomor tidak ditemukan.\n";
}

int main() {
    int pilih;

    do {
        cout << "\n=== ANTREAN AKADEMIK ===\n";
        cout << "1. Tambah antrean\n";
        cout << "2. Layani antrean\n";
        cout << "3. Tampilkan antrean\n";
        cout << "4. Cari mahasiswa\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambah(); break;
            case 2: layani(); break;
            case 3: tampilkan(); break;
            case 4: cari(); break;
            case 0: cout << "Program selesai.\n"; break;
            default: cout << "Pilihan salah.\n";
        }
    } while (pilih != 0);

    while (head != NULL)
        layani();

    return 0;
}
