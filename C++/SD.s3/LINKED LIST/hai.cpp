
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string nama;
    Node* next;
};

Node* head = NULL;
Node* sekarang = NULL;

void tambah() { 
    Node* baru = new Node;

    cin.ignore(1000, '\n');
    cout << "Nama mahasiswa: ";
    getline(cin, baru->nama);

    if (head == NULL) {
        head = baru;
        baru->next = head;
        sekarang = head;
    } else {
        Node* p = head;

        while (p->next != head)
            p = p->next;

        p->next = baru;
        baru->next = head;
    }

    cout << "Peserta ditambahkan.\n";
}

void tampilkan() {
    if (head == NULL) {
        cout << "Belum ada peserta.\n";
        return;
    }

    Node* p = head;
    int nomor = 1;

    cout << "\nDAFTAR PESERTA\n";

    do {
        cout << nomor++ << ". " << p->nama;
        if (p == sekarang)
            cout << " <-- GILIRAN SEKARANG";
        cout << endl;

        p = p->next;
    } while (p != head);
}

void giliranBerikutnya() {
    if (sekarang == NULL) {
        cout << "Belum ada peserta.\n";
        return;
    }

    sekarang = sekarang->next;

    cout << "Giliran berikutnya: "
         << sekarang->nama << endl;
}

void hapusPeserta() {
    if (head == NULL) {
        cout << "Belum ada peserta.\n";
        return;
    }

    string nama;
    cin.ignore(1000, '\n');
    cout << "Nama peserta yang dihapus: ";
    getline(cin, nama);

    Node* p = head;
    Node* prev = head;

    while (prev->next != head)
        prev = prev->next;

    do {
        if (p->nama == nama) {
            if (p->next == p) {
                head = NULL;
                sekarang = NULL;
            } else {
                prev->next = p->next;

                if (p == head)
                    head = p->next;

                if (p == sekarang)
                    sekarang = p->next;
            }

            delete p;
            cout << "Peserta dihapus.\n";
            return;
        }

        prev = p;
        p = p->next;
    } while (p != head);

    cout << "Peserta tidak ditemukan.\n";
}

void hitungPeserta() {
    if (head == NULL) {
        cout << "Jumlah peserta: 0 (Belum ada peserta).\n";
        return;
    }

    Node* p = head;
    int jumlah = 0;

    do {
        jumlah++;
        p = p->next;
    } while (p != head);

    cout << "Jumlah mahasiswa dalam daftar: " << jumlah << " orang.\n";
}

int main() {
    int pilih;

    do {
        cout << "\n=== GILIRAN PRESENTASI ===\n";
        cout << "1. Tambah peserta\n";
        cout << "2. Giliran berikutnya\n";
        cout << "3. Tampilkan peserta\n";
        cout << "4. Hapus peserta\n";
        cout << "5. Hitung jumlah peserta\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambah(); break;
            case 2: giliranBerikutnya(); break;
            case 3: tampilkan(); break;
            case 4: hapusPeserta(); break;
            case 5: hitungPeserta(); break;
            case 0: break;
            default: cout << "Pilihan salah.\n";
        }
    } while (pilih != 0);

    while (head != NULL) {
        if (head->next == head) {
            delete head;
            head = NULL;
        } else {
            Node* p = head;
            while (p->next != head)
                p = p->next;

            p->next = head->next;
            Node* hapus = head;
            head = head->next;
            delete hapus;
        }
    }

    sekarang = NULL;
    return 0;
}
