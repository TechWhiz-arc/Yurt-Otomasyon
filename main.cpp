#include<iostream>
#include<string>
#include<fstream>

#define OGRENCİ_ARRAY_SIZE 500

struct ogrenci {
    std::string ad = "";
    std::string soyad = "";
    int TC = 0;
};

ogrenci ogrenciler[OGRENCİ_ARRAY_SIZE];

void saveStudents() {
    std::ofstream file("students.dat", std::ios::binary);
    if (!file) {
        std::cerr << "Dosya açılamadı!" << std::endl;
        return;
    }

    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        if (ogrenciler[i].ad != "") {
            int nameLength = ogrenciler[i].ad.size();
            file.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            file.write(ogrenciler[i].ad.c_str(), nameLength);  // Write name

            int surnameLength = ogrenciler[i].soyad.size();
            file.write(reinterpret_cast<char*>(&surnameLength), sizeof(surnameLength));
            file.write(ogrenciler[i].soyad.c_str(), surnameLength);  // Write surname

            file.write(reinterpret_cast<char*>(&ogrenciler[i].TC), sizeof(ogrenciler[i].TC));  // Write TC number
        }
    }
    file.close();
}

void loadStudents() {
    std::ifstream file("students.dat", std::ios::binary);
    if (!file) {
        std::cerr << "Dosya açılamadı!" << std::endl;
        return;
    }

    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        int nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        if (file.eof()) break;

        ogrenciler[i].ad.resize(nameLength);
        file.read(&ogrenciler[i].ad[0], nameLength);

        int surnameLength;
        file.read(reinterpret_cast<char*>(&surnameLength), sizeof(surnameLength));
        ogrenciler[i].soyad.resize(surnameLength);
        file.read(&ogrenciler[i].soyad[0], surnameLength);

        file.read(reinterpret_cast<char*>(&ogrenciler[i].TC), sizeof(ogrenciler[i].TC));

        if (file.eof()) break;
    }

    file.close();
}

void ogrenciKayit() {
    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        if (ogrenciler[i].ad == "") { // Find the first empty spot
            std::cout << "Öğrenci adını girin: ";
            std::cin >> ogrenciler[i].ad;
            std::cout << "Öğrencinin soyadını girin: ";
            std::cin >> ogrenciler[i].soyad;
            std::cout << "Öğrencinin TC kimlik numarasını girin: ";
            std::cin >> ogrenciler[i].TC;
            std::cout << "Öğrenci başarılı ile kaydedildi.\n";
            // Save immediately after registration
            saveStudents();
            return; // exit after saving
        }
    }
    std::cout << "Kayıt yapılacak yer kalmadı.\n";
}

void ogrenciSil() {
    std::string ad, soyad;
    int TC;
    std::cout << "Öğrencinin adını girin: ";
    std::cin >> ad;
    std::cout << "Öğrencinin soyadını girin: ";
    std::cin >> soyad;
    std::cout << "Öğrencinin TC kimlik numarasını girin: ";
    std::cin >> TC;

    // Search for the student and delete their record
    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        if (ogrenciler[i].ad == ad && ogrenciler[i].soyad == soyad && ogrenciler[i].TC == TC) {
            ogrenciler[i].ad = "";
            ogrenciler[i].soyad = "";
            ogrenciler[i].TC = 0;
            std::cout << "Öğrenci kaydınız başarıyla silindi.\n";
            // Save after deletion
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

    // Find the student to edit
    for (int i = 0; i < OGRENCİ_ARRAY_SIZE; i++) {
        if (ogrenciler[i].ad == ad && ogrenciler[i].soyad == soyad) {
            std::cout << "Yeni adı girin: ";
            std::cin >> ogrenciler[i].ad;
            std::cout << "Yeni soyadı girin: ";
            std::cin >> ogrenciler[i].soyad;
            std::cout << "Öğrenci kaydı başarıyla güncellendi.\n";
            // Save after edit
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
    // Load students when the program starts
    loadStudents();

    int secim;
    bool answer = true;
    while (answer) {
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
                answer = false;
                break;
            default:
                std::cout << "Geçersiz seçim, tekrar deneyin.\n";
        }
    }
    return 0;
}
