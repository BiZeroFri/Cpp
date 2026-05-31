#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>

using namespace std;

struct Date {	//daty
    int day;
    int month;
    int year;
};


class MediaItem {	//klasa abstrakcyjna
protected:
    string title;
    int year;
    chrono::system_clock::time_point borrowDate; // Data wypożyczenia

public:
    
    MediaItem(string t, int y, Date bDate) : title(t), year(y) {
        tm tm_date = {};
        tm_date.tm_mday = bDate.day;
        tm_date.tm_mon = bDate.month - 1; //0 do 11
        tm_date.tm_year = bDate.year - 1900; //lata od 1900
        
        time_t tt = mktime(&tm_date);
        borrowDate = chrono::system_clock::from_time_t(tt);
    }

    virtual ~MediaItem() {}		//destruktor wirtualny żeby pamięć nie wyciekła 

    
    virtual void displayInfo() const = 0;	//metoda abstrakcyjna - wyświetlenie danych

    
   virtual bool isOverdue() const {		//czy minęło 30 dni
    auto now = chrono::system_clock::now();
    
    
    auto diff = chrono::duration_cast<chrono::hours>(now - borrowDate); //w godzinach bo w dniach się wysypało :(
    
    
    return diff.count() > 720;
}
};


class Book : public MediaItem { 	//pochodna klasa - książka
private:
    string author;
    int pages;

public:
    Book(string t, int y, Date bDate, string auth, int p)
        : MediaItem(t, y, bDate), author(auth), pages(p) {}

    ~Book() override {
    }

    void displayInfo() const override {
        cout << "[KSIĄŻKA] " << author << " - \"" << title << "\" (" << year << ")\n"
                  << "          Strony: " << pages << " | Status: " 
                  << (isOverdue() ? "PRZETERMINOWANE!" : "W terminie") << "\n\n";
    }
};


class DVD : public MediaItem {	//pochodna klasa - dvd
private:
    int duration; 
    string director;

public:
    DVD(string t, int y, Date bDate, int dur, string dir)
        : MediaItem(t, y, bDate), duration(dur), director(dir) {}

    ~DVD() override {}

    void displayInfo() const override {
        cout << "[FILM DVD] \"" << title << "\" w reżyserii " << director << " (" << year << ")\n"
                  << "           Czas: " << duration << " min | Status: " 
                  << (isOverdue() ? "PRZETERMINOWANE!" : "W terminie") << "\n\n";
    }
};


class Magazine : public MediaItem {		//pochodna klasa - magazyn
private:
    int issueNumber;

public:
    Magazine(string t, int y, Date bDate, int issue)
        : MediaItem(t, y, bDate), issueNumber(issue) {}

    ~Magazine() override {}

    void displayInfo() const override {
        cout << "[CZASOPISMO] \"" << title << "\" | Numer wydania: " << issueNumber << " (" << year << ")\n"
                  << "              Status: " << (isOverdue() ? "PRZETERMINOWANE!" : "W terminie") << "\n\n";
    }
};


int main() {
    
    vector<unique_ptr<MediaItem>> library;	//wektor przechowujacy wskazniki do klasy

    // Przykładowe daty:
    Date oldDate = {1, 2, 2026};   
    Date freshDate = {29, 5, 2026}; 

    
    library.push_back(make_unique<Book>("Przewodnik po głupocie", 2024, oldDate, "Wiktoria Brożek", 1200));
    library.push_back(make_unique<Book>("Wiedźmin", 1993, freshDate, "Andrzej Sapkowski", 330));
    library.push_back(make_unique<Book>("HsObs", 2025, oldDate, "Katerine Romanov", 500));

    
    library.push_back(make_unique<DVD>("Film", 2010, freshDate, 148, "Marek Cukierek"));
    library.push_back(make_unique<DVD>("Fajnejszy film", 1999, oldDate, 136, "Stefan Prace"));
    library.push_back(make_unique<DVD>("Władca Pierścieni", 2001, freshDate, 178, "Peter Jackson"));

    
    library.push_back(make_unique<Magazine>("Magazyn top wiezniow", 2026, oldDate, 114));
    library.push_back(make_unique<Magazine>("National Geographic", 2025, freshDate, 5));
    library.push_back(make_unique<Magazine>("CDAction", 2026, freshDate, 312));

    
    
    cout << "--- BIBLIOTEKA ---\n\n";
    for (const auto& item : library) {
        item->displayInfo(); 
    }

    return 0;
}
