#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

struct Pegawai
{
    int id;
    char nama[50];
    double gaji;
};

void tambahPegawai();
void lihatPegawai();
void cariPegawai();
void perbaruiGaji();

int main()
{
    int pilihan;
    do
    {
        cout << "\nSistem Informasi Kepegawaian";
        cout << "\n1. Tambah Data Pegawai";
        cout << "\n2. Lihat Daftar Pegawai";
        cout << "\n3. Cari Pegawai Berdasarkan ID";
        cout << "\n4. Perbarui Gaji Pegawai";
        cout << "\n5. Keluar";
        cout << "\nPilih menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahPegawai();
            break;
        case 2:
            lihatPegawai();
            break;
        case 3:
            cariPegawai();
            break;
        case 4:
            perbaruiGaji();
            break;
        case 5:
            cout << "Keluar dari program..." << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);
    return 0;
}

void tambahPegawai()
{
    FILE *file = fopen("pegawai.dat", "ab");
    if (!file)
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    Pegawai p;
    cout << "Masukkan ID Pegawai: ";
    cin >> p.id;
    cout << "Masukkan Nama Pegawai: ";
    cin.ignore();
    cin.getline(p.nama, 50);
    cout << "Masukkan Gaji Pegawai: ";
    cin >> p.gaji;

    fwrite(&p, sizeof(Pegawai), 1, file);
    fclose(file);
    cout << "Data pegawai berhasil ditambahkan!" << endl;
}

void lihatPegawai()
{
    FILE *file = fopen("pegawai.dat", "rb");
    if (!file)
    {
        cout << "Gagal membuka file atau tidak ada data!" << endl;
        return;
    }

    Pegawai p;
    cout << "\nDaftar Pegawai:" << endl;
    while (fread(&p, sizeof(Pegawai), 1, file))
    {
        cout << "ID: " << p.id << ", Nama: " << p.nama << ", Gaji: " << p.gaji << endl;
    }
    fclose(file);
}

void cariPegawai()
{
    FILE *file = fopen("pegawai.dat", "rb");
    if (!file)
    {
        cout << "Gagal membuka file atau tidak ada data!" << endl;
        return;
    }

    int idCari;
    cout << "Masukkan ID Pegawai yang dicari: ";
    cin >> idCari;

    Pegawai p;
    bool ditemukan = false;
    while (fread(&p, sizeof(Pegawai), 1, file))
    {
        if (p.id == idCari)
        {
            cout << "Pegawai ditemukan: ID: " << p.id << ", Nama: " << p.nama << ", Gaji: " << p.gaji << endl;
            ditemukan = true;
            break;
        }
    }
    fclose(file);
    if (!ditemukan)
    {
        cout << "Pegawai dengan ID " << idCari << " tidak ditemukan." << endl;
    }
}

void perbaruiGaji()
{
    FILE *file = fopen("pegawai.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");
    if (!file || !tempFile)
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    int idCari;
    double gajiBaru;
    cout << "Masukkan ID Pegawai yang ingin diperbarui gajinya: ";
    cin >> idCari;

    Pegawai p;
    bool ditemukan = false;

    while (fread(&p, sizeof(Pegawai), 1, file))
    {
        if (p.id == idCari)
        {
            cout << "Masukkan gaji baru: ";
            cin >> gajiBaru;
            p.gaji = gajiBaru;
            ditemukan = true;
        }
        fwrite(&p, sizeof(Pegawai), 1, tempFile);
    }
    fclose(file);
    fclose(tempFile);

    remove("pegawai.dat");
    rename("temp.dat", "pegawai.dat");

    if (!ditemukan)
    {
        cout << "Pegawai dengan ID " << idCari << " tidak ditemukan." << endl;
    }
    else
    {
        cout << "Gaji pegawai berhasil diperbarui." << endl;
    }
}
