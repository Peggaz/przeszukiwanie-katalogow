/*Zadanie rekrutacyjne do firmy telester
* Wersja podstawowa: 
Napisać aplikację okienkową (za pomocą mfc) – preferowane rozwiązanie lub konsolową, w języku programowania C++ na platformę Windows, pozwalającą na wskazanie folderu na dysku, w którym usunięte zostaną (w całej strukturze podkatalogów) pliki spełniające określony warunek filtrowania oraz puste katalogi.
Przeszukiwany folder ma być drzewem podkatalogów posiadającym co najmniej trzy poziomy zagnieżdżenia.
Struktura podkatalogów ma być wynikowo pozbawiona pustych folderów (bez względu na to, czy w danym podkatalogu były wcześniej pliki).
Po uruchomieniu procesu usuwania plików/folderów aplikacja musi wyświetlać postęp działania (na przykład pasek postępu lub procentowy przyrost). Jednoznacznie ma być pokazany start i koniec procesu.
Warunki filtrowania plików:
a)	według czasu utworzenia
b)	według czasu modyfikacji
c)	według czasu ostatniego użycia
Aby obsłużyć wszystkie warunki filtrowania będzie niezbędne użycie WinAPI (nie trzeba do wszystkich warunków go używać).
Aplikacja powinna umożliwiać zdefiniowanie zakresu czasowego dla poszczególnych warunków filtrowania, w którym zarówno dolny, jak i górny przedział może być otwarty.
Parametry programu: ścieżka do folderu, warunek filtrowania, czas lub zakres czasowy.
Czas realizacji: 6 godzin

Wersja rozszerzona:
Wprowadzenie w aplikacji wielowątkowości przyspieszającej działanie programu.
Czas realizacji: Do ustalenia

*/

#include "iostream"
#include <string>

#include <filesystem>
#include "konsola1.h"

namespace fs = std::filesystem;

std::string INCLUDE_DELETE = "del";
std::string PATH_SEARCH = "C:/Users/username/Desktop/TEL-STER/Main";
std::string global_progress_bar = "|          |";
int proges_bar = 1;


std::string upper_case(std::string s) {
    std::for_each(s.begin(), s.end(), [](char& c) {
        c = ::toupper(c);
        });
    return s;
}

void add_progress_bar() {
    proges_bar++;
    if (global_progress_bar.size() > proges_bar + 1)
        global_progress_bar[proges_bar] = *"=";
    system("cls");

    std::cout << global_progress_bar;
}

bool delet_catalog(std::string path, std::string file_like_to_del) {
    bool ret = false;
    for (const auto& entry : fs::directory_iterator(path)) {
        const auto file_name_str = entry.path().filename().string();
        std::error_code ec;
        if (entry.is_directory()) {
            if (!delet_catalog(path + "/" + file_name_str, file_like_to_del)) {
                fs::remove(path + "/" + file_name_str, ec);
            }
        } else if (entry.is_regular_file()) {
            if (upper_case(file_name_str).find(upper_case(file_like_to_del)) != std::string::npos ) {
                std::cout << "usunieteo plik: " << file_name_str << '\n';
                fs::remove(path + "/" + file_name_str);
            } else {
                ret = true;
            }
        } else
            std::cout << "??    " << file_name_str << '\n';
    }
    add_progress_bar();
    return ret;
}



int main(int argc, const char** argv) {
    const fs::path pathToShow{ argc >= 2 ? argv[1] : fs::current_path() };
    for (const auto& entry : fs::directory_iterator(PATH_SEARCH)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_directory()) {
            std::cout << "dir:  " << filenameStr << '\n';
        }
        else if (entry.is_regular_file()) {
            std::cout << "file: " << filenameStr << '\n';
        }
        else
            std::cout << "??    " << filenameStr << '\n';
    }

    std::cout << "======================\n";

    delet_catalog(PATH_SEARCH, INCLUDE_DELETE);
    std::cout << "\nzakonczona";
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
