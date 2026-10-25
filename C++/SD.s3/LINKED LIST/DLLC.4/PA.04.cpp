
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
    int kode;
    cout << "Kode menu: ";
    cin >> kode;

    // Validasi agar kode menu tidak duplikat
    if (head != NULL) {
        Node* p = head;
        do {
            if (p->kode == kode) {
                cout << "Kode menu sudah digunakan!\n";
                return;
            }
            p = p->next;
        } while (p != head);
    }

    Node* baru = new Node;
    baru->kode = kode;
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

//modifikasi fungsi tampilkan untuk menampilkan menu maju dan mundur
void tampilMaju() {
    if (head == NULL) {
        cout << "Menu kosong.\n";
        return;
    }

    Node* p = head;
    cout << "\nURUTAN MENU MAJU\n";

    do {
        cout << p->kode << " - " << p->nama;
        if (p == sekarang)
            cout << " <-- MENU AKTIF";
        cout << endl;

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
        cout << p->kode << " - " << p->nama;
        if (p == sekarang)
            cout << " <-- MENU AKTIF";
        cout << endl;

        p = p->prev;
    } while (p != terakhir);
}

//modifikasi fungsi navigasi untuk menavigasi menu maju dan mundur
void navigasi() {
    if (sekarang == NULL) {
        cout << "Menu kosong.\n";
        return;
    }

    char arah;

    do {
        cout << "\nN = Berikutnya, P = Sebelumnya, 0 = Selesai: ";
        cin >> arah;

        if (arah == 'N' || arah == 'n') {
            sekarang = sekarang->next;
            cout << "Menu aktif: " << sekarang->nama << endl;
        } else if (arah == 'P' || arah == 'p') {
            sekarang = sekarang->prev;
            cout << "Menu aktif: " << sekarang->nama << endl;
        } else if (arah != '0') {
            cout << "Arah tidak valid.\n";
        }
    } while (arah != '0');
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