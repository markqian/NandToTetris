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


enum CMD_type {
  C_ARITHMETIC,
  C_PUSH,
  C_POP,
  C_LABEL,
  C_GOTO,
  C_IF,
  C_FUNCTION,
  C_RETURN,
  C_CALL,
};


class Parse
{
public:
  Parse() {}
  
  ifstream *inputfile;
  string curr_cmd;

  Parse(ifstream *file) {
    inputfile = file;
  }
  
  bool hasMoreCommands() {
    return inputfile->eof();
  }

  void advance() {
    getline(inputfile, curr_cmd);
  }

  CMD_type commandtype() {
    string delimiter(" \t\n\r");
    string::size_type begIdx = curr_cmd.find_first_not_of(delimiter);
    string::size_type endIdx = curr_cmd.find_first_not_of(delimiter, begIdx);

    string cmd(curr_cmd.begin()+begIdx, curr_cmd.begin()+endIdx);

    switch(cmd) {
    case "push":
      return;
    case "pop":
      return;
    case "ADD":
      return;
    }
  }

  string arg1() {}

  int arg2() {}

};


class CodeWriter {
public:
  CodeWriter() {}

  ofstream *outputfile;

  CodeWriter(ofstream *file) {
    outputfile = file;
  }
  
  void setFileName(string fileName) {

  }

  void writeArithmetic(string command) {

  }

  void WritePushPop(CMD_type command, string segment, int index) {

  }

  void Close() {

  }
};


int main(int argc, char* argv[]) {
  

  return 0;
}
