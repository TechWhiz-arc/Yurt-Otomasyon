// Samethan Sönmez NO:2412729001
#include <iostream>
#include <string>
#include <fstream>

#define OGRENCİ_ARRAY_SIZE 500

struct ogrenci {
    std::string ad = "";
    std::string soyad = "";
    long long TC = 0;
};

ogrenci ogrenciler[OGRENCİ_ARRAY_SIZE];

void saveStudents() {
    std::ofstream file("students.dat", std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Dosya açılamadı!" << std::endl;
        return;
    }

    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        if (ogrenciler[i].ad != "") {
            int nameLength = ogrenciler[i].ad.size();
            file.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            file.write(ogrenciler[i].ad.c_str(), nameLength);

            int surnameLength = ogrenciler[i].soyad.size();
            file.write(reinterpret_cast<char*>(&surnameLength), sizeof(surnameLength));
            file.write(ogrenciler[i].soyad.c_str(), surnameLength);

            file.write(reinterpret_cast<char*>(&ogrenciler[i].TC), sizeof(ogrenciler[i].TC));
        }
    }

    file.close();
}

void loadStudents() {
    std::ifstream file("students.dat", std::ios::binary);
    if (!file) {
        return; // Eğer dosya yoksa veya açılamıyorsa, sessizce çık
    }

    int index = 0;
    while (true) {
        int nameLength, surnameLength;
        if (!file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) break;

        std::string ad(nameLength, '\0');
        file.read(&ad[0], nameLength);

        if (!file.read(reinterpret_cast<char*>(&surnameLength), sizeof(surnameLength))) break;

        std::string soyad(surnameLength, '\0');
        file.read(&soyad[0], surnameLength);

        int TC;
        if (!file.read(reinterpret_cast<char*>(&TC), sizeof(TC))) break;

        if (index < OGRENCİ_ARRAY_SIZE) {
            ogrenciler[index].ad = ad;
            ogrenciler[index].soyad = soyad;
            ogrenciler[index].TC = TC;
            index++;
        } else {
            break; // Öğrenci dizisini aşma durumunda döngüden çık
        }
    }

    file.close();
}

void ogrenciKayit() {
    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        if (ogrenciler[i].ad == "") {
            std::cout << "Öğrenci adını girin: ";
            std::cin >> ogrenciler[i].ad;
            std::cout << "Öğrencinin soyadını girin: ";
            std::cin >> ogrenciler[i].soyad;
            std::cout << "Öğrencinin TC kimlik numarasını girin: ";
            std::cin >> ogrenciler[i].TC;
            std::cout << "Öğrenci başarılı ile kaydedildi.\n";
            saveStudents();
            return;
        }
    }
    std::cout << "Kayıt yapılacak yer kalmadı.\n";
}

void ogrenciSil() {
    std::string ad, soyad;
    long long  TC;
    std::cout << "Öğrencinin adını girin: ";
    std::cin >> ad;
    std::cout << "Öğrencinin soyadını girin: ";
    std::cin >> soyad;
    std::cout << "Öğrencinin TC kimlik numarasını girin: ";
    std::cin >> TC;

    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        if (ogrenciler[i].ad == ad && ogrenciler[i].soyad == soyad && ogrenciler[i].TC == TC) {
            ogrenciler[i].ad = "";
            ogrenciler[i].soyad = "";
            ogrenciler[i].TC = 0;
            std::cout << "Öğrenci kaydı başarıyla silindi.\n";
            saveStudents();
            return;
        }
    }
    std::cout << "Öğrenci kaydı bulunamadı.\n";
}

void duzenle() {
    std::string ad, soyad;
    std::cout << "Değiştirmek istediğiniz öğrencinin adını girin: ";
    std::cin >> ad;
    std::cout << "Değiştirmek istediğiniz öğrencinin soyadını girin: ";
    std::cin >> soyad;

    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        if (ogrenciler[i].ad == ad && ogrenciler[i].soyad == soyad) {
            std::cout << "Yeni adı girin: ";
            std::cin >> ogrenciler[i].ad;
            std::cout << "Yeni soyadı girin: ";
            std::cin >> ogrenciler[i].soyad;
            std::cout << "Öğrenci kaydı başarıyla güncellendi.\n";
            saveStudents();
            return;
        }
    }
    std::cout << "Öğrenci kaydı bulunamadı.\n";
}

void listele() {
    bool found = false;
    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        if (ogrenciler[i].ad != "") {
            std::cout << "Ad: " << ogrenciler[i].ad << "\n";
            std::cout << "Soyad: " << ogrenciler[i].soyad << "\n";
            std::cout << "TC: " << ogrenciler[i].TC << "\n\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Kayıtlı öğrenci bulunmamaktadır.\n";
    }
}

void menu() {
    std::cout << "Hangi işlemi yapmak istiyorsunuz? \n [1]-Öğrenci kaydet\n [2]-Öğrenci Kaydını sil\n [3]-Öğrenci kaydını düzenle\n [4]-Kayıtlı öğrencileri listele\n [0]-Çıkış\n";
}

int main() {
    loadStudents();

    int secim;
    while (true) {
        menu();
        std::cin >> secim;
        switch (secim) {
            case 1:
                ogrenciKayit();
                break;
            case 2:
                ogrenciSil();
                break;
            case 3:
                duzenle();
                break;
            case 4:
                listele();
                break;
            case 0:
                std::cout << "Programdan çıkılıyor...\n";
                return 0;
            default:
                std::cout << "Geçersiz seçim, tekrar deneyin.\n";
        }
    }
}
