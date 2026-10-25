
#include <iostream>
#include <string>
using namespace std;

struct Node {
    int kode;
    string nama;
    Node* prev;
    Node* next;
};

Node* head = NULL;
Node* sekarang = NULL;

void tambah() {
    Node* baru = new Node;

    cout << "Kode menu: ";
    cin >> baru->kode;
    cin.ignore(1000, '\n');

    cout << "Nama menu: ";
    getline(cin, baru->nama);

    if (head == NULL) {
        head = baru;
        baru->next = baru;
        baru->prev = baru;
    } else {
        Node* tail = head->prev;

        baru->next = head;
        baru->prev = tail;

        tail->next = baru;
        head->prev = baru;
    }

    if (sekarang == NULL)
        sekarang = head;

    cout << "Menu ditambahkan.\n";
}

void tampilMaju() {
    if (head == NULL) {
        cout << "Menu kosong.\n";
        return;
    }

    Node* p = head;
    cout << "\nURUTAN MENU MAJU\n";

    do {
        cout << p->kode << " - " << p->nama << endl;
        p = p->next;
    } while (p != head);
}

void tampilMundur() {
    if (head == NULL) {
        cout << "Menu kosong.\n";
        return;
    }

    Node* p = head->prev;
    Node* terakhir = p;

    cout << "\nURUTAN MENU MUNDUR\n";

    do {
        cout << p->kode << " - " << p->nama << endl;
        p = p->prev;
    } while (p != terakhir);
}

void navigasi() {
    if (sekarang == NULL) {
        cout << "Menu kosong.\n";
        return;
    }

    char arah;
    cout << "N = Berikutnya, P = Sebelumnya: ";
    cin >> arah;

    if (arah == 'N' || arah == 'n')
        sekarang = sekarang->next;
    else if (arah == 'P' || arah == 'p')
        sekarang = sekarang->prev;
    else {
        cout << "Arah tidak valid.\n";
        return;
    }

    cout << "Menu aktif: " << sekarang->nama << endl;
}

void hapusMenu() {
    if (head == NULL) {
        cout << "Menu kosong.\n";
        return;
    }

    int kode;
    cout << "Kode menu yang dihapus: ";
    cin >> kode;

    Node* p = head;

    do {
        if (p->kode == kode) {
            if (p->next == p) {
                head = NULL;
                sekarang = NULL;
            } else {
                p->prev->next = p->next;
                p->next->prev = p->prev;

                if (p == head)
                    head = p->next;

                if (p == sekarang)
                    sekarang = p->next;
            }

            delete p;
            cout << "Menu dihapus.\n";
            return;
        }

        p = p->next;
    } while (p != head);

    cout << "Kode menu tidak ditemukan.\n";
}

int main() {
    int pilih;

    do {
        cout << "\n=== NAVIGASI MENU ===\n";
        cout << "1. Tambah menu\n";
        cout << "2. Hapus menu\n";
        cout << "3. Tampilkan maju\n";
        cout << "4. Tampilkan mundur\n";
        cout << "5. Navigasi menu\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambah(); break;
            case 2: hapusMenu(); break;
            case 3: tampilMaju(); break;
            case 4: tampilMundur(); break;
            case 5: navigasi(); break;
            case 0: break;
            default: cout << "Pilihan salah.\n";
        }
    } while (pilih != 0);

    while (head != NULL) {
        Node* p = head;

        if (head->next == head) {
            head = NULL;
        } else {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
        }

        delete p;
    }

    sekarang = NULL;
    return 0;
}
