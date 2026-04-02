#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::filesystem;



int wypisz(string npliku)
{
	fstream plik1;
	
	plik1.open(npliku);
	
	int linie=0, slowa=0, znaki=0;
	string s1;
	
	if(!plik1)
	{
		cout << "Nie dziala plik :(";
		
		return 1;
	}
	else
	{
		while(!plik1.eof())
		{
			getline(plik1, s1);
			linie++;
			
			
			for (char &c : s1) {
            znaki++; // Liczymy każdy znak
            if (ispunct(c)) {
                c = ' '; // Zamieniamy interpunkcję na spację dla stringstream
            }
        }

        stringstream ss(s1);
        string slowo;
        while (ss >> slowo) { //do opaczania!  OPACZ TO!!!!!!!!!!!!!!!!!!!!!!
            slowa++;
        }
			

		}
		string wynik = "wyniki_analizy.txt";
		ofstream plik2(wynik);
		
		if (plik2.is_open()) {
        plik2<< "Analiza pliku: " << npliku << endl;
        plik2 << "Liczba linii: " << to_string(linie) << endl;
        plik2 << "Liczba slow: " << to_string(slowa) << endl;
        plik2 << "Liczba znakow: " << to_string(znaki) << endl;
        plik2.close();
        cout << "Wyniki zapisano w: " << wynik << endl;
    }
		
	}
	
}

int main(int argc, char* argv[])
{

	path katalog = current_path();
	string nazwa = argv[1];
	
	
	
	switch(path p{nazwa}; status(p).type())
	{
		case file_type::not_found:
			cout <<"nie ma pliku\n";
			break;
		case file_type::directory:
			cout << "dir: "<<p<<endl;
			for(const auto& it : directory_iterator{p})
			{
				cout<<" - "<<it.path()<<endl;
			}
			break;
		case file_type::regular:
			cout<<" ok "<<endl;
			[[fallthrough]];
			default:
				wypisz(nazwa);
				
				
			
	}
	
	
	
	
	return 0;
}
