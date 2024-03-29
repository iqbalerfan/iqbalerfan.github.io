#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Mendefinisikan struktur untuk menyimpan data barang
struct Barang {
    string nama;
    string kodeUnik;
    int jumlah;
    double harga;
    Barang* next;
};

// Kelas Inventaris untuk mengelola daftar barang
class Inventaris {
private:
    Barang* head;

public:
    Inventaris() : head(nullptr) {}

    // Fungsi untuk menambahkan barang baru ke dalam inventaris
    void tambahBarang(string nama, string kodeUnik, int jumlah, double harga) {
        Barang* baru = new Barang;
        baru->nama = nama;
        baru->kodeUnik = kodeUnik;
        baru->jumlah = jumlah;
        baru->harga = harga;
        baru->next = head;
        head = baru;
        cout << "Barang berhasil ditambahkan." << endl;
    }

    // Fungsi untuk menampilkan semua barang dalam inventaris
    void tampilkanDaftarBarang() {
        Barang* current = head;
        if (current == nullptr) {
            cout << "Inventaris kosong." << endl;
            return;
        }
        cout << "====================================================================" << endl;
        cout << setw(20) << left << "Nama" << setw(20) << "Kode Unik" << setw(10) << "Jumlah" << setw(10) << "Harga" << endl;
        cout << "--------------------------------------------------------------------" << endl;
        while (current != nullptr) {
            cout << setw(20) << left << current->nama << setw(20) << current->kodeUnik << setw(10) << current->jumlah << setw(10) << current->harga << endl;
            current = current->next;
        }
        cout << "====================================================================" << endl;
    }

    // Fungsi untuk mencari barang dalam inventaris berdasarkan nama atau kode unik
    Barang* cariBarang(string keyword) {
        Barang* current = head;
        while (current != nullptr) {
            if (current->nama == keyword || current->kodeUnik == keyword) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Fungsi untuk menghapus barang dari inventaris berdasarkan kode unik
    void hapusBarang(string kodeUnik) {
        Barang* current = head;
        Barang* prev = nullptr;
        while (current != nullptr) {
            if (current->kodeUnik == kodeUnik) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Barang dengan kode unik " << kodeUnik << " telah dihapus." << endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Barang dengan kode unik " << kodeUnik << " tidak ditemukan." << endl;
    }

    // Fungsi untuk memperbarui data barang dalam inventaris
    void perbaruiBarang(string kodeUnik, int jumlah, double harga) {
        Barang* barang = cariBarang(kodeUnik);
        if (barang != nullptr) {
            barang->jumlah = jumlah;
            barang->harga = harga;
            cout << "Informasi barang berhasil diperbarui." << endl;
        } else {
            cout << "Barang dengan kode unik " << kodeUnik << " tidak ditemukan." << endl;
        }
    }

    // Fungsi untuk menyimpan data inventaris ke dalam file
    void simpanData() {
        ofstream file("inventaris.txt");
        if (!file) {
            cerr << "Gagal membuka file." << endl;
            return;
        }
        Barang* current = head;
        while (current != nullptr) {
            file << current->nama << " " << current->kodeUnik << " " << current->jumlah << " " << current->harga << endl;
            current = current->next;
        }
        file.close();
        cout << "Data inventaris telah disimpan." << endl;
    }

    // Fungsi untuk memuat data inventaris dari file
    void muatData() {
        ifstream file("inventaris.txt");
        if (!file) {
            cerr << "Gagal membuka file." << endl;
            return;
        }
        string nama, kodeUnik;
        int jumlah;
        double harga;
        while (file >> nama >> kodeUnik >> jumlah >> harga) {
            tambahBarang(nama, kodeUnik, jumlah, harga);
        }
        file.close();
        cout << "Data inventaris telah dimuat." << endl;
    }

    // Destructor untuk menghapus semua barang dan membebaskan memori
    ~Inventaris() {
        Barang* current = head;
        while (current != nullptr) {
            Barang* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    Inventaris inventaris;
    inventaris.muatData();

    int pilihan;
    do {
        cout << "\n==========================================" << endl;
        cout << "               MENU INVENTARIS            " << endl;
        cout << "==========================================" << endl;
        cout << "1. Tambah Barang" << endl;
        cout << "2. Tampilkan Daftar Barang" << endl;
        cout << "3. Cari Barang" << endl;
        cout << "4. Hapus Barang" << endl;
        cout << "5. Perbarui Informasi Barang" << endl;
        cout << "6. Simpan Data Inventaris" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string nama, kodeUnik;
                int jumlah;
                double harga;
                cout << "Masukkan nama barang: ";
                cin.ignore(); // Membersihkan buffer
                getline(cin, nama);
                cout << "Masukkan kode unik: ";
                getline(cin, kodeUnik);
                cout << "Masukkan jumlah barang: ";
                cin >> jumlah;
                cout << "Masukkan harga barang: ";
                cin >> harga;
                inventaris.tambahBarang(nama, kodeUnik, jumlah, harga);
                break;
            }
            case 2:
                inventaris.tampilkanDaftarBarang();
                break;
            case 3: {
                string keyword;
                cout << "Masukkan nama atau kode unik barang yang ingin dicari: ";
                cin.ignore(); // Ignore newline left in the input buffer
                getline(cin, keyword);
                Barang* barang = inventaris.cariBarang(keyword);
                if (barang != nullptr) {
                    cout << "Barang ditemukan:" << endl;
                    inventaris.tampilkanDaftarBarang();
                } else {
                    cout << "Barang tidak ditemukan." << endl;
                }
                break;
            }
            case 4:
                {
                    string kodeUnik;
                    cout << "Masukkan kode unik barang yang ingin dihapus: ";
                    cin >> kodeUnik;
                    inventaris.hapusBarang(kodeUnik);
                }
                break;
            case 5:
                {
                    string kodeUnik;
                    int jumlah;
                    double harga;
                    cout << "Masukkan kode unik barang yang ingin diperbarui: ";
                    cin >> kodeUnik;
                    cout << "Masukkan jumlah baru: ";
                    cin >> jumlah;
                    cout << "Masukkan harga baru: ";
                    cin >> harga;
                    inventaris.perbaruiBarang(kodeUnik, jumlah, harga);
                }
                break;
            case 6:
                inventaris.simpanData();
                break;
            case 7:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih kembali." << endl;
        }
    } while (pilihan != 7);

    return 0;
}
