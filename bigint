#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class BigInt {
	private:
		string value; 
		
	public:
		BigInt() {		//domyslny
			value ='0'; 
		}	
		
		BigInt(string val) {	//standardowy
			value = val;	
		}
		
		BigInt(const BigInt& other){	//kopiujacy
			value = other.value;
		}
		
		BigInt& operator=(const BigInt& other)	// =
		{
			if (this != &other)
			{
				value = other.value;
			}
			return *this;
		}
		
		string getValue() const{	//pobieranie wartosci
			return value;
		}
		
		bool operator==(const BigInt& other) const{ // ==
			return value == other.value;
		}
		
		BigInt operator+() const{	//dodatni
			return *this;
		}
		
		BigInt operator-() const{
			if(value == "0") return *this;
			
			if(value[0] == '-'){
				return BigInt(value.substr(1));
			}
			
			return BigInt("-" + value);
		}
		
		
		BigInt operator+(const BigInt& other) const {	//dodawanie
        string str1 = value;
        string str2 = other.value;
        string result = "";

        while (str1.length() < str2.length()) str1 = "0" + str1;	//wyrównanie
        while (str2.length() < str1.length()) str2 = "0" + str2;

        int carry = 0;	 //Przeniesienie

        for (int i = str1.length() - 1; i >= 0; i--) {
            int digit1 = str1[i] - '0'; 	// Zamiana znaku na cyfrę 
            int digit2 = str2[i] - '0';

            int sum = digit1 + digit2 + carry;
            carry = sum / 10;       
            result += (sum % 10) + '0'; 	//Dopisanie jedności do wyniku
        }

        if (carry > 0) {
            result += (carry + '0');	 //to co zostało na końcu
        }

        reverse(result.begin(), result.end());	 //odwracanie
        return BigInt(result);
    }

    
    BigInt operator-(const BigInt& other) const {	//odejmowanie
        string str1 = value;
        string str2 = other.value;
        string result = "";

        while (str1.length() < str2.length()) str1 = "0" + str1;
        while (str2.length() < str1.length()) str2 = "0" + str2;

        int borrow = 0;		//pożyczka

        for (int i = str1.length() - 1; i >= 0; i--) {
            int digit1 = str1[i] - '0';
            int digit2 = str2[i] - '0';

            int sub = digit1 - digit2 - borrow;

            if (sub < 0) {
                sub += 10;
                borrow = 1;	
            } else {
                borrow = 0;
            }

            result += (sub + '0');
        }

        reverse(result.begin(), result.end());

        
        size_t noZero = result.find_first_not_of('0'); 	//usuwanie zer
        if (noZero != string::npos) {
            result = result.substr(noZero);
        } else {
            result = "0"; 	//!były same zera!
        }

        return BigInt(result);
    }

    
    friend ostream& operator<<(ostream& os, const BigInt& obj) { 	// << 
        os << obj.value;
        return os;
    }
};

int main() {
    
    BigInt a;	//domyslny            
    BigInt b("999999999999999999");		//standardowy
    BigInt c("888888888888888888");
    BigInt d = b;	//kopiujacy

    cout << "Konstruktor domyslny (a): " << a << "\n";
    cout << "Konstruktor standardowy (b): " << b << "\n";
    cout << "Konstruktor kopiujacy (d = b): " << d << "\n";

    
    a = c;		//op przypisania
    cout << "Po przypisaniu (a = c): " << a << "\n";

    
    if (b == d) {	//op logiczny
        cout << " (==) b jest rowne d\n";
    }

    
    cout << "Jednoargumentowy +b: " << +b << "\n";		//jednoargumentowe
    cout << "Jednoargumentowy -b: " << -b << "\n";

    
    BigInt suma = b + c;	//dwuargumentowe
    BigInt roznica = b - c;

    cout << "Suma (b + c):     " << suma << "\n";
    cout << "Roznica (b - c):  " << roznica << "\n";

    return 0;
}
