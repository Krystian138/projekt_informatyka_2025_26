# Arkanoid – projekt z Informatyki II (C++ / SFML)

## Opis gry

Projekt jest prostą grą typu **Arkanoid** napisaną w C++ z użyciem biblioteki **SFML**.  
Gracz steruje paletką na dole ekranu i odbija piłkę tak, aby zbić wszystkie klocki na planszy.  
Po przegranej wynik jest zapisywany do pliku i można go później obejrzeć w ekranie wyników.

Rozdzielczość okna: **800 × 600**, liczba FPS ograniczona do **60**.

---

## Funkcjonalności

- gra w trybie graficznym z animowanymi obiektami (paletka, piłka, klocki),
- sterowanie z klawiatury (menu + rozgrywka),
- kolizje:
  - piłka–ściany,
  - piłka–paletka,
  - piłka–klocki (znikanie / zmiana koloru po trafieniu),
- kilka poziomów „wytrzymałości” klocków (kolor zależny od liczby punktów życia),
- zapis i odczyt **stanu gry** do pliku `zapis.txt`,
- zapis wyników gracza do pliku `wyniki.txt` i ekran z listą ostatnich wyników,
- prosta architektura obiektowa:
  - `Game` – logika gry,
  - `Paletka` – sterowanie paletką,
  - `Pilka` – ruch i kolizje piłki,
  - `Stone` – klocek,
  - `GameState` – serializacja stanu gry (snapshot),
  - `Menu` – menu główne.

---

## Sterowanie

### Menu główne

- **Strzałka ↑ / ↓** – zmiana zaznaczonej opcji w menu,
- **Enter** – zatwierdzenie wyboru,
- **ESC** – wyjście z gry (lub powrót do menu z innych ekranów).

Przykładowe pozycje w menu:

1. **Nowa gra** – start od początku,
2. **Wczytaj zapis** – kontynuacja z pliku `zapis.txt`,
3. **Ostatnie wyniki** – wyświetlenie zawartości `wyniki.txt`,
4. **Wyjście** – zamknięcie programu.

### Podczas gry

- **Strzałka ← / →** – ruch paletki w lewo / prawo,
- **S** – zapis aktualnego stanu gry do pliku `zapis.txt`,
- **ESC** – powrót do menu głównego.

---

## Zapis stanu gry i wyniki

- **Zapis gry** – po wciśnięciu **S** w trakcie rozgrywki:
  - program tworzy „snapshot” obiektów (`GameState`),
  - zapisuje pozycję paletki, piłki, wektor klocków (pozycje + punkty życia) do pliku `zapis.txt`.

- **Wczytanie gry** – z menu wybieramy opcję **Wczytaj zapis**:
  - plik `zapis.txt` jest wczytywany,
  - stan gry jest odtwarzany: paletka, piłka, klocki wracają do zapisanych pozycji.

- **Wyniki** – po przegranej (piłka spada poniżej dolnej krawędzi okna):
  - aktualny wynik gracza dopisywany jest do pliku `wyniki.txt`,
  - w menu można przejść do ekranu **Ostatnie wyniki**,  
    gdzie tekst z pliku jest wyświetlany w oknie gry.

---

## Struktura katalogów i ważniejsze pliki

Projekt znajduje się w katalogu `początek2`.

Najważniejsze pliki:

- `początek2.cpp` – punkt wejścia programu, pętla główna, obsługa stanów aplikacji  
  (menu, rozgrywka, ekran wyników, wyjście),
- `Game.h / Game.cpp` – główna logika gry (inicjalizacja, aktualizacja, rysowanie,
  obsługa klocków, zapisu i odczytu stanu),
- `Paletka.h / paletka.cpp` – klasa paletki (ruch, ograniczenie do krawędzi ekranu, rysowanie),
- `Pilka.h / pilka.cpp` – klasa piłki (ruch, kolizje ze ścianami, paletką, reset pozycji),
- `Stonge.h / Stonge.cpp` – klasa klocka (`Stone`), dziedziczy po `sf::RectangleShape`,
- `GameState.h / GameState.cpp` – struktury i funkcje do zapisu/odtwarzania stanu gry,
- `Menu.h / Menu.cpp` – rysowanie i obsługa menu głównego,
- `arial.ttf` – używana czcionka,
- `zapis.txt` – zapis aktualnego stanu gry,
- `wyniki.txt` – plik tekstowy z wynikami gracza,
- `początek2.vcxproj` – plik projektu Visual Studio.

---

## Jak uruchomić projekt

1. Zainstaluj **Visual Studio** z obsługą „Desktop development with C++”.
2. Zainstaluj bibliotekę **SFML 2.x** (wersja dla Visual Studio, 64-bit).
3. Sklonuj repozytorium lub pobierz je jako ZIP i rozpakuj.
4. Otwórz plik projektu:  
   `początek2/początek2.vcxproj` w Visual Studio.
5. Upewnij się, że w ustawieniach projektu:
   - ścieżki **Include** i **Library** wskazują na katalogi z SFML,
   - dołączone są odpowiednie biblioteki (`sfml-graphics`, `sfml-window`, `sfml-system` – wersje debug/release).
6. Wybierz konfigurację **Debug** lub **Release**, platformę **x64**.
7.  uruchom projekt.

---
