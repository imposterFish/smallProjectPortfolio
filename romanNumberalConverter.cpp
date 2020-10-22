#include <iostream>
#include <string.h>
#include <fstream>
/*
    "Abby" Strebel
    CS 1337.001
*/

using namespace std;

int RomToAr(string rom)
{
    int arab=0;
    for (int index=0; index < rom.length(); index++) //loops
    {
        if(rom[index]==' ')                                //vv goes through the letters and assigns the correct arabic number
            arab+=0;
        else if (rom[index] == 'M')
            arab += 1000;
        else if (rom[index] == 'D')
            arab += 500;
        else if (rom[index] == 'C' && (rom[index+1] == 'M' || rom[index+1] == 'D'))
            arab -= 100;
        else if (rom[index] == 'C')
            arab += 100;
        else if (rom[index] == 'L')
            arab += 50;
        else if (rom[index] == 'X' && (rom[index+1] == 'L' || rom[index+1] == 'C'))
            arab -= 10;
        else if (rom[index] == 'X')
            arab += 10;
        else if (rom[index] == 'V')
            arab += 5;
        else if (rom[index] == 'I' && (rom[index+1] == 'V' || rom[index+1] == 'X'))
            arab -= 1;
        else if (rom[index] == 'I')
            arab += 1;
    }
    return arab;

}

string ArToRom(int num)
{
    string rom="";

    int thousands,hundreds,tens,ones;

    if(num>999)                         //vvv  assigns simpler numbers for each place value
        thousands = num/1000;
    if(num>99)
        hundreds = num%1000/100;
    if(num>9)
        tens = num%1000%100/10;
    ones = num%1000%100%10;             //^^^

    if (thousands > 0 && thousands <= 4){  //assigns thousand numberal
        for (int x=1;  x<=thousands; x++)
        {
            rom += "M";
            }
    }

    if (hundreds > 0 && hundreds < 4){    //assigns houdreds numberal for the letter c
        for (int x=1; x<=hundreds; x++){
            rom += "C";
        }
    }
    else if (hundreds == 4){             //assigns special case 400
        rom += "CD";
    }
    else if (hundreds == 5){           //assigns special case 500
        rom += "D";
    }
    else if (hundreds > 5 && hundreds < 9){ //
        for (int x=6; x<=hundreds; x++){
            rom += "C";
            }
    }
    else
    {
        rom += "CM"; //900               //
    }

    if (tens > 0 && tens < 4){
        for (int c=1; c<=tens; c++)  //10's
        {
            rom += "X";
        }
    }
    else if (tens == 4)
    {
        rom += "XL";         //40
    }
    else if (tens == 5)
    {
        rom += "L";             //50
    }
    else if (tens > 5 && tens< 9){
        for (int x=6; x<=tens; x++)  //60 70 80 numberals
        {
            rom += "X";
        }
    }
    else
    {
        rom += "XC"; //90
    }

    if (ones > 0 && ones < 4)
    {
        for (int c=1; c<=ones; c++) // 1 2 or 3
        {
            rom += "I";
        }
    }
    else if (ones == 4){ //4
        rom += "IV";
    }
    else if (ones == 5){ //5
        rom += "V";
    }
    else if (ones > 5 && ones < 9) //6,7,8 but ads a v ahead of it so its like
    {
        for (int v=6; v<=ones; v++)
        {
            rom += "I";
        }
    }
    else
    {
        rom += "IX";//9
    }

    return rom;

}

int main()
{
    char cha=' ';
    int pos=0;
    fstream doc; // file stream object
    doc.open("numbers.txt",ios::binary|ios::in|ios::out); //opens file in binaaary
    int numberer=0;
    if(doc.good())//If file opens properly
    {
        cout << "Good\n";
        while(!doc.eof())//While not EOF
        {
            //cout << "test\n";
            //cout << numberer << "numberer\n";
            //doc.seekp(pos);//pos = ftell(doc); //Get current file position
            cha = (char)doc.peek();//Check first character of line (peek)
            //cout << cha << endl;
            if (cha == ' ')
            {
                //cout << "arabic\n";
                doc.seekg((22*numberer)+16, ios::beg);//Move ahead 16 characters
                int numb;
                doc >> numb;//doc.get(numb);//get number
                doc.seekg((22*numberer), ios::beg);//bak to begining
                string rom=ArToRom(numb);//Convert to Roman
                doc << rom; //Output Roman numeral to file
                //doc << rom;
            }
            else
            {
                //cout << "roman\n";
                string ara = "";//cout >> "poop";
                doc >> ara;//Read string
                int araba = RomToAr(ara);//Convert to Arabic
                doc.seekg((22*numberer)+16, ios::beg);//Move file pointer ahead (16 - string length) characters
                doc << araba;//Output Arabic to file
            }
            //file pointer move
            numberer++;
            doc.seekg((22*numberer),ios::beg);
            doc.peek();
        }
    }
    else
        cout << "error"; // <<returns error to consol if the file didnt work
    return 0;                                                                                                           //Why did the programer quit his job?
}                                                                                                                       //'Cuz he didnt get arrays
