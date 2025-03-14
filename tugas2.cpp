#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

struct Buku
{
    char ID[20];
    char judul[50];
    char penulis[50];
    int stok;
};

bool login(string &username)
{
    string password;
    string validUsername = "rara";
    string validPassword = "151";

    while (true)
    {
        cout << "LOGIN KE DATABASE PERPUSTAKAAN INFORMATIKA\n";

        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;

        if (username == validUsername && password == validPassword)
        {
            return true;
        }
        else
        {
            cout << "Username atau password salah.\n";
        }
    }
}

void tambahBuku()
{
    Buku buku;
    FILE *file = fopen("data.dat", "ab");

    if (!file)
    {
        cout << "Gagal membuka file!\n";
        return;
    }

    do
    {
        cout << "===== Tambah Data Buku =====\n";

        cout << "ID buku: ";
        cin.ignore();
        cin.getline(buku.ID, sizeof(buku.ID));

        cout << "Judul buku: ";
        cin.getline(buku.judul, sizeof(buku.judul));

        cout << "Penulis: ";
        cin.getline(buku.penulis, sizeof(buku.penulis));

        cout << "Stok: ";
        cin >> buku.stok;
        cin.ignore();

        fwrite(&buku, sizeof(Buku), 1, file);
        cout << "Buku berhasil ditambahkan!\n";

        char kembali;
        do
        {
            cout << "Balik ke menu? (Y/N) ";
            cin >> kembali;
            cin.ignore();

            if (kembali == 'Y' || kembali == 'y' || kembali == 'N' || kembali == 'n')
            {
                break;
            }
            cout << "Input tidak valid! Masukkan Y atau N.\n";
        } while (true);

        if (kembali == 'N' || kembali == 'n')
            break;

    } while (true);

    fclose(file);
}

void tampilkanBuku()
{
    Buku buku;
    Buku daftarBuku[100];
    int jumlah = 0;

    FILE *file = fopen("data.dat", "rb");
    if (!file)
    {
        cout << "File tidak ditemukan.\n";
        return;
    }

    while (fread(&buku, sizeof(Buku), 1, file))
    {
        daftarBuku[jumlah++] = buku;
    }
    fclose(file);

    if (jumlah == 0)
    {
        cout << "Tidak ada buku dalam daftar.\n";
        return;
    }

    for (int i = 0; i < jumlah - 1; i++)
    {
        for (int j = 0; j < jumlah - i - 1; j++)
        {
            if (strcmp(daftarBuku[j].ID, daftarBuku[j + 1].ID) > 0)
            {
                swap(daftarBuku[j], daftarBuku[j + 1]);
            }
        }
    }

    cout << left << setw(10) << "ID" << setw(30) << "Judul" << setw(30) << "Penulis" << setw(10) << "Stok" << endl;
    cout << string(80, '=') << endl;
    for (int i = 0; i < jumlah; i++)
    {
        cout << left << setw(10) << daftarBuku[i].ID << setw(30) << daftarBuku[i].judul << setw(30) << daftarBuku[i].penulis << setw(10) << daftarBuku[i].stok << endl;
    }

    char kembali;
    cout << "Balik ke menu? (Y/N) ";
    cin >> kembali;
    cin.ignore();
}

void cariBuku()
{
    Buku buku;
    char kataKunci[50];
    bool ditemukan = false;

    cout << "Masukkan kata kunci dari judul buku yang dicari: ";
    cin.ignore();
    cin.getline(kataKunci, sizeof(kataKunci));

    FILE *file = fopen("data.dat", "rb");

    if (!file)
    {
        cout << "File tidak ditemukan.\n";
        return;
    }

    cout << "\n===========================================================================\n";
    cout << left << setw(10) << "ID" << setw(30) << "Judul" << setw(30) << "Penulis" << setw(10) << "Stok" << endl;
    cout << "===========================================================================\n";

    while (fread(&buku, sizeof(Buku), 1, file))
    {
        if (strstr(buku.judul, kataKunci) != nullptr)
        {
            cout << left << setw(10) << buku.ID << setw(30) << buku.judul << setw(30) << buku.penulis << setw(10) << buku.stok << endl;
            ditemukan = true;
        }
    }
    fclose(file);

    if (!ditemukan)
    {
        cout << "Buku dengan kata " << kataKunci << " tidak ditemukan.\n";
    }

    char kembali;
    cout << "Balik ke menu? (Y/N) ";
    cin >> kembali;
    cin.ignore();
}

void hapusBuku()
{
    Buku buku;
    char hapusID[20];
    bool ditemukan = false;
    Buku daftarBuku[100];
    int jumlah = 0;

    cout << "Masukkan ID buku yang ingin dihapus: ";
    cin.ignore();
    cin.getline(hapusID, sizeof(hapusID));

    FILE *file = fopen("data.dat", "rb");
    if (!file)
    {
        cout << "File tidak ditemukan!\n";
        return;
    }

    while (fread(&buku, sizeof(Buku), 1, file))
    {
        if (strcmp(buku.ID, hapusID) == 0)
        {
            ditemukan = true;
        }
        else
        {
            daftarBuku[jumlah++] = buku;
        }
    }
    fclose(file);

    if (ditemukan)
    {
        file = fopen("data.dat", "wb");
        for (int i = 0; i < jumlah; i++)
        {
            fwrite(&daftarBuku[i], sizeof(Buku), 1, file);
        }
        fclose(file);
        cout << "Buku dengan ID " << hapusID << " telah dihapus!\n";
    }
    else
    {
        cout << "Buku dengan ID " << hapusID << " tidak ditemukan.\n";
    }

    char kembali;
    cout << "Balik ke menu? (Y/N) ";
    cin >> kembali;
    cin.ignore();
}

int main()
{
    remove("data.dat");
    string username;
    if (!login(username))
    {
        return 0;
    }

    int pilihan;
    do
    {
        cout << "\nHalo, " << username << "! SELAMAT DATANG DI DATABASE PERPUSTAKAAN INFORMATIKA\n";
        cout << "1. Tambah data buku\n";
        cout << "2. Tampilkan daftar buku\n";
        cout << "3. Cari buku\n";
        cout << "4. Hapus buku\n";
        cout << "5. Keluar\n";
        cout << ">> ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            tambahBuku();
            break;
        case 2:
            tampilkanBuku();
            break;
        case 3:
            cariBuku();
            break;
        case 4:
            hapusBuku();
            break;
        case 5:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}