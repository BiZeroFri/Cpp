#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

string s1;

int slptime;
string any;

int main()
{
	fstream plik1;
	
	plik1.open("rock.txt");
	
	cout <<"press any key to start";
	cin >> any;
	
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
			
			slptime =111*s1.length();
			
			
			Sleep(slptime);
			
			
			cout << s1<<" ";
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
