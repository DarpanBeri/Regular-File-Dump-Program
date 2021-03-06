/*********************************************************************
 Name: Zach Selchau
 File: xbd.cpp
 Notes: The sourcecode file containing the functions and code required to run a hex/binarydump program.



 Name: Darpan Beri
 File: xbd.cpp
  Notes: The sourcecode file containing the functions and code required to run a hex/binarydump program.
**********************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "xbd.hpp"


using namespace std;

int binaryToDecimal(string binaryString){

    double sum = 0;
    reverse(binaryString.begin(), binaryString.end());

    for(int i=0; i<binaryString.length(); i++)
        if(binaryString[i] == '1'){
            sum += pow(2.0, (double)i);
        }
    return (int)sum;    
}

string binaryToAscii(string bin){

    const int dec = binaryToDecimal(bin);
    char noPanic;

    if(dec < 127 && dec > 31) {noPanic=static_cast<char>(dec);}
    else return ".";

    return string(1, noPanic);
    
}

string decimalToHex(int num){
    stringstream ss;
    ss << hex << num;
    return ss.str();
}

string decimalToBinary(int num){
	string binStr = "";
    string numStr = decimalToHex(num);

    if(numStr.length()==1)numStr = "0" + numStr;

    if(strcmp(numStr.c_str(), "ffffffff")==0) return "";

    for(int i=0; i<numStr.length(); i++){
        if(numStr[i]=='0')binStr.append("0000");
        if(numStr[i]=='1')binStr.append("0001");
        if(numStr[i]=='2')binStr.append("0010");
        if(numStr[i]=='3')binStr.append("0011");
        if(numStr[i]=='4')binStr.append("0100");
        if(numStr[i]=='5')binStr.append("0101");
        if(numStr[i]=='6')binStr.append("0110");
        if(numStr[i]=='7')binStr.append("0111");
        if(numStr[i]=='8')binStr.append("1000");
        if(numStr[i]=='9')binStr.append("1001");
        if(numStr[i]=='a'||numStr[i]=='A')binStr.append("1010");
        if(numStr[i]=='b'||numStr[i]=='B')binStr.append("1011");
        if(numStr[i]=='c'||numStr[i]=='C')binStr.append("1100");
        if(numStr[i]=='d'||numStr[i]=='D')binStr.append("1101");
        if(numStr[i]=='e'||numStr[i]=='E')binStr.append("1110");
        if(numStr[i]=='f'||numStr[i]=='F')binStr.append("1111");
    }	

	return binStr;
}

string asciiToBinary(string str){
    string bin = "";
	int strLength = str.length();

	for (int i = 0; i < strLength; ++i)
	{
		string cBin = decimalToBinary(int(str[i]));
		bin += cBin;
	}

	return bin;
}

string binaryToHex(string binaryString){
    string hexString = "";

    for(int i=0; i<2; i++){

        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "0000")== 0) hexString.append("0");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "0001")== 0) hexString.append("1");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "0010")== 0) hexString.append("2");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "0011")== 0) hexString.append("3");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "0100")== 0) hexString.append("4");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "0101")== 0) hexString.append("5");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "0110")== 0) hexString.append("6");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "0111")== 0) hexString.append("7");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "1000")== 0) hexString.append("8");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "1001")== 0) hexString.append("9");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "1010")== 0) hexString.append("A");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "1011")== 0) hexString.append("B");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "1100")== 0) hexString.append("C");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "1101")== 0) hexString.append("D");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "1110")== 0) hexString.append("E");
        if(strcmp(binaryString.substr(i*4, 4).c_str(),  "1111")== 0) hexString.append("F");
        
    }

    return hexString;
}

string asciiToHex(string asciiString){
    return(binaryToHex(asciiToBinary(asciiString)));
}

string decimalToAddress(int num){
    string hexIndex = decimalToHex(num);
    while(hexIndex.length() < 7) hexIndex.insert(0, "0");
    return hexIndex;
}

string addSpacesToBinary(string binary){
    binary.append("  ");
    binary.insert(40," ");
    binary.insert(32," ");
    binary.insert(24," ");
    binary.insert(16," ");
    binary.insert(8," ");
    return binary;
}

string addSpacesToHex(string hex){
    hex.append("  ");
    hex.insert(28," ");
    hex.insert(24," ");
    hex.insert(20," ");
    hex.insert(16," ");
    hex.insert(12," ");
    hex.insert(8," ");
    hex.insert(4," ");
    return hex;
}

int main(int argc, char* argv[]){

    bool isOutBinary = false;       //Hex format currently
    bool isFileBinary = true;       //Binary format currently
    int fileArgIndex = 2;           //Binary format currently
    string fullText = "";
    string asciiText = "";
    string hexText = "";
    string binaryText = "";

    //First check for args
    if(strcmp(argv[1], "-b") == 0)isOutBinary = true;         //Change format to binary
    else fileArgIndex = 1;           //Change format to hex

    //Second create ifstream and check if file is a binary file
    string fileName(argv[fileArgIndex]);
    FILE *fp;
    int c = 0;

    fp = fopen(argv[fileArgIndex], "r");
    while(!feof(fp)){
        c = fgetc(fp);
        fullText.append(decimalToBinary(c));
    }
    fclose(fp);

    //Third put ifstream into sstream
    if(true){
        //Fifth read file and convert
        int chunkLength = 0;    //Counts chars in chuck
        int charPointer = 0;    //Points to current char in fullText
        binaryText = fullText;  //fullText is currently in Binary

        while(charPointer < binaryText.length()){
            chunkLength = 0;
            string currChunk = "";
            string hex_string = "";
            string binary_chunk = "";
            string ascii_char = "";
            bool tooShortException = false;

            while(chunkLength < 8){ //Creating the chunk of binary
                if(charPointer >= binaryText.length()){
                    tooShortException=true;
                    break;
                }
                currChunk.append(1, binaryText[charPointer++]);
                chunkLength++;
            }
            if(tooShortException){
                if(chunkLength >= 4){
                    string specialCase = currChunk.substr(0, 4);
                    asciiText.append(".");
                    hexText.append(binaryToHex(specialCase));
                }else break;
            }
            else if(isOutBinary){
                binary_chunk = currChunk;
                // Convert 'binary_chunk' to 'ascii_char'
                ascii_char = binaryToAscii(binary_chunk);
                // Append ascii_char to asciiText
                asciiText.append(ascii_char);
            }
            else{
                binary_chunk = currChunk;
                // Convert 'binary_chunk' to 'hex_string'
                hex_string = binaryToHex(binary_chunk);
                // Append to hexText
                hexText.append(hex_string);
                // Append to asciiText
                asciiText.append(binaryToAscii(binary_chunk));
            }
                
        }

        //Sixth output result

        /* OUTPUT FORMAT: I = Index column, h = hex, b = binary and a = ascii

        if isOutBinary = False;
        // Need a decimal counter for getting correct hex address.
        // 
        IIIIIII hhhh hhhh hhhh hhhh hhhh hhhh hhhh hhhh aaaaaaaaaaaaaaaa

        if isOutBinary = True
        // Need a decimal counter for getting correct hex address.
        IIIIIII bbbbbbbb bbbbbbbb bbbbbbbb bbbbbbbb bbbbbbbb bbbbbbbb aaaaaa */

        if(isOutBinary){
            int address = 0;
            int binaryCounter = 0;
            int asciiCounter = 0;
            string asciiTextClone = asciiText;
            string binaryTextClone = binaryText;
            string binaryLine = ""; // contains 8 char of binary in a word which appears 6 times.
            string asciiLine = ""; // contains 6 chars of ascii
            //Fixing texts so that we dont have any special cases
            for(int i = binaryText.length() % 48; i < 48; i++) {
                if(i==0)break;
                binaryTextClone.append(" "); 
            }
            for(int i = asciiTextClone.length() % 6; i < 6; i++){
                if(i==0)break;
                asciiTextClone.append(" ");
            }

            //For each line
            for(int i = 0; i < asciiTextClone.length(); i += 6){

                binaryLine = addSpacesToBinary(binaryTextClone.substr(i*8, 48));
                asciiLine = asciiTextClone.substr(i, 6);

                //First output <address_>
                cout << decimalToAddress(address) << ": ";

                //Second output binary line
                cout << binaryLine;

                //Third output asciiLine
                cout << asciiLine << endl;

                address += 6;//Incrementing the address
            }

        }else{
            int address = 0;
            int hexCounter = 0;
            int asciiCounter = 0;
            string asciiTextClone = asciiText;
            string hexTextClone = hexText;
            string hexLine = ""; // contains 4 char of hex in a word which appears 8 times.
            string asciiLine = ""; // contains 16 chars of ascii
            // fix text so that we dont have any special cases
            for(int i = hexText.length() % 32; i < 32; i++){
                if(i==0)break; 
                hexTextClone.append(" "); // 8*4 = 32
            }

            for(int i = asciiTextClone.length() % 16; i < 16; i++){
                if(i==0)break;
                asciiTextClone.append(" ");
            }

            for(int i = 0; i < asciiTextClone.length(); i += 16){
                hexLine = addSpacesToHex(hexTextClone.substr(i*2, 32));
                asciiLine = asciiTextClone.substr(i, 16);

                // OUTPUT per line
                cout << decimalToAddress(address) << ":" << " " << hexLine << asciiLine << "\n";
                address += 16;//Incrementing the address
            }

        }

        //cout << asciiText << endl;         //Testing SS
    }
}
