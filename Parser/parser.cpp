#include<iostream>
#include<stack>
#include<fstream>
#include <vector>
using namespace std;
const int MAX = 60;
int token_index = 0;
int k = 0;
string input_string;
stack <string> stk;
pair<string, int> mau[MAX][MAX];
vector <int> dollar_indexes;
void table() {
	mau[0][1] = make_pair("(dlm,pl)", 0);
	mau[0][2] = make_pair("(dlm,p)", 0);
	mau[0][3] = make_pair("(RS,until)", 0);
	mau[0][4] = make_pair("(RS,loop)", 0);
	mau[0][5] = make_pair("(dlm,<)", 0);
	mau[0][6] = make_pair("(dlm,>)", 0);
	mau[0][7] = make_pair("(dlm,=)", 0);
	mau[0][8] = make_pair("(dlm,<=)", 0);
	mau[0][9] = make_pair("(dlm,>=)", 0);
	mau[0][10] = make_pair("(dlm,<>)", 0);
	mau[0][11] = make_pair("(RS,finish)", 0);
	mau[0][12] = make_pair("(RS,start)", 0);
	mau[0][13] = make_pair("(RS,condition)", 0);
	mau[0][14] = make_pair("(fpoint,)", 0);
	mau[0][15] = make_pair("(integer,)", 0);
	mau[0][16] = make_pair("(id,)", 0);
	mau[0][17] = make_pair("(dlm,/)", 0);
	mau[0][18] = make_pair("(dlm,*)", 0);
	mau[0][19] = make_pair("(dlm,-)", 0);
	mau[0][20] = make_pair("(dlm,+)", 0);
	mau[0][21] = make_pair("(dlm,||)", 0);
	mau[0][22] = make_pair("(dlm,:=)", 0);
	mau[0][23] = make_pair("(RS,fpoint)", 0);
	mau[0][24] = make_pair("(RS,integer)", 0);
	mau[0][25] = make_pair("#", 0);

	mau[1][0] = make_pair("S'", 0);
	mau[2][0] = make_pair("STMT", 0);
	mau[3][0] = make_pair("S1", 0);
	mau[4][0] = make_pair("S5", 0);
	mau[5][0] = make_pair("S4", 0);
	mau[6][0] = make_pair("S6", 0);
	mau[7][0] = make_pair("B", 0);
	mau[8][0] = make_pair("E", 0);
	mau[9][0] = make_pair("A", 0);
	mau[10][0] = make_pair("A1", 0);
	mau[11][0] = make_pair("D", 0);
	mau[12][0] = make_pair("S2", 0);
	mau[13][0] = make_pair("S7", 0);
	mau[14][0] = make_pair("OP", 0);
	mau[15][0] = make_pair("S3", 0);
	mau[16][0] = make_pair("(dlm,pl)", 0);
	mau[17][0] = make_pair("(dlm,p)", 0);
	mau[18][0] = make_pair("(RS,until)", 0);
	mau[19][0] = make_pair("(RS,loop)", 0);
	mau[20][0] = make_pair("(dlm,<)", 0);
	mau[21][0] = make_pair("(dlm,>)", 0);
	mau[22][0] = make_pair("(dlm,=)", 0);
	mau[23][0] = make_pair("(dlm,<=)", 0);
	mau[24][0] = make_pair("(dlm,>=)", 0);
	mau[25][0] = make_pair("(dlm,<>)", 0);
	mau[26][0] = make_pair("(RS,finish)", 0);
	mau[27][0] = make_pair("(RS,start)", 0);
	mau[28][0] = make_pair("(RS,condition)", 0);
	mau[29][0] = make_pair("(fpoint,)", 0);
	mau[30][0] = make_pair("(integer,)", 0);
	mau[31][0] = make_pair("(id,)", 0);
	mau[32][0] = make_pair("(dlm,/)", 0);
	mau[33][0] = make_pair("(dlm,*)", 0);
	mau[34][0] = make_pair("(dlm,-)", 0);
	mau[35][0] = make_pair("(dlm,+)", 0);
	mau[36][0] = make_pair("(dlm,||)", 0);
	mau[37][0] = make_pair("(dlm,:=)", 0);
	mau[38][0] = make_pair("(RS,fpoint)", 0);
	mau[39][0] = make_pair("(RS,integer)", 0);
	mau[40][0] = make_pair("#", 0);

	for (int i = 1; i <= 40; i++) {
		for (int j = 1; j <= 25; j++) {
			mau[i][j] = make_pair("NULL", -1);
		}
	}
	mau[1][4] = make_pair("$STMT$#", 1);
	mau[1][13] = make_pair("$STMT$#", 1);
	mau[1][16] = make_pair("$STMT$#", 1);
	mau[1][23] = make_pair("$STMT$#", 1);
	mau[1][24] = make_pair("$STMT$#", 1);

	mau[2][3] = make_pair("$epsilon", 33);
	mau[2][4] = make_pair("$S3", 4);
	mau[2][11] = make_pair("$epsilon", 33);
	mau[2][13] = make_pair("$S2", 3);
	mau[2][16] = make_pair("$(id,)$S4", 5);
	mau[2][23] = make_pair("$S1", 2);
	mau[2][24] = make_pair("$S1", 2);
	mau[2][25] = make_pair("$epsilon", 33);

	mau[3][23] = make_pair("$(RS,fpoint)$(id,)$S5", 6);
	mau[3][24] = make_pair("$(RS,integer)$(id,)$S5", 7);

	mau[4][21] = make_pair("$(dlm,||)", 8);
	mau[4][22] = make_pair("$S4", 9);

	mau[5][22] = make_pair("$(dlm,:=)$S6", 32);

	mau[6][2] = make_pair("$B$(dlm,||)", 10);
	mau[6][14] = make_pair("$B$(dlm,||)", 10);
	mau[6][15] = make_pair("$B$(dlm,||)", 10);
	mau[6][16] = make_pair("$B$(dlm,||)", 10);

	mau[7][2] = make_pair("$A$E", 11);
	mau[7][14] = make_pair("$A$E", 11);
	mau[7][15] = make_pair("$A$E", 11);
	mau[7][16] = make_pair("$A$E", 11);

	mau[8][1] = make_pair("$epsilon", 14);
	mau[8][5] = make_pair("$epsilon", 14);
	mau[8][6] = make_pair("$epsilon", 14);
	mau[8][7] = make_pair("$epsilon", 14);
	mau[8][8] = make_pair("$epsilon", 14);
	mau[8][9] = make_pair("$epsilon", 14);
	mau[8][10] = make_pair("$epsilon", 14);
	mau[8][19] = make_pair("$(dlm,-)$A$E", 13);
	mau[8][20] = make_pair("$(dlm,+)$A$E", 12);
	mau[8][21] = make_pair("$epsilon", 14);

	mau[9][2] = make_pair("$D$A1", 15);
	mau[9][14] = make_pair("$D$A1", 15);
	mau[9][15] = make_pair("$D$A1", 15);
	mau[9][16] = make_pair("$D$A1", 15);

	mau[10][1] = make_pair("$epsilon", 18);
	mau[10][5] = make_pair("$epsilon", 18);
	mau[10][6] = make_pair("$epsilon", 18);
	mau[10][7] = make_pair("$epsilon", 18);
	mau[10][8] = make_pair("$epsilon", 18);
	mau[10][9] = make_pair("$epsilon", 18);
	mau[10][10] = make_pair("$epsilon", 18);
	mau[10][17] = make_pair("$(dlm,/)$D$A1", 17);
	mau[10][18] = make_pair("$(dlm,*)$D$A1", 16);
	mau[10][19] = make_pair("$epsilon", 18);
	mau[10][20] = make_pair("$epsilon", 18);
	mau[10][21] = make_pair("$epsilon", 18);

	mau[11][2] = make_pair("$(dlm,p)$B$(dlm,pl)", 19);
	mau[11][14] = make_pair("$(fpoint,)", 22);
	mau[11][15] = make_pair("$(integer,)", 21);
	mau[11][16] = make_pair("$(id,)", 20);

	mau[12][13] = make_pair("$(RS,condition)$(dlm,p)$S7$(dlm,pl)$(RS,start)$STMT$(RS,finish)", 23);

	mau[13][2] = make_pair("$B$OP$B", 24);
	mau[13][14] = make_pair("$B$OP$B", 24);
	mau[13][15] = make_pair("$B$OP$B", 24);
	mau[13][16] = make_pair("$B$OP$B", 24);

	mau[14][5] = make_pair("$(dlm,<)", 26);
	mau[14][6] = make_pair("$(dlm,>)", 25);
	mau[14][7] = make_pair("$(dlm,=)", 29);
	mau[14][8] = make_pair("$(dlm,<=)", 28);
	mau[14][9] = make_pair("$(dlm,>=)", 27);
	mau[14][10] = make_pair("$(dlm,<>)", 30);

	mau[15][4] = make_pair("$(RS,loop)$STMT$(RS,until)$(dlm,p)$S7$(dlm,pl)", 31);

	

	for (int i = 16; i <= 40; i++) {
		for (int j = 1; j <= 25; j++) {
			if (j == (i - 15)) {
				mau[i][j] = make_pair("pop", 0);
			}
		}
	}
	mau[40][25] = make_pair("accept", 0);

}
string get_token( ){
	k = input_string.find(")", token_index );
	//cerr << "k in function :" << k <<endl;
	string current_string = input_string.substr(token_index, k - token_index + 1);
	//cerr << "current_string : "<< current_string <<endl;
	token_index = k + 1;	
	//cerr << "token_index : "<< token_index<<endl;
	return current_string;
}
string look_up_table(string stack_top, string current_string){
	int col, row;
	for (int i = 1; i <= 40; i++) {
		if (mau[i][0].first.compare(stk.top()) == 0){
			row = i;
			//cerr << "here" << endl;
			//cerr << "row" << row << endl;
			break;
		}
	}
	for (int i = 1; i <= 25; i++) {
		if (mau[0][i].first.compare(current_string) == 0) {
			col = i;
			//cerr << "here" << endl;
			//cerr << "col" << col << endl;
			break;
		}
	}
	//cerr << "mau : " << mau[row][col].first << endl;
	return mau[row][col].first;
}
string algo(string stack_top, string current_string){
	string grammar_rule = look_up_table(stack_top, current_string);
	//cerr << "grammar_rule: " << grammar_rule << endl;
	if (grammar_rule.compare("pop") == 0){
		return "pop";
	}
	else if (grammar_rule.compare("accept") == 0 ){
		return "accepted";
	}
	else if (grammar_rule.compare("NULL") == 0){
		return "ERROR";
	}
	else {
		while (stack_top.compare(current_string) != 0 ){
			stk.pop();
			for (int i = 0; i < grammar_rule.size(); i++) {
				if(grammar_rule[i] == '$'){
					//cerr << dollar_indexes.size() << endl;
					dollar_indexes.push_back(i);
					//cerr <<"i :" << i << endl;
				}
			}
			dollar_indexes.push_back(grammar_rule.size());
			//cerr << dollar_indexes.size() << endl;
			/*for (int i = 0 ;i < dollar_indexes.size() ; i++){
				cerr << "dollar_indexes: " << dollar_indexes[i] << " ";
			}
			cerr << endl;*/
			for (int i = dollar_indexes.size() - 1; i > 0; i--){
				//cerr << "i " << i << endl;
				string sub_push = grammar_rule.substr(dollar_indexes[i - 1] + 1, (dollar_indexes[i] - dollar_indexes[i - 1] )- 1 );
				if(sub_push.compare("epsilon") != 0)
					stk.push(sub_push);
				//cerr << stk.top() << endl;
				//cerr << "i " << i << endl;
			}
			stack_top = stk.top();
			//cerr << "top " << stack_top;
			grammar_rule = look_up_table( stack_top,current_string);
			dollar_indexes.clear();
			//cerr << "grammar_rule: " << grammar_rule << endl;
			if(grammar_rule.compare("pop") == 0){
				return "pop";
			}
		}
	}
}
int main() {
	table();
	/*for (int i = 0; i <= 40; i++) {
		for (int j = 0; j <= 25; j++) {
			cout << mau[i][j].first << " " << mau[i][j].second << " ";
		}
		cout << endl;
	}*/
	//--------------checking the table------------------
	ifstream read;
	ofstream write;
	read.open("parser_input.txt");
	write.open ("parser_output.txt");
	read >> input_string;
	cout << input_string;
	stk.push("S'");
	//cerr << stk.top();
	//cerr << input_string.size();
	while(k < input_string.size() - 1){
		string sample = get_token();
		//cerr << "sample " << sample << endl; 
		if(stk.top().compare("(RS,until)") == 0 && sample.compare("(RS,until)") != 0 ){
			stk.push("STMT");
		}
		if(stk.top().compare("(RS,finish)") == 0 && sample.compare("(RS,finish)") != 0 ){
			stk.push("STMT");
		}
		if (sample.compare("#") != 0 && stk.top().compare("#") == 0 ){
			stk.pop();
			stk.push("S'");
		}
		//cerr  << "k: "<< k << endl;
		//string s = get_token();
		//cerr << s << endl;
		//cerr << "stack top in main :" << stk.top() <<endl;
		string answer = algo(stk.top() , sample);
		//cerr << "answer" << answer << endl;
		if(answer.compare("ERROR") == 0){
			write << "The string is not accepted.";
			return 0;
		}
		else if(answer.compare("accepted") == 0){
			write << "The string is accepted.";
			return 0;
		}
		else if(answer.compare("pop") == 0){
			stk.pop();	
		}	
	}
	return 0;
}


