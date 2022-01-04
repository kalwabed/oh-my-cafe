// copyright (c) 2021, @author Kelompok 7 -- 21 IF 04
//-----------------------------------------------------------
// Muhammad Albaab Ridho Pratama 21.11.4057
// Evi Zulfia Rahmah             21.11.4064
// Kalwabed Rizki				  21.11.4078
// Ndaru Windra Sayidinaa		  21.11.4089
// Firresa Alif Nurrahman		  21.11.4104

#include <iomanip>
#include <iostream>

#include "VariadicTable.h"
#include "helpers.h"

using namespace std;

// --start-region-- Deklarasi global variabel
string menu[10] = {"Nasi Goreng", "Nasi Padang", "Mie ayam V1", "Mie Goreng",
                   "Nasi Kuning", "V60",         "Choco milk",  "Long black",
                   "Americano",   "Cappucino"};

int hargaPerItem[10] = {10000, 12000, 15000, 18000, 20000,
                        30000, 13000, 20000, 17000, 18000};
int jumlahPerItem[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int totalHarga, indexPesanan = 0;

struct Pesanan {
  string nama;
  int index, jumlah, harga;
} pesanan[10];
// --end-region-- Deklarasi global variabel

// --start-region-- Deklarasi function dan prosedur
void listMenu() {
  // print menu with matrix style
  cout << "==============================" << endl;
  cout << "=          MAKANAN           =" << endl;
  cout << "==============================" << endl;
  for (int i = 0; i < 5; i++) {
    cout << i + 1 << ". " << formatTab(menu[i]);
    cout << hargaPerItem[i] << endl;
  }

  // print menu with matrix style
  cout << "==============================" << endl;
  cout << "=          MINUMAN           =" << endl;
  cout << "==============================" << endl;
  for (int i = 5; i < 10; i++) {
    cout << i + 1 << ". " << formatTab(menu[i]);
    cout << hargaPerItem[i] << endl;
  }

  cout << endl;
}

// mode : 0 default, 1 update
void tampilkanPesanan(int mode = 0) {
  system("clear");

  switch (mode) {
    case 1:
      cout << "==============================" << endl;
      cout << "=        Ubah Pesanan        =" << endl;
      cout << "==============================" << endl;
      break;

    default:
      cout << "==============================" << endl;
      cout << "=        Pesanan             =" << endl;
      cout << "==============================" << endl;
      break;
  }

  VariadicTable<int, string, int, int, int> vt(
      {"No.", "Menu", "Jumlah", "Harga", "Subtotal"}, 10);

  // perulangan untuk menampilkan pesanan makanan dan harga makanan, jumlah
  // makanan dan subtotal makanan
  int indexNumber = 1;
  // tampilkan pesanan
  for (int i = 0; i < 10; i++) {
    if (pesanan[i].jumlah > 0) {
      vt.addRow(indexNumber++, pesanan[i].nama, pesanan[i].jumlah,
                hargaPerItem[pesanan[i].index], pesanan[i].harga);
    }
  }

  // mencetak tabel pesanan
  vt.print(cout);

  totalHarga = 0;
  for (int i = 0; i < 10; i++) {
    totalHarga += hargaPerItem[pesanan[i].index] * pesanan[i].jumlah;
  }

  cout << "Total Harga Pesanan Anda : " << totalHarga << endl;
}

void promptUbahPesanan() {
  int nomorMenu, jumlahPesanan, subtotalBaru;

  tampilkanPesanan(1);
  cout << endl;
  cout << "Masukkan nomor menu yang ingin diubah : ";
  cin >> nomorMenu;
  cout << "Masukkan jumlah pesanan yang ingin diubah : ";
  cin >> jumlahPesanan;

  subtotalBaru = hargaPerItem[pesanan[nomorMenu - 1].index] * jumlahPesanan;
  pesanan[nomorMenu - 1].jumlah = jumlahPesanan;
  pesanan[nomorMenu - 1].harga = subtotalBaru;
}

void assignPesanan(int index, int indexMenu) {
  // memasukkan nilai pesanan ke dalam array pesanan
  pesanan[index].nama = menu[indexMenu];
  pesanan[index].index = indexMenu;
  pesanan[index].jumlah = jumlahPerItem[indexMenu];
  pesanan[index].harga = hargaPerItem[indexMenu] * jumlahPerItem[indexMenu];
}
// --end-region-- Deklarasi function dan prosedur

int main() {
  int pilihan, lanjut, uangPembayaran, totalKembalian = 0, ubahPesanan, donasi,
                                       isDonasi;

  cout << "==============================" << endl;
  cout << "=     SELAMAT DATANG DI      =" << endl;
  cout << "=        Oh My Cafe          =" << endl;
  cout << "==============================" << endl;

pilihMenu:
  listMenu();

  cout << "Masukkan pilihan menu: ";
  cin >> pilihan;

  for (int i = 0; i < 10; i++) {
    if (pilihan == i + 1) {
      cout << "Masukkan jumlah " << menu[i] << " yang ingin dipesan : ";
      cin >> jumlahPerItem[i];

      assignPesanan(indexPesanan++, i);

      cout << endl;
      cout << "Apakah anda ingin memesan lagi? (1. Ya, 2. Tidak) : ";
      cin >> lanjut;

      if (lanjut == 1) {
        system("clear");
        goto pilihMenu;
      }
      break;
    }
  }

  tampilkanPesanan();

  cout << endl;
  cout << "Apakah anda ingin mengubah pesanan? (1. Ya, 2. Tidak) : ";
  cin >> ubahPesanan;

  if (ubahPesanan == 1) {
    promptUbahPesanan();
    tampilkanPesanan();

    cout << endl;
    cout << "Apakah anda ingin memesan lagi? (1. Ya, 2. Tidak) : ";
    cin >> lanjut;

    if (lanjut == 1) {
      goto pilihMenu;
    }
  }

  tampilkanPesanan();

bayar:
  cout << endl;
  cout << "Masukkan uang pembayaran: ";
  cin >> uangPembayaran;

  totalKembalian = uangPembayaran - totalHarga;

  if (totalKembalian < 0) {
    cout << "Uang pembayaran anda kurang" << endl;
    cout << "Tekan ENTER untuk kembali input uang...";
    cin.ignore();
    cin.get();
    goto bayar;
  }

  tampilkanPesanan();
  cout << "Uang pembayaran: " << uangPembayaran << endl;
  cout << "Total kembalian: " << totalKembalian << endl;

  if (totalKembalian > 0 && totalKembalian <= 500) {
    cout << endl;
    cout << "Apakah anda ingin mengirimkan donasi? (1. Ya, 2. Tidak) : ";
    cin >> isDonasi;
    if (isDonasi == 1) {
      donasi = totalKembalian;
      totalKembalian = 0;
      tampilkanPesanan();
      cout << "Uang pembayaran: " << uangPembayaran << endl;
      cout << "Total kembalian: " << totalKembalian << endl;
      cout << "Donasi: " << donasi << endl;
    }
  }

  cout << endl;
  cout << "--- Terima kasih telah berbelanja di Oh My Cafe ---" << endl;

  return 0;
}
