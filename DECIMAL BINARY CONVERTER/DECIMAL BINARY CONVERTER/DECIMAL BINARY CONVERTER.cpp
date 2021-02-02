// DECIMAL BINARY CONVERTER.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>
#include <string> 

using namespace std;
/*Decimal <---> Binary Converter 
  Binary code IEEE754
*/

string binarInt(int n){
    string binary;
    while (n != 0) {
        binary+=(n % 2 == 0 ? "0" : "1");
        n /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}
string fraction(float fractional, int k_prec) {
    string binary;
    while (k_prec--) {
        fractional *= 2;
        int fract_bit = fractional;
        if (fract_bit == 1) {
            fractional -= fract_bit;
            binary.push_back(1+'0');
        }
        else
            binary.push_back(0+'0');
    }
    return binary;
}
string dec_to_bin_IEEE754(float dec) {
    int dec_I = abs(dec);
    float dec_F = ((float)abs(dec) - dec_I);

    string bin_exponent = binarInt(dec_I);
    string  bin_mantysa = fraction(dec_F, 23);

    int normalization = (bin_exponent.size() - 1) + 127;
    bin_exponent.erase(0, 1);
    bin_mantysa = bin_exponent + bin_mantysa;
    bin_mantysa.erase(23);
    bin_exponent = binarInt(normalization);

    bitset<32> IEEE754(bin_exponent + bin_mantysa);

    if (dec < 0) {
        IEEE754.set(31, 1);
    }
    return IEEE754.to_string();
}
float bin_IEEE754_to_dec(string & input_bin_numb) {
    string bin_sign, bin_exponent, bin_mantysa;
    bin_sign = input_bin_numb[0];
    bin_exponent = input_bin_numb.substr(1, 8);
    bin_mantysa = input_bin_numb.substr(9);

    bitset<sizeof(bin_exponent)> temp(bin_exponent);
    int exponent = temp.to_ulong();
    exponent = exponent - 127;
    double mantysa = 0;

    for (int i = 0; i < bin_mantysa.size(); i++) {
        mantysa += double(stoi(bin_mantysa.substr(i, 1)) * pow(2, (-(i + 1))));
    }
    mantysa++;

    float L = pow(-1, (stoi(bin_sign))) * mantysa * pow(2, exponent);
     return L;
}
bool is_digits(const string& str)
{
    return str.find_first_not_of("0123456789") == string::npos;
}
bool is_digitsDEC(const string& str)
{
    return str.find_first_not_of("0123456789.") == string::npos;
}

int main() {
    while (true) {
        cout << "Dec, Bin Conversion" << endl;
        cout << "Press 1 to convert Dec ---> Bin IEEE754" << endl;
        cout << "Press 2 to convert Bin IEEE754 ---> Dec" << endl;
        int n;
        cin >> n;
        if (n == 1 || n == 2) {
            if (n == 1) {
                // Converting Floating-Point Decimal to binary32 IEEE754
                cout << "Please enter a decimal number " << endl;
                string  input_dec_numb;
                cin >> input_dec_numb;
                if (is_digitsDEC(input_dec_numb)) {
                    float dec = stof(input_dec_numb);
                    cout << "Dec: " << dec << endl;
                    cout << "Bin in IEEE754:  ";
                    cout << dec_to_bin_IEEE754(dec) << endl;
                }
                else {
                    cout << "You enter no number" << endl;
                }
            }
            else if (n == 2) {
                // Converting binary32 IEEE754 to Floating-Point Decimal
                cout << "Please enter binar number in IEEE754 " << endl;
                string  input_bin_numb;
                cin >> input_bin_numb;
                if (is_digits(input_bin_numb)) {
                    if (input_bin_numb.find_first_not_of("01") == 1) {
                        if (input_bin_numb.size() == 32) {
                            cout << "Dec: " << bin_IEEE754_to_dec(input_bin_numb) << endl;
                        }
                        else {
                            cout << "You enter wrong number" << endl;
                            cout << "In IEEE754 Bin have 32 bits: 1 sign bit, 8 bits for exponent and 23 for mantissa" << endl;
                            cout << "Example: 10111110000000000000000000000000,  it's -0,125" << endl;
                            cout << "Incorect format: 1 01111100 00000000000000000000000 WRONG!!!!!! " << endl;
                            cout << "No white marks betwean numbers!!!" << endl;
                        }
                    }
                    else {
                        cout << "It contains a decimal number" << endl;
                    }
                }
                else {
                    cout << "It's Neither binary nor the decimal number" << endl;
                }
            }
        }
        else {
            cout << "Wrong key" << endl;
        }
    }
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
