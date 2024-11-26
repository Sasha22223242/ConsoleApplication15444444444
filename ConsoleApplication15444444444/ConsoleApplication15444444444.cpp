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
        cout << "�����: " << movie.title << ", �������: " << movie.director
            << ", ����: " << movie.genre << ", �������: " << movie.popularityRating
            << ", ֳ��: " << movie.price << " ���" << endl;
    }
}

void addMovie(vector<VideoStore>& store) {
    VideoStore movie;
    cout << "������ ����� ������: ";
    cin.ignore();
    getline(cin, movie.title);
    cout << "������ ��������: ";
    getline(cin, movie.director);
    cout << "������ ����: ";
    getline(cin, movie.genre);
    cout << "������ ������� ����������� (�� 0 �� 10): ";
    cin >> movie.popularityRating;
    cout << "������ ���� �����: ";
    cin >> movie.price;
    store.push_back(movie);
}

void searchByTitle(const vector<VideoStore>& store, const string& title) {
    bool found = false;
    for (const auto& movie : store) {
        if (movie.title == title) {
            cout << "��������� �����: " << movie.title << ", �������: " << movie.director
                << ", ����: " << movie.genre << ", �������: " << movie.popularityRating
                << ", ֳ��: " << movie.price << " ���" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Գ��� � ������ \"" << title << "\" �� ���������." << endl;
    }
}

void searchByGenre(const vector<VideoStore>& store, const string& genre) {
    bool found = false;
    for (const auto& movie : store) {
        if (movie.genre == genre) {
            cout << "��������� �����: " << movie.title << ", �������: " << movie.director
                << ", ����: " << movie.genre << ", �������: " << movie.popularityRating
                << ", ֳ��: " << movie.price << " ���" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Գ���� � ���� \"" << genre << "\" �� ��������." << endl;
    }
}

void searchByDirector(const vector<VideoStore>& store, const string& director) {
    bool found = false;
    for (const auto& movie : store) {
        if (movie.director == director) {
            cout << "��������� �����: " << movie.title << ", �������: " << movie.director
                << ", ����: " << movie.genre << ", �������: " << movie.popularityRating
                << ", ֳ��: " << movie.price << " ���" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Գ���� �������� \"" << director << "\" �� ��������." << endl;
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
        cout << "�������������� ����� � ���� \"" << genre << "\": " << popularMovie << " � ��������� " << maxRating << endl;
    }
    else {
        cout << "� ���� \"" << genre << "\" ���� ������." << endl;
    }
}

void saveToFile(const vector<VideoStore>& store, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& movie : store) {
            file << movie.title << "\n" << movie.director << "\n" << movie.genre << "\n"
                << movie.popularityRating << "\n" << movie.price << "\n";
        }
        cout << "��� ��������� � ����: " << filename << endl;
    }
    else {
        cout << "�� ������� ������� ���� ��� ������." << endl;
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
        cout << "��� ������ ����������� � �����: " << filename << endl;
    }
    else {
        cout << "�� ������� ������� ���� ��� �������." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ukr");

    vector<VideoStore> store;
    string filename = "movies.txt";
    int choice;

    loadFromFile(store, filename);

    do {
        cout << "\n����:\n";
        cout << "1. �������� �� ������\n";
        cout << "2. ������ �����\n";
        cout << "3. ����� �� ������\n";
        cout << "4. ����� �� ������\n";
        cout << "5. ����� �� ���������\n";
        cout << "6. �������������� ����� � ����\n";
        cout << "7. �������� ��� � ����\n";
        cout << "8. �����\n";
        cout << "������� ��: ";
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
            cout << "������ ����� ������ ��� ������: ";
            cin.ignore();
            getline(cin, title);
            searchByTitle(store, title);
            break;
        }
        case 4: {
            string genre;
            cout << "������ ���� ��� ������: ";
            cin.ignore();
            getline(cin, genre);
            searchByGenre(store, genre);
            break;
        }
        case 5: {
            string director;
            cout << "������ �������� ��� ������: ";
            cin.ignore();
            getline(cin, director);
            searchByDirector(store, director);
            break;
        }
        case 6: {
            string genre;
            cout << "������ ���� ��� ������ ��������������� ������: ";
            cin.ignore();
            getline(cin, genre);
            searchMostPopularInGenre(store, genre);
            break;
        }
        case 7:
            saveToFile(store, filename);
            break;
        case 8:
            cout << "�� ���������!" << endl;
            break;
        default:
            cout << "������� ����. ��������� �� ���.\n";
        }
    } while (choice != 8);

    return 0;
}
