#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void show_list()
{
	ifstream file("list.txt");
	
	string line;
	int num = 1;
	
	while (getline(file, line)){
		cout<<num<<". "<<line<<endl;
		num++;
	}
	num=0;
	
	file.close();
}

void add_task()
{
	ofstream file("list.txt", ios::app);
	
	string newtask;
	
	cout << "Wprowadz nowe zadanie"<< endl;
	getline(cin, newtask);
	
	file << newtask<<endl;
	
	cout <<"Zapisano"<<endl;
	
	file.close();
}

void delete_task()
{
	vector<string> tasks;
	string line;
	
	ifstream in("list.txt");
	
	while(getline(in, line))
		tasks.push_back(line);
		
	in.close();
	
	if(tasks.empty())
	{
		cout << "Lista zadañ jest pusta." << endl;
        return;
	}
	
	cout <<"Podaj numer zadania do usuniecia"<<endl;
	int choice;
	cin >> choice;
	cin.ignore();
	
	if(choice < 1 || choice > tasks.size()){
		cout << "Nieprawidlowy numer"<<endl;
		return;
	}
	
	tasks.erase(tasks.begin() + choice - 1);
	
	ofstream out("list.txt");
	for (size_t i = 0; i < tasks.size();i++)
	out << tasks[i] << endl;
	
	cout << "Zadanie usuniete"<<endl;
	
	out.close();
}

int main()
{
	int choose;
	
	while(true){
	
	cout << endl <<"Wybierz co chcesz zrobic" << endl;
	cout << "1. Wyswietl liste zadan"<<endl;
	cout << "2. Dodaj nowe zadanie"<<endl;
	cout << "3. Usun zadanie"<<endl;
	cout << "4. Zakoncz"<<endl;
	
	cin >> choose;
	cout<<endl;
	cin.ignore();
	
	switch (choose){
		case 1:
			show_list();
		break;
		
		case 2:
			add_task();	
		break;
		
		case 3:
			delete_task();
		break;
		
		case 4:
		return 0;
	}
	}
}


