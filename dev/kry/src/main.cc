#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <vector>

#include "lex.h"
#include "krytype.h"
#include "parser.h"
#include "codegen.h"

using namespace std;

string read_file(string f) {
    ifstream file(f);
    if (!file.is_open()) {
        cerr << "Couldn't open file '" << f << "'\n";
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
}

int main() {
    string input_file = "examples/example.kry";

	string src = read_file(input_file);
	vector<Token> tokens = lex(src);
	Parser *parser = new Parser(tokens);
	vector<Stmt *> ast = parser->parse();

	parser->error_check();

    codegen(input_file, true, true);

	return 0;
}
