#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
/*
    "Abby" Strebel
    CS 1337.001
    Revised 1/28/2021

    Input File Notes:
    - Each line has to have roman numerals XOR arabic numerals
    - The line should start with roman numerals, not arabic numerals
    - There is NO input validation

    Example of a valid file:
                3999 
                5    
XV                   
IX                   
V                    
                205  
                12   

*/

int RomToAr(string rom) {
    int ara=0;
    string roman = rom;
    string tempRom;

    // Get the thousands
    if (roman[0]=='M') { // Checking if the first character is 'M' or 1000+
        for (int x=0; x<3; x++) { // I only deal with numbers 3999 or less
            if (roman[x] != 'M') {
                roman = roman.substr(x); // Take the thousands out of the temp string
                ara = x * 1000; // Add the thousands in
                break;
            }
        }
    }

    // Get the Hundreds
    if (roman[0]=='C') { // Can be 100 - 300, 400, 900
        for (int x=0; x<3; x++) {
            if (roman[x] != 'C') {
                if (roman[x] == 'D') { // 400
                    ara += 400;
                }
                else if (roman[x] == 'M') { // 900
                    ara += 900;
                }
                else { // 100 - 300
                    ara += x * 100; // Add the hundreds in
                }
                roman = roman.substr(x); // Take the hundreds out of the temp string
                break;
            }
        }
    }
    else if (roman[0]=='D') { // Can be 500, 600, 700, 800
        roman = roman.substr(1); // Takes out the 'D'
        ara += 500; // Puts the 500 in
        for (int x=0; x<3; x++) {
            if (roman[x] != 'C') {
                ara += x*100; // Puts in the extra
                roman = roman.substr(x);
            }
        }
    }

    // Get the tens
    if (roman[0]=='X') { // Can be 10 - 30, 40, 90
        for (int x=0; x<3; x++) {
            if (roman[x] != 'X') {
                if (roman[x] == 'L') { // 40
                    ara += 40;
                }
                else if (roman[x] == 'C') { // 90
                    ara += 90;
                }
                else { // 10 - 30
                    ara += x * 10; // Add the tens in
                }
                roman = roman.substr(x); // Take the tens out of the temp string
                break;
            }
        }
    }
    else if (roman[0]=='L') { // Can be 50, 60, 70, 80
        roman = roman.substr(1); // Takes out the 'L'
        ara += 50; // Puts 50 in
        for (int x=0; x<3; x++) {
            if (roman[x] != 'X') {
                ara += x*10; // Gets what is missed
                roman = roman.substr(x);
            }
        }
    }

    // Get the ones
    if (roman[0]=='I') { // Can be 1 - 3, 4, 9
        for (int x=0; x<3; x++) {
            if (roman[x] != 'I') {
                if (roman[x] == 'V') { // 4
                    ara += 4;
                }
                else if (roman[x] == 'X') { // 9
                    ara += 9;
                }
                else { // 1 - 3
                    ara += x; // Add the tens in
                }
                roman = roman.substr(x); // Take the tens out of the temp string
                break;
            }
        }
    }
    else if (roman[0]=='V') { // Can be 5, 6, 7, 8
        roman = roman.substr(1); // Takes out the 'L'
        ara += 5; // Adds 5 in
        for (int x=0; x<3; x++) {
            if (roman[x] != 'V') {
                ara += x; // Adds in the rest
                roman = roman.substr(x);
            }
        }
    }

    return ara;
}

string ArToRom(int num) {
    string rom="";
    int thousands,hundreds,tens,ones;

    // assigns simpler numbers for each place value
    if(num>999) 
        thousands = num/1000;
    if(num>99)
        hundreds = num%1000/100;
    if(num>9)
        tens = num%1000%100/10;
    ones = num%1000%100%10;

    // assigns thousand numeral
    if (thousands > 0 && thousands <= 4) {
        for (int x=1;  x<=thousands; x++) {
            rom += "M";
        }
    }

    // assigns hudreds numeral
    if (hundreds > 0 && hundreds < 4) { // assigns 100 - 300
        for (int x=1; x<=hundreds; x++) {
            rom += "C";
        }
    }
    else if (hundreds == 4) { // assigns special case, 400
        rom += "CD";
    }
    else if (hundreds == 5) { // assigns special case, 500
        rom += "D";
    }
    else if (hundreds == 6) { // assigns special case, 600
        rom += "DC";
    }
    else if (hundreds == 7) { // assigns special case, 700
        rom += "DCC";
    }
    else if (hundreds == 8) { // assigns special case, 800
        rom += "DCCC";
    }
    else if (hundreds == 9) { // assigns special case, 900
        rom += "CM";        
    }
    
    // Assigns 10's
    if (tens > 0 && tens < 4) { // assigns 10 - 30
        for (int c=1; c<=tens; c++) {
            rom += "X";
        }
    }
    else if (tens == 4) { // assigns 40
        rom += "XL";
    }
    else if (tens == 5) { // assigns 50
        rom += "L";
    }
    else if (tens == 6) { // assigns 60
        rom += "LX";
    }
    else if (tens == 7) { // assigns 70
        rom += "LXX";
    }
    else if (tens == 8) { // assigns 80
        rom += "LXXX";
    }
    else if (tens == 9) { // assigns 90
        rom += "XC"; 
    }

    // Assigns 1's
    if (ones > 0 && ones < 4) { // assigns 1 - 3
        for (int c=1; c<=ones; c++) {
            rom += "I";
        }
    }
    else if (ones == 4) { // assigns 4
        rom += "IV";
    }
    else if (ones == 5){ // assigns 5
        rom += "V";
    }
    else if (ones == 6){ // assigns 6
        rom += "VI";
    }
    else if (ones == 7){ // assigns 7
        rom += "VII";
    }
    else if (ones == 8){ // assigns 8
        rom += "VIII";
    }
    else if (ones == 9){ // assigns 9
        rom += "IX";
    }

    // Done!
    return rom;
}

int main() { 
    string fileName = "numbers.txt"; // Name of the file to be opened

    int arabicNum; // Stores arabicNumber
    string romanNum; // Stores romanNumberals

    char cha;
    int pos=0;
    fstream doc; // file stream object
    doc.open(fileName, ios::binary|ios::in|ios::out); // opens file in binary mode, for input and output operations
    int fileIterator=0; // Iterates through file
    if(doc.good()) { // File opened properly
        cout << "File opened\n";

        while(!doc.eof()) { // While not end of file
            cha = (char)doc.peek(); // Check first character of line 
            cout << "First char is: " << cha << ".\n";
            if (isblank(cha)) { // This line in file is Arabic Numerals
                doc.seekg((22*fileIterator)+16, ios::beg); // Move ahead 16 characters
                doc >> arabicNum; // Get arabic number from file
                doc.seekg((22*fileIterator), ios::beg); // Back to begining of line
                string rom=ArToRom(arabicNum); // Convert to Roman
                doc << rom; // Output Roman numeral to file
            }
            else { // This line in file is Roman Numberals
                doc >> romanNum; // Read string
                doc.seekg((22*fileIterator)+16, ios::beg); // Move file pointer ahead (16 - string length) characters
                doc << RomToAr(romanNum);// Convert to Arabic, output Arabic to file
            }
            //file pointer move
            fileIterator++;
            doc.seekg((22*fileIterator),ios::beg);
            doc.peek();
        }
    }
    else {
        cout << "Error - file can't be read"; // File didn't open!
    }
    doc.close();
    return 0;                                
}