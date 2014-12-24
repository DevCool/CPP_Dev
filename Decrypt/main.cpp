#include <iostream>
#include <ios>
#include <fstream>
using namespace std;

int main(int argc,char* argv[])
{
    if(argc != 3) {
        cout << "Cannot continue." << endl
             << "Usage: Decrypt.exe mysource.txt mydestination.txt" << endl;
        return -1;
    }
    ifstream infile;infile.open(argv[1],ios::in | ios::binary);//first file
    if(!infile) {
        cout << "Cannot open file for reading... error!" << endl;
        return -1;
    }
    ofstream outfile;outfile.open(argv[2],ios::out | ios::binary);//second file
    if(!outfile) {
        cout << "Cannot open file for reading... error!" << endl;
        return -1;
    }
    infile.seekg(0,ios::beg);
    int posB=infile.tellg();
    infile.seekg(0,ios::end);
    int posE=infile.tellg();
    int length=posE-posB;
    infile.seekg(0,ios::beg);
    outfile.seekp(0,ios::beg);
    char* a=new char[length];
    infile.read(a,length);
    bool currentBit;unsigned char currentByte;
    for(int i=0;i <length;i++) {
        currentByte=a[i];
        currentBit=currentByte&1;
        currentByte=(currentBit<<7)|(currentByte>>1);
        a[i]=currentByte;
    }
    outfile.write(a,length);
    return 0;
}