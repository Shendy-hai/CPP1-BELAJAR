
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string judul;
    string penyanyi;
    Node* prev;
    Node* next;
};

Node* head = NULL;
Node* tail = NULL;

void tambah() {
    Node* baru = new Node;

    cin.ignore(1000, '\n');
    cout << "Judul lagu: ";
    getline(cin, baru->judul);

    cout << "Penyanyi  : ";
    getline(cin, baru->penyanyi);

    baru->prev = tail;
    baru->next = NULL;

    if (head == NULL)
        head = tail = baru;
    else {
        tail->next = baru;
        tail = baru;
    }

    cout << "Lagu ditambahkan.\n";
}

void tampilMaju() {
    Node* p = head;

    if (p == NULL) {
        cout << "Playlist kosong.\n";
        return;
    }

    cout << "\nPLAYLIST MAJU\n";
    while (p != NULL) {
        cout << p->judul << " - "
             << p->penyanyi << endl;
        p = p->next;
    }
}

void tampilMundur() {
    Node* p = tail;

    if (p == NULL) {
        cout << "Playlist kosong.\n";
        return;
    }

    cout << "\nPLAYLIST MUNDUR\n";
    while (p != NULL) {
        cout << p->judul << " - "
             << p->penyanyi << endl;
        p = p->prev;
    }
}

void hapusLagu() {
    string judul;
    cin.ignore(1000, '\n');

    cout << "Judul lagu yang dihapus: ";
    getline(cin, judul);

    Node* p = head;

    while (p != NULL && p->judul != judul)
        p = p->next;

    if (p == NULL) {
        cout << "Lagu tidak ditemukan.\n";
        return;
    }

    if (p->prev != NULL)
        p->prev->next = p->next;
    else
        head = p->next;

    if (p->next != NULL)
        p->next->prev = p->prev;
    else
        tail = p->prev;

    delete p;
    cout << "Lagu berhasil dihapus.\n";
}

int main() {
    int pilih;

    do {
        cout << "\n=== PLAYLIST MUSIK ===\n";
        cout << "1. Tambah lagu\n";
        cout << "2. Hapus lagu\n";
        cout << "3. Tampilkan maju\n";
        cout << "4. Tampilkan mundur\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambah(); break;
            case 2: hapusLagu(); break;
            case 3: tampilMaju(); break;
            case 4: tampilMundur(); break;
            case 0: break;
            default: cout << "Pilihan salah.\n";
        }
    } while (pilih != 0);

    while (head != NULL) {
        Node* p = head;
        head = head->next;
        delete p;
    }

    tail = NULL;
    return 0;
}
