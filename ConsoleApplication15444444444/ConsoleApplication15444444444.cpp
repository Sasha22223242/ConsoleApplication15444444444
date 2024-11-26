#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <locale>
#include <codecvt>

using namespace std;

struct VideoStore {
    string title;
    string director;
    string genre;
    float popularityRating;
    float price;
};

void displayMovies(const vector<VideoStore>& store) {
    for (const auto& movie : store) {
        cout << "Назва: " << movie.title << ", Режисер: " << movie.director
            << ", Жанр: " << movie.genre << ", Рейтинг: " << movie.popularityRating
            << ", Ціна: " << movie.price << " грн" << endl;
    }
}

void addMovie(vector<VideoStore>& store) {
    VideoStore movie;
    cout << "Введіть назву фільму: ";
    cin.ignore();
    getline(cin, movie.title);
    cout << "Введіть режисера: ";
    getline(cin, movie.director);
    cout << "Введіть жанр: ";
    getline(cin, movie.genre);
    cout << "Введіть рейтинг популярності (від 0 до 10): ";
    cin >> movie.popularityRating;
    cout << "Введіть ціну диска: ";
    cin >> movie.price;
    store.push_back(movie);
}

void searchByTitle(const vector<VideoStore>& store, const string& title) {
    bool found = false;
    for (const auto& movie : store) {
        if (movie.title == title) {
            cout << "Знайдений фільм: " << movie.title << ", Режисер: " << movie.director
                << ", Жанр: " << movie.genre << ", Рейтинг: " << movie.popularityRating
                << ", Ціна: " << movie.price << " грн" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Фільм з назвою \"" << title << "\" не знайдений." << endl;
    }
}

void searchByGenre(const vector<VideoStore>& store, const string& genre) {
    bool found = false;
    for (const auto& movie : store) {
        if (movie.genre == genre) {
            cout << "Знайдений фільм: " << movie.title << ", Режисер: " << movie.director
                << ", Жанр: " << movie.genre << ", Рейтинг: " << movie.popularityRating
                << ", Ціна: " << movie.price << " грн" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Фільмів у жанрі \"" << genre << "\" не знайдено." << endl;
    }
}

void searchByDirector(const vector<VideoStore>& store, const string& director) {
    bool found = false;
    for (const auto& movie : store) {
        if (movie.director == director) {
            cout << "Знайдений фільм: " << movie.title << ", Режисер: " << movie.director
                << ", Жанр: " << movie.genre << ", Рейтинг: " << movie.popularityRating
                << ", Ціна: " << movie.price << " грн" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Фільмів режисера \"" << director << "\" не знайдено." << endl;
    }
}

void searchMostPopularInGenre(const vector<VideoStore>& store, const string& genre) {
    float maxRating = -1;
    string popularMovie;
    for (const auto& movie : store) {
        if (movie.genre == genre && movie.popularityRating > maxRating) {
            maxRating = movie.popularityRating;
            popularMovie = movie.title;
        }
    }

    if (!popularMovie.empty()) {
        cout << "Найпопулярніший фільм у жанрі \"" << genre << "\": " << popularMovie << " з рейтингом " << maxRating << endl;
    }
    else {
        cout << "У жанрі \"" << genre << "\" немає фільмів." << endl;
    }
}

void saveToFile(const vector<VideoStore>& store, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& movie : store) {
            file << movie.title << "\n" << movie.director << "\n" << movie.genre << "\n"
                << movie.popularityRating << "\n" << movie.price << "\n";
        }
        cout << "Дані збережено у файл: " << filename << endl;
    }
    else {
        cout << "Не вдалося відкрити файл для запису." << endl;
    }
}

void loadFromFile(vector<VideoStore>& store, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        VideoStore movie;
        while (getline(file, movie.title)) {
            getline(file, movie.director);
            getline(file, movie.genre);
            file >> movie.popularityRating;
            file >> movie.price;
            file.ignore();
            store.push_back(movie);
        }
        cout << "Дані успішно завантажено з файлу: " << filename << endl;
    }
    else {
        cout << "Не вдалося відкрити файл для читання." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ukr");

    vector<VideoStore> store;
    string filename = "movies.txt";
    int choice;

    loadFromFile(store, filename);

    do {
        cout << "\nМеню:\n";
        cout << "1. Показати всі фільми\n";
        cout << "2. Додати фільм\n";
        cout << "3. Пошук за назвою\n";
        cout << "4. Пошук за жанром\n";
        cout << "5. Пошук за режисером\n";
        cout << "6. Найпопулярніший фільм у жанрі\n";
        cout << "7. Зберегти дані у файл\n";
        cout << "8. Вийти\n";
        cout << "Виберіть дію: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayMovies(store);
            break;
        case 2:
            addMovie(store);
            break;
        case 3: {
            string title;
            cout << "Введіть назву фільму для пошуку: ";
            cin.ignore();
            getline(cin, title);
            searchByTitle(store, title);
            break;
        }
        case 4: {
            string genre;
            cout << "Введіть жанр для пошуку: ";
            cin.ignore();
            getline(cin, genre);
            searchByGenre(store, genre);
            break;
        }
        case 5: {
            string director;
            cout << "Введіть режисера для пошуку: ";
            cin.ignore();
            getline(cin, director);
            searchByDirector(store, director);
            break;
        }
        case 6: {
            string genre;
            cout << "Введіть жанр для пошуку найпопулярнішого фільму: ";
            cin.ignore();
            getline(cin, genre);
            searchMostPopularInGenre(store, genre);
            break;
        }
        case 7:
            saveToFile(store, filename);
            break;
        case 8:
            cout << "До побачення!" << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 8);

    return 0;
}
