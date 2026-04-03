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

string czysc(string s) //usuwamy zbedne znaki
{
	string wynik = "";
	for(char c : s)
	{
		if (isalnum(c)) wynik += tolower(c);
	}
	return wynik;
}

void operacje(map<string, int>& mapa, ofstream& wyjscie)
{
	wyjscie << "Slowa zawierajace 'o' i 'l': ";
	auto it = mapa.begin();
	while (it != mapa.end())
	{
		string s = it->first;
		if(s.find('o') != string::npos && s.find('l') != string::npos)
		{
			wyjscie << s << " ";
		}
		if(s.find('q') != string::npos)
		{
			it = mapa.erase(it);
		}
		else{
			++it;
		}
	}
	wyjscie <<endl;
}

vector<string> wektor_slow(const map<string, int>& mapa)
{
	vector<string> v;
	for(auto const& [slowo, licznik] : mapa) v.push_back(slowo);
	
	sort(v.begin(), v.end(), [](const string& a, const string& b)
	{
	if(a.length() != b.length()) return a.length() < b.length();
	return a < b;
	});
	return v;
}

void statystyki(map<string, int>& mapa, const vector<string>& posortowane, int p, int np)
{
	ofstream plikOut("wyniki_analizy_szczegolowej.txt");
	plikOut << "Liczba roznych slow: " << mapa.size() << endl; // ile roznych slow
    plikOut << "Wyrazy parzyste: " << p << ", nieparzyste: " << np << endl; // parzyste/nieparzyste
    
    if(!posortowane.empty())
    {
    	size_t maxLen = posortowane.back().length();
    	plikOut << "Najdluzsze wyrazy: ";
    	for(const auto& s : posortowane)
    	{
    		if(s.length() == maxLen) plikOut << s <<" ";
		}
		plikOut << endl;
	}
	operacje(mapa, plikOut);
	plikOut.close();
}

void analiza_szczegolowa(string npliku)
{
	fstream plik1;
	plik1.open(npliku);
	
	map<string, int> mapa_slow;
	vector<string> wszystkie_slowa;
	int parzyste = 0, nieparzyste = 0;
	
	string linia, slowo1;
	
	while(getline(plik1, linia)) //dwa różne sposoby przeglądania pliku!
	{
		stringstream ss(linia); //rozbijamy linie
		while(ss >> slowo1)
		{
			string slowo2 = czysc(slowo1);
			if(!slowo2.empty())
			{
				mapa_slow[slowo2]++; //zliczamy wystapienie slowa w mapie
				wszystkie_slowa.push_back(slowo2);
				
				if(slowo2.length() % 2 == 0) parzyste++;
				else nieparzyste++;
			}
		}			
	}
	
	plik1.close();
	
	statystyki(mapa_slow, wektor_slow(mapa_slow), parzyste, nieparzyste);
	
}



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
		while(!plik1.eof()) //dwa różne sposoby przeglądania pliku!
		{
			getline(plik1, s1);
			linie++;
			
			
			for (char &c : s1) {
            znaki++; 
            if (ispunct(c)) {
                c = ' '; // Zamieniamy interpunkcję na spację dla stringstream
            }
        }

        stringstream ss(s1);
        string slowo;
        while (ss >> slowo) { // wrzucamy do stringa 
            slowa++;
        }
			

		}
		string wyniki = "wyniki_analizy.txt";
		ofstream plik2(wyniki);
		
		if (plik2.is_open()) {
        plik2<< "Analiza pliku: " << npliku << endl;
        plik2 << "Liczba linii: " << to_string(linie) << endl;
        plik2 << "Liczba slow: " << to_string(slowa) << endl;
        plik2 << "Liczba znakow: " << to_string(znaki) << endl;
        plik2.close();
        cout << "Wyniki zapisano w: " << wyniki << endl;
    }
		
	}
return 0;	
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
				analiza_szczegolowa(nazwa);
				
							
	}
	
	return 0;
}
