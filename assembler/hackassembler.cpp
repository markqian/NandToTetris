#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <regex>
#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <utility>

using namespace std;

class Parser {
public:
  int NUMCOMP = 18;
  int NUMDEST = 8;
  int NUMJUMP = 8;
  int symbolCounter = 16;
  int linecount = 0;

  struct comp_table {
    string compa0;
    string compa1;
    string binary;
  } c_table[18] = {
    {"0", "", "101010"},
    {"1", "", "111111"}, 
    {"-1","", "111010"}, 
    {"D", "", "001100"},
    {"A", "M",  "110000"},
    {"!D", "","001101"},
    {"!A", "!M","110001"},
    {"-D", "", "001111"},
    {"-A", "-M", "110011"},
    {"D+1", "", "011111"},
    {"A+1", "M+1","110111"},
    {"D-1","","001110"},
    {"A-1","M-1","110010"},
    {"D+A","D+M","000010"},
    {"D-A","D-M","010011"},
    {"A-D","M-D","000111"},
    {"D&A","D&M","000000"},
    {"D|A","D|M","010101"},
  };

  struct dest_table {
    string dest;
    string binary;
  } d_table[8] = {
    {"","000"},
    {"M","001"},
    {"D","010"},
    {"MD","011"},
    {"A","100"},
    {"AM","101"},
    {"AD","110"},
    {"AMD","111"},
  };


  struct jump_table {
    string jump;
    string binary;
  } j_table[8] = {
    {"","000"},
    {"JGT","001"},
    {"JEQ","010"},
    {"JGE","011"},
    {"JLT","100"},
    {"JNE","101"},
    {"JLE","110"},
    {"JMP","111"},
  };

  vector<pair<string, int> > s_table;
  vector<pair<string, int> > l_table;
  vector<pair<string, int> > p_table;

  struct pre_table {
    string symbol;
    int value;
  } pr_table[23] = {
    {"SP",0},
    {"LCL",1},
    {"ARG",2},
    {"THIS",3},
    {"THAT",4},
    {"R0",0},
    {"R1",1},
    {"R2",2},
    {"R3",3},
    {"R4",4},
    {"R5",5},
    {"R6",6},
    {"R7",7},
    {"R8",8},
    {"R9",9},
    {"R10",10},
    {"R11",11},
    {"R12",12},
    {"R13",13},
    {"R14",14},
    {"R15",15},
    {"SCREEN",16384},
    {"KBD",24576},
  };

  int lookupsymbol(vector<pair<string, int> > &table, string v) {
    for (vector<pair<string, int> >::iterator it = table.begin(); it != table.end(); it++) {
	if ((*it).first == v) {
	  return (*it).second;
	}
    }
    return -1;
  }

  int lookupsymbol(pre_table pr_table[], string v) {
    for (int i = 0; i<23; i++)
      {
	if (pr_table[i].symbol == v)
	  return pr_table[i].value;
      }
    return -1;
  }

  bool is_number(const std::string& s) {
    for (int i = 0; i<s.length(); i++)
      {
	if (!isdigit(s[i])) {
	  return false;
	}
      }
    return true;
  }

  string v2binary15(int v) {
    string b;
    while (v != 0) {
      if (v%2 ==0) {
	b = "0" + b;
      }
      else {
	b = "1" + b;
      }
      v = v/2;
    }

    for (int i = b.length(); i < 15; ++i) {
      b = "0" + b;
    }

    return b;
  }  

  void add_symbol_to_table(string symbol) {
    s_table.push_back(make_pair(symbol, symbolCounter));
  }

  void add_label_to_table(string symbol, int val) {
    l_table.push_back(make_pair(symbol, val));
  }


  string getvalue(string v) {
    string binary;

    if (is_number(v)) {
      int numb;
      istringstream (v) >> numb;
      binary = v2binary15(numb);
      return binary;
    }
    else {
      int numb;

      numb = lookupsymbol(pr_table, v);
      if (numb!=-1) {
	binary = v2binary15(numb);
	return binary;
      }

      numb = lookupsymbol(s_table, v);
      if (numb!=-1) {
	binary = v2binary15(numb);
	return binary;
      }

      numb = lookupsymbol(l_table, v);
      if (numb!=-1) {
	binary = v2binary15(numb);
	return binary;
      }

      binary = v2binary15(symbolCounter);
      add_symbol_to_table(v);	
      symbolCounter++;
      return binary;
    }
  }


  string getcomp(string comp) {
    for (int i = 0; i<NUMCOMP; i++) {
      if (c_table[i].compa0 == comp) {
	return "0"+c_table[i].binary;
      }
      else if (c_table[i].compa1 == comp) {
	return "1"+c_table[i].binary;
      }
    }
    return "";
  }


  string getdest(string dest) {
    for (int i = 0; i<NUMDEST; i++) {
      if (d_table[i].dest == dest) {
	return d_table[i].binary;
      }
    }
    return "";
  }


  string getjump(string jump) {
    for (int i = 0; i<NUMJUMP; i++) {
      if (j_table[i].jump == jump) {
	return j_table[i].binary;
      }    
    }
    return "";
  }


  string assemble(string in) {
    const string delims("@=;/");
    string::size_type begIdx;
    begIdx = in.find_first_of(delims);

    if (begIdx != string::npos) {
      if (in[begIdx] == '@') {		
	string v = getvalue(in.substr(begIdx+1));      
	return "0"+v;
      }
      else if (in[begIdx] == '=') {
	string comp = getcomp(in.substr(begIdx+1));
	string dest = getdest(in.substr(0,begIdx));
	string jump = getjump("");
	return "111"+comp+dest+jump;
      }
      else if (in[begIdx] == ';') {
	string comp = getcomp(in.substr(0,begIdx));
	string dest = getdest("");
	string jump = getjump(in.substr(begIdx+1));
	return "111"+comp+dest+jump;
      }
      else if (in[begIdx] == '/') {
       	return "";
      }
      else if (in[begIdx] == '(') {
	return "";
      }
    }
    else {
      return "";
    }
  }


  void parseFile(const string &filename) {
    string line;
    ifstream file(filename);
    ifstream file2(filename);

    int endIdx = filename.find_last_of(".") ;
    ofstream outfile(filename.substr(0,endIdx)+".hack");

    if (!file || !file2) {
      cerr << "can't open input file \"" << filename << "\""<<endl;
      exit(EXIT_FAILURE);      
    }
    
    string delimiter("\n\t\r ");
    string label;
    while (getline(file2, label)) {
      string::size_type Idx = label.find_first_of("(@/;=");
      
      if (Idx != string::npos) {
	if (label[Idx] == '(') {
	  int endIdx = label.find_last_of(")") - Idx - 1;
	  string symbol = label.substr(Idx+1, endIdx);
	  add_label_to_table(symbol,linecount);
	}
	else if (label[Idx] != '/') {
	  linecount++;
	}
      }
    }

    while (getline(file, line)) {
      string::size_type begIdx = line.find_first_of("/(");
      if (begIdx != string::npos) {
	line = line.substr(0, begIdx - 1);
      }
      for (int i = 0; i<delimiter.size(); i++) {
	line.erase(remove(line.begin(), line.end(), delimiter[i]), line.end());
      }
      
      string out = assemble(line);
      if (out != "") {	
	outfile<<out<<endl;
	cout<<out<<endl;
      }
    }
  }
};

int main(int argc, char*argv[]) {
  Parser p;
  string file = argv[1];
  p.parseFile(file);
}
