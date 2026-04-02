#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void add()
{
	struct str{
		string date;
		string cat;
		string desc;
		double amount;
	};
	
	str obj;
	
	cout<<"Data (YYYY-MM-DD): ";
	cin >> obj.date;
	
	cout<<"Kategoria: ";
	cin >> obj.cat;
	cin.ignore();
	
	cout<<"Opis: ";
	getline(cin, obj.desc);
	
	cout<<"Ile: ";
	cin>>obj.amount;
	
	ofstream file("wydatki.txt", ios::app);
	
	if(file.is_open()){
		file<<obj.date<<";"<<obj.cat<<";"<<obj.desc<<";"<<obj.amount<<"\n";
		file.close();
		cout<<"Zapisano"<<endl;
	}
		
	
}

void show()
{
	ifstream file("wydatki.txt");
	
	string line;
	
	cout<<"Lista wydatkow: "<<endl;
	
	while(getline(file, line))
	{
		stringstream ss(line);
		string date, cat, desc, amount;
		
		getline(ss, date, ';');
		getline(ss, cat, ';');
		getline(ss, desc, ';');
		getline(ss, amount, ';');
		
		
		cout<<date<<" | "<<cat<<" | "<<desc<<" | "<<amount<<" zl\n";
	}
	
	cout<<endl;
	
	file.close();
}

void summary()
{
	ifstream file("wydatki.txt");
	
	string line;
	double total=0;
	double amo=0;
	
	while(getline(file,line))
	{
		stringstream ss(line);
		string date, cat, desc, amount;
		
		getline(ss, date, ';');
		getline(ss, cat, ';');
		getline(ss, desc, ';');
		getline(ss, amount, ';');
		
		stringstream convert(amount);
		convert >> amo;
		
		total += amo;		
		
	}
	
	file.close();
	cout<<"Suma wydatkow: "<<total<<endl;
	cout<<endl;
	
}

int main(){
	
	int menu;
	
	while(true)
	{
		cout<<"Monitor wydatkow"<<endl;
		cout<<"1. Dodaj wydatek"<<endl;
		cout<<"2. Pokaz wydatki"<<endl;
		cout<<"3. Pokaz podsumowanie"<<endl;
		cout<<"4. Wyjdz"<<endl;
	
		cin>>menu;
		cin.ignore();
		
		switch(menu){
			case 1:
				add();
			break;
			
			case 2:
				show();
			break;
			
			case 3:
				summary();
			break;
			
			case 4:
				return 0;	
			break;
		}
	}
	

}
