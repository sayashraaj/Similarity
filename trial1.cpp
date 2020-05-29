#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main () {
string s;
string sTotal;

ifstream in;
in.open("/Users/sayash/Desktop/comp_prog/Levenshtein/file.txt");

while(!in.eof()) {
	getline(in, s);
	sTotal += s;

}

cout << sTotal;

in.close();
return 0;
}
