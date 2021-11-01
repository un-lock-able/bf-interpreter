#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int numOfByte = 20;
char paper[numOfByte] = {0};
char ptr = 0;
int filePos = 0;
string prog;
ifstream infile;

void readProgrameFile(){
	string curline;
	while(getline(infile, curline)){
		prog += curline;
	}
}

void removeSpace(){
	int index = 0;
	int last = prog.length();
	if(!prog.empty()){
		while (index < last){
			if (prog[index] == ' ' || prog[index] == '\t'){
				prog.erase(index,1);
			}
			else{index++;}
		}
	}
}

int main(int argc, char* argv[]){
	infile.open(argv[1]);
	if (!infile){
		cout<<"File not found!";
		return 1;
	}
	readProgrameFile();
	infile.close();
	removeSpace();
	while(ptr<numOfByte && ptr>=0 && filePos<prog.length() && filePos>=0){
		switch (prog[filePos]){
			case '>':
				++ptr;
				break;
			case '<':
				--ptr;
				break;
			case '+':
				paper[ptr]++;
				break;
			case '-':
				paper[ptr]--;
				break;
			case '.':
				cout << paper[ptr];
				break;
			case ',':
				//cout << "\nWAITING FOR INPUT:"<<endl;
				cin >> paper[ptr];
				break;
			case '[':
				if (!paper[ptr]){
					int rightNeeded = 1;
					while (rightNeeded > 0){
						filePos++;
						if (filePos>=prog.length()){cout<<"Missing ']'"<<endl;break;}
						if (prog[filePos]=='['){rightNeeded++;}
						else if (prog[filePos]==']'){rightNeeded--;}
					}
				}
				break;
			case ']':
				if (paper[ptr]){
					int leftNeeded = 1;
					while (leftNeeded > 0){
						filePos--;
						if (filePos < 0){cout<<"Missing '['"<<endl;filePos--;break;}
						if (prog[filePos]==']'){leftNeeded++;}
						else if (prog[filePos]=='['){leftNeeded--;}
					}
				}
				break;
			default:
				break;
		}
		filePos++;
	}
	return 0;
}