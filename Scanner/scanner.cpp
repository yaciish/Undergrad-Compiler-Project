#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
ifstream file1;
ofstream file2;
vector <pair<string, string> > reserved_wordTable;
vector <pair<string, string> > delemeter_operatorTable;
vector <pair <string, string> > computing_operatorTable;
vector <pair <string, string> > comparing_operatorTable;
vector < string > symbolTable;
char c;
void tables() {
	reserved_wordTable.push_back(make_pair("RS", "start"));
	reserved_wordTable.push_back(make_pair("RS", "finish"));
	reserved_wordTable.push_back(make_pair("RS", "condition"));
	reserved_wordTable.push_back(make_pair("RS", "loop"));
	reserved_wordTable.push_back(make_pair("RS", "until"));
	reserved_wordTable.push_back(make_pair("RS", "fpoint"));
	reserved_wordTable.push_back(make_pair("RS", "integer"));
	delemeter_operatorTable.push_back(make_pair("dlm", "||"));
	delemeter_operatorTable.push_back(make_pair("dlm", ")"));
	delemeter_operatorTable.push_back(make_pair("dlm", "("));
	delemeter_operatorTable.push_back(make_pair("dlm", ":="));
	delemeter_operatorTable.push_back(make_pair("dlm", "COM"));
	computing_operatorTable.push_back(make_pair("dlm", "SL"));
	computing_operatorTable.push_back(make_pair("dlm", "-"));
	computing_operatorTable.push_back(make_pair("dlm", "+"));
	computing_operatorTable.push_back(make_pair("dlm", "*"));
	comparing_operatorTable.push_back(make_pair("dlm", ">"));
	comparing_operatorTable.push_back(make_pair("dlm", "<"));
	comparing_operatorTable.push_back(make_pair("dlm", ">="));
	comparing_operatorTable.push_back(make_pair("dlm", "<="));
	comparing_operatorTable.push_back(make_pair("dlm", "="));
	comparing_operatorTable.push_back(make_pair("dlm", "<>"));
}
int what_is(char ch) {
	if (48 <= ch && ch <= 57) return 68; //Digit
	if (97 <= ch && ch <= 122 && ch != 120) return 76; //Letter
	if (ch == 120) return 120; //x
	if (ch == 124) return 124; // |
	if (ch == 47) return 47; // /
	if (ch == 58) return 58; // :
	if (ch == 60) return 60; // <
	if (ch == 62) return 62; // >
	if(ch == ' ')return 32; // space
	if(ch == 9) return 9; // tab
	if(ch == 13) return 13; // enter
	return 101; //else
}
int find(string x){
	for(int i = 0; i < symbolTable.size(); i++){
		if((x.compare(symbolTable[i])) == 0){
			return i;
		}
	}
	symbolTable.push_back(x);
	for(int i = 0; i < symbolTable.size(); i++){
		if((x.compare(symbolTable[i])) == 0){
			return i;
		}
	}
}
int look_up_rw(string st){
	for(int i = 0; i < reserved_wordTable.size(); i++){
		if(st.compare(reserved_wordTable[i].second) == 0){
			return i;
		}
	}
	return -1;
}
int look_up_other_tables(string st){
	for(int i = 0; i < delemeter_operatorTable.size(); i++){
		if(st.compare(delemeter_operatorTable[i].second) == 0){
			return i;
		}
	}
	for(int i = 0; i < computing_operatorTable.size(); i++){
		if(st.compare(computing_operatorTable[i].second) == 0){
			return i;
		}
	}
	for(int i = 0; i < comparing_operatorTable.size(); i++){
		if(st.compare(comparing_operatorTable[i].second) == 0){
			return i;
		}
	}
	return -1;
}
void where_is_word (string st){
	//cerr << "here in where_is_word" << endl;
	for(int i = 0; i < delemeter_operatorTable.size(); i++){
		if(st.compare(delemeter_operatorTable[i].second) == 0){
			file2 << "( delemeter operator , " << delemeter_operatorTable[i].second << " )" << endl;
			return;
		}
	}
	for(int i = 0; i < computing_operatorTable.size(); i++){
		if(st.compare(computing_operatorTable[i].second) == 0){
			file2 << "( computing operator , " << computing_operatorTable[i].second << " )" << endl;
			return;
		}
	}
	for(int i = 0; i < comparing_operatorTable.size(); i++){
		if(st.compare(comparing_operatorTable[i].second) == 0){
			//cerr << "inside comparing table." << endl;
			file2 << "( comparing operator , " << comparing_operatorTable[i].second << " )" << endl;
			return;
		}
	}
}

void get_token(char c){
	string word;
	word.clear();
	switch(what_is(c)){
		case(9):{
			//file2 << "tab" << endl;
			return;
		}
		case(13):{
			//file2 << "enter" << endl;
			return;
		}
		case(32):{
			//file2 << "space" << endl;
			return;
		}
		case(58):{
			word += c;
			file1.get(c);
			if(c == '='){
				word += c;
				file2 << "( comparing operator , ASSIGNMENT )" << endl;
				return;
			}
			else{
				file2 << "ERROR  for : ." << endl;
				get_token(c);
				return;
			}
		}
		case(60):{
			word += c;
			file1.get(c);
			if(c == '='){
				word += c;
				file2 << "( comparing operator , LE )" << endl;
				return;	
			}
			if(c == '>'){
				word += c;
				file2 << "( comparing operator , OPP )" << endl;
				return;
			}
			else{
				file2 << "( comparing operator , L )" << endl;
				get_token(c);
				return;
			}	
		}
		case(62):{
			word += c;
			file1.get(c);
			if(c == '='){
				word += c;
				file2 << "( comparing operator , GE )" << endl;
				return;
			}
			else{
				file2 << "( comparing operator , G )" << endl;
				get_token(c);
				return;
			}
		}
		case(124):{
			word += c;
			file1.get(c);
			if(c == '|'){
				word += c;
				file2 << "( delemeter operator , END )" << endl;
				return;
			}
			else{
				file2 << "ERROR for | ." << endl;
				get_token(c);
				return;
			}	
		}
		case(47):{
			word += c;
			file1.get(c);
			if(c == '/'){
				while(c != '\n'){
					//cerr << "47" << endl;
					//cerr << "c: " << c << endl;
					file1.get(c);
				}
				return;
			}
			else{
				file2 << "( computing operator , SL )" << endl;
				get_token(c);
				return;
			}
		}
		case(76):{
			word += c;
			file1.get(c);
			if(isalpha(c)){
				while(isalpha(c)){
					//cerr << "76" << endl;
					word += c;
					//cerr << "word in case 76: " << word << endl;
					file1.get(c);
				}
				if(isdigit(c)){
					//file2 << "ERROR" << endl;
					while(c != ' '){
						file1.get(c);
					}
					return;
				}
				else{
					if(look_up_rw(word) != -1){
						//cerr << "word in case 76/ look up: " << word << endl;
						file2 << "( reserved word , " <<  reserved_wordTable[look_up_rw(word)].second << " )" << endl;	
						get_token(c);
						return;
					}
					else{
						file2 << "ERROR" << endl;
						get_token(c);
						return;
					}
				}
			}
			if(isdigit(c)){
				file2 << "ERROR" << endl;
				while(c != ' '){
					//cerr << "76/2" << endl;
					file1.get(c);
				}
				return;
			}
			file2 << "ERROR" << endl;
			get_token(c);
			return;
		}
		case(120):{
			word += c;
			file1.get(c);
			if(isdigit(c)){
				word += c;
				file1.get(c);
				if(isdigit(c)){
					word += c;
					file1.get(c);
					if(c == ' '){
						file2 << "( ID , " << find(word) << " )"<< endl;
						return;
					}
					if(isdigit(c) || isalpha(c)){
						file2 << " ERROR" << endl;
						while(c != ' '){
							//cerr << "120" << endl;
							file1.get(c);
						}
						return;
					}
					file2 << "( ID , " << find(word) << " )"<< endl;
					get_token(c);
					return;
				}
				if(isalpha(c)){
					file2 << "ERROR" << endl;
					while(c != ' '){
						//cerr << "120/2" << endl;
						file1.get(c);
					}
					return;
				}
				file2 << "ERROR" << endl;
				get_token(c);
				return;
			}
			if(isalpha(c)){
				while(c != ' '){
					//cerr << " 120 /3 " << endl;
					file1.get(c);
				}
				file2 << "ERROR" << endl;
				return;
			}
			file2 << "ERROR" << endl;
			get_token(c);
			return;			
		}
		case(68):{
			word += c;
			file1.get(c);
			if(isdigit(c)){
				while(isdigit(c)){
					//cerr << "68" << endl;
					word += c;
					file1.get(c);
				}
				if(c == ' '){
					//cerr << "this is an integer." << endl;
					file2 << "( integer , " << stoi(word) << " )" << endl;
					return;
				}
				if(c == '.'){
					word += c;
					file1.get(c);
					if(c == ' ' || c == '\n'){
						file2 << "ERROR" << endl;
						return;
					}
					if(isdigit(c)){
						while(isdigit(c)){
							//cerr << "68 / 2" << endl;
							word += c;
							file1.get(c);
						}
						if(c == ' '){
							file2 << "( fpoint , " << stod(word) << " )" << endl;
							return;
						}
						if(c == '.'){
							file2 << "ERROR" << endl;
							while(c != ' '){
								//cerr << "68 / 3" << endl;
								file1.get(c);
							}
							return;
						}
						file2 << "( fpoint , " << stod(word) << " )" << endl;
						get_token(c);
						return;
					}
					if(c == '.'){
						file2 << "ERROR" << endl;
						while(c != ' '){
							//cerr << "68/4" << endl;
							file1.get(c);
						}
						return;
					}
					file2 << "ERROR" << endl;
					get_token(c);
					return;
				}
					file2 << "( integer , " << stoi(word) << " )" << endl;
					get_token(c);
					return;
				}
				if(c == '.'){
					word += c;
					file1.get(c);
					if(c == ' ' || c == '\n'){
						file2 << "ERROR" << endl;
						return;
					}
					if(isdigit(c)){
						while(isdigit(c)){
							//cerr << "ergerg" << endl;
							word += c;
							file1.get(c);
						}
						if(c == ' '){
							file2 << "( fpoint , " << stod(word) << " )" << endl;
							return;
						}
						if(c == '.'){
							file2 << "ERROR" << endl;
							while(c != ' '){
								//cerr << "inja" << endl;
								get_token(c);
							}
							return;
						}
						file2 << "( fpoint , " << stod(word) << " )" << endl;
						get_token(c);
						return;
					}
					if(c == '.'){
						file2 << "ERROR" << endl;
						while(c != ' '){
							//cerr << "here" << endl;
							file1.get(c);
						}
						return;
					}
					file2 << "ERROR" << endl;
					get_token(c);
					return;
				}
				if(c == ' '){
					file2 << "( integer , " << stoi(word) << " )" << endl;
					return;
				}
				if(isalpha(c)){
					file2 << "ERROR" << endl;
					while(c != ' '){
						//cerr << "hereee" << endl;
						file1.get(c);
					}
					return;
				}
				file2 << "( integer , " << stoi(word) << " )" << endl;
				get_token(c);
				return;
			}
			case(101):{
				word += c;
				//cerr << "the word is: \n |" << word << "|" << endl;
				if(c == '\t' || c == '\n' || c == ' '){
					//cerr << "1st" << endl;
					return;
				}
				if(look_up_other_tables(word) == -1){
					//file2 << "ERRORR" << endl;
					//cerr << "2nd" << endl;
					return;
				}
				else{
					//cerr << "inside the last else." << endl;
					where_is_word(word);
					return;
				}
				
			}
	}

}
int main() {
	file1.open("scanner_input.txt"); //In the "scanner_input.txt" file, after the last character, type in "enter" or "space". There must be an empty line or a space in order to exit the file.
	file2.open("scanner_output.txt");
	tables();
	while (file1.get(c)) {
		//cerr << c << endl;
		get_token(c);
	}
	return 0;
}
