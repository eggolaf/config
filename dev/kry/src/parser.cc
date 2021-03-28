#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "lex.h"
#include "krytype.h"
#include "parser.h"

using namespace std;

static Token error_token = Token{TokenKind::Error, ""};

Parser::Parser(vector<Token> _tokens) {
	errors = {};
	warnings = {};
	tokens = _tokens;
	pos = 0;
}

vector<Stmt *> Parser::parse() {
	vector<Stmt *> ast = {};

	return ast;
}

Token Parser::consume(TokenKind kind) {
	Token t = peek();
	pos++;
	if (t.kind != kind)
		return error_token;
	return t;
}

Token Parser::expect(char ch) {
	Token t = peek();
	pos++;
	if (t.lexeme[0] != ch) {
		ostringstream out;  
		out << "Expected '" << ch << "' but found '" << t.lexeme << "'";
		error(out.str());
		return error_token;
	}
	return t;
}

bool Parser::eat(TokenKind kind) {
	Token t = peek();
	if (t.kind != kind)
		return false;
	pos++;
	return true;
}

Token Parser::peek() {
	return tokens[pos];
}

bool Parser::is_error(Token t) {
	return t.kind == TokenKind::Error;
}

void Parser::error_check() {
	if (!errors.empty()) {
		cout << "errors: " << errors.size() << "\n";
		for (string err : errors)
			cout << "\terror: " << err << "\n";
	}

	if (!warnings.empty()) {
		cout << "warnings: " << warnings.size() << "\n";
		for (string war : warnings)
			cout << "\twarning: " << war << "\n";
	}
	if (!errors.empty())
		exit(EXIT_FAILURE);
}

void Parser::fatal(string msg) {
	cout << "fatal: " << msg << "\n";
	exit(EXIT_FAILURE);
}

void Parser::error(string err) {
	errors.push_back(err);
}

void Parser::warning(string warning) {
	warnings.push_back(warning);
}

Parameter::Parameter(string _name, KryType _type) {
	name = _name;
	type = _type;
}

StmtFuncDef::StmtFuncDef(string _name, KryType _type,
		vector<Parameter> _pars, vector<Stmt *> _body) {
	kind = StmtKind::StmtFuncDef;
	name = _name;
	type = _type;
	pars = _pars;
	body = _body;
}

ExprIntLiteral::ExprIntLiteral(int val) {
	kind = ExprKind::IntLiteral;
	value = val;
}

StmtReturn::StmtReturn(Expr *val) {
	kind = StmtKind::StmtReturn;
	value = val;
}
