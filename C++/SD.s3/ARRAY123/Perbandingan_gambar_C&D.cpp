
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
using namespace std;

struct RGB {
    unsigned char r, g, b;
};

struct BMP {
    int width, height;
    vector<vector<RGB>> pixel;
};

uint16_t read16(const unsigned char* h, int pos) {
    return h[pos] | (uint16_t(h[pos + 1]) << 8);
}

uint32_t read32(const unsigned char* h, int pos) {
    return uint32_t(h[pos])
         | (uint32_t(h[pos + 1]) << 8)
         | (uint32_t(h[pos + 2]) << 16)
         | (uint32_t(h[pos + 3]) << 24);
}

bool bacaBMP(const string& nama, BMP& gambar) {
    ifstream file(nama, ios::binary);

    if (!file) {
        cout << "Gagal membuka file: " << nama << endl;
        return false;
    }

    unsigned char header[54];

    file.read(reinterpret_cast<char*>(header), 54);

    if (file.gcount() != 54 ||
        header[0] != 'B' || header[1] != 'M') {
        cout << "File BMP tidak valid: " << nama << endl;
        return false;
    }

    uint32_t offset = read32(header, 10);
    uint32_t headerSize = read32(header, 14);

    int32_t width = static_cast<int32_t>(read32(header, 18));
    int32_t tinggiAsli = static_cast<int32_t>(read32(header, 22));

    uint16_t planes = read16(header, 26);
    uint16_t bitDepth = read16(header, 28);
    uint32_t compression = read32(header, 30);

    if (headerSize < 40 || width <= 0 ||
        tinggiAsli == 0 || tinggiAsli == INT32_MIN ||
        planes != 1 || bitDepth != 24 || compression != 0) {
        cout << "Format BMP tidak didukung: " << nama << endl;
        return false;
    }

    gambar.width = width;
    gambar.height = tinggiAsli < 0
                  ? -tinggiAsli : tinggiAsli;

    uint64_t rowSize =
        ((uint64_t(gambar.width) * 3 + 3) / 4) * 4;

    uint64_t dataSize = rowSize * gambar.height;

    file.seekg(0, ios::end);
    uint64_t fileSize = static_cast<uint64_t>(file.tellg());

    if (offset > fileSize || dataSize > fileSize - offset) {
        cout << "Data pixel tidak lengkap: " << nama << endl;
        return false;
    }

    gambar.pixel.assign(
        gambar.height, vector<RGB>(gambar.width)
    );

    vector<unsigned char> baris(rowSize);

    file.seekg(offset, ios::beg);

    for (int yFile = 0; yFile < gambar.height; yFile++) {
        file.read(reinterpret_cast<char*>(baris.data()), rowSize);

        if (!file) {
            cout << "Gagal membaca data pixel: " << nama << endl;
            return false;
        }

        int y = tinggiAsli < 0
              ? yFile
              : gambar.height - 1 - yFile;

        for (int x = 0; x < gambar.width; x++) {
            int pos = x * 3;

            gambar.pixel[y][x] = {
                baris[pos + 2],
                baris[pos + 1],
                baris[pos]
            };
        }
    }

    cout << "\nFile: " << nama << endl;
    cout << "Ukuran file  : " << fileSize << " byte\n";
    cout << "Header pixel : " << offset << " byte\n";
    cout << "Lebar        : " << gambar.width << " pixel\n";
    cout << "Tinggi       : " << gambar.height << " pixel\n";
    cout << "Bit depth    : " << bitDepth << " bit\n";
    cout << "Ukuran data  : " << dataSize << " byte\n";

    return true;
}

int main() {
    BMP gambarC, gambarD;

    cout << "=== MEMBACA GAMBAR C ===\n";

    if (!bacaBMP(
    R"(D:\VS CODE\C++\C++\SD.s3\ARRAY123\gambar C.bmp)",
    gambarC)) {
    return 1;
}

if (!bacaBMP(
    R"(D:\VS CODE\C++\C++\SD.s3\ARRAY123\gambar D.bmp)",
    gambarD)) {
    return 1;
}

    if (gambarC.width != gambarD.width ||
        gambarC.height != gambarD.height) {
        cout << "\nUkuran kedua gambar berbeda.\n";
        cout << "Perbandingan pixel dibatalkan.\n";
        return 1;
    }

    int totalBerbeda = 0;
    uint64_t totalPixel =
        uint64_t(gambarC.width) * gambarC.height;

    cout << "\n=== HASIL PERBANDINGAN ===\n";

    for (int y = 0; y < gambarC.height; y++) {
        for (int x = 0; x < gambarC.width; x++) {
            RGB c = gambarC.pixel[y][x];
            RGB d = gambarD.pixel[y][x];

            if (c.r != d.r ||
                c.g != d.g ||
                c.b != d.b) {

                totalBerbeda++;

                cout << "\nPerbedaan ke-" << totalBerbeda << endl;
                cout << "Koordinat (x,y): ("
                     << x << ", " << y << ")\n";

                cout << "RGB C: ("
                     << int(c.r) << ", "
                     << int(c.g) << ", "
                     << int(c.b) << ")\n";

                cout << "RGB D: ("
                     << int(d.r) << ", "
                     << int(d.g) << ", "
                     << int(d.b) << ")\n";
            }
        }
    }

    cout << "\n=== RINGKASAN ===\n";
    cout << "Resolusi       : "
         << gambarC.width << " x "
         << gambarC.height << endl;

    cout << "Total pixel    : " << totalPixel << endl;
    cout << "Pixel berbeda  : " << totalBerbeda << endl;
    cout << "Pixel sama     : "
         << totalPixel - totalBerbeda << endl;

    if (totalBerbeda == 0) {
        cout << "Kedua gambar memiliki pixel yang sama.\n";
    }

    return 0;
}
