#include <iostream>
#include <string>
#include <time.h>

// Function prototypes
void ogrenciKayit();
void aidatOdeme();
void yurttanCikis();
void yurdaGiris();

int main() {
    int secim;

    std::cout << "Hangi işlemi yapmak istiyorsunuz? \n 1-Öğrenci kayıt\n 2-Aidat ödeme \n 3-Yurttan çıkış\n 4-Yurda giriş\n";
    std::cin >> secim;

    switch (secim) {
        case 1:
            ogrenciKayit();
            break;
        case 2:
            aidatOdeme();
            break;
        case 3:
            yurttanCikis();
            break;
        case 4:
            yurdaGiris();
            break;
        default:
            std::cout << "Geçersiz seçim." << std::endl;
            break;
    }

    return 0;
}

// Öğrenci kayıt fonksiyonu
void ogrenciKayit() {
    std::string ad, soyad, DT, cinsiyet, posta, adres, university, veli, vcep, vposta, yakinlik, burs;
    int oda_numara, oda_kisi, yatak_numara, kat, bmiktar, TC, cep;
    srand(time(nullptr));

    setlocale(LC_ALL, "Turkish");

    std::cout << "Öğrenci adını girin: ";
    std::cin >> ad;
    std::cout << "Öğrenci soyadını girin: ";
    std::cin >> soyad;
    std::cout << "Öğrenci TC kimlik numarasını girin: ";
    std::cin >> TC;
    std::cout << "Öğrenci doğum tarihini girin: ";
    std::cin >> DT;
    std::cout << "Öğrenci cinsiyetini girin: ";
    std::cin >> cinsiyet;
    std::cout << "Öğrenci cep telefonunu girin: ";
    std::cin >> cep;
    std::cout << "Öğrenci e-postasını girin: ";
    std::cin >> posta;
    std::cout << "Öğrenci adresini girin: ";
    std::cin >> adres;
    std::cout << "Üniversite adını girin: ";
    std::cin >> university;
    std::cout << "Veli adını-soyadını girin: ";
    std::cin >> veli;
    std::cout << "Velinin cep telefonunu girin: ";
    std::cin >> vcep;
    std::cout << "Velinin e-posta adresini girin: ";
    std::cin >> vposta;
    std::cout << "Velinin öğrenciye olan yakınlığı nedir?(anne,baba,abi...) ";
    std::cin >> yakinlik;
    std::cout << "Öğrencinin(varsa) aldığı burs türü nedir(devlet,vakıf)? ";
    std::cin >> burs;
    std::cout << "Öğrencinin aldığı burs miktarını girin: ";
    std::cin >> bmiktar;

    // Random oda numarası
    oda_numara = rand() % 501;
    if (oda_numara == 0) {
        oda_numara++;
    }
    std::cout << "Oda numaranız: " << oda_numara << std::endl;

    kat = oda_numara / 50;
    std::cout << "Kat numaranız: " << kat << std::endl;

    // Random oda kişisi
    oda_kisi = rand() % 9;
    if (oda_kisi == 0) {
        oda_kisi++;
    }
    std::cout << "Odanız " << oda_kisi << " kişilik." << std::endl;

    // Random yatak numarası
    yatak_numara = rand() % 4001;
    std::cout << "Yatak numaranız: " << yatak_numara << std::endl;
}

// Aidat ödeme fonksiyonu
void aidatOdeme() {
    int oda_kisi, aidat, odeme, borc;

    std::cout << "Odanız kaç kişilik (1/2/4/8)? ";
    std::cin >> oda_kisi;

    if (oda_kisi == 1) {
        aidat = 855;
    } else if (oda_kisi == 2) {
        aidat = 765;
    } else if (oda_kisi == 4) {
        aidat = 720;
    } else if (oda_kisi == 8) {
        aidat = 517;
    } else {
        std::cout << "Geçersiz oda kişisi!" << std::endl;
        return;
    }

    std::cout << "Bu ay ne kadar aidat ödemesi yaptınız? ";
    std::cin >> odeme;
    borc = aidat - odeme;
    if (borc < 0) {
        borc = 0;
    }
    std::cout << "Kalan borcunuz: " << borc << std::endl;
}

// Yurttan çıkış fonksiyonu
void yurttanCikis() {
    float cikis;
    std::cout << "Öğrencinin yurttan çıkış saatini girin: ";
    std::cin >> cikis;

    if (cikis < 6.00) {
        std::cout << "Sabah saat altıdan önce yurttan çıkamazsınız." << std::endl;
    }
}

// Yurda giriş fonksiyonu
void yurdaGiris() {
    float giris;
    std::cout << "Öğrencinin yurda giriş saatini girin: ";
    std::cin >> giris;

    if (giris > 23.00) {
        std::cout << "Yurda akşam on birden sonra giriş yasaktır." << std::endl;
    }
}
