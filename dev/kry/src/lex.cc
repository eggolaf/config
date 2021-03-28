/* I orginally wrote this in c, that's why it looks a lot like c */

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "lex.h"

using namespace std;

struct Lexer;

typedef unsigned int uint;
typedef void *(*state_func)(Lexer *);

struct Lexer {
	string input;
	uint start;
	uint pos;
	uint width;
	vector<Token> tokens;
};

static Lexer *lexer_new(string);
static vector<Token> lexer_run(Lexer *);

static state_func lex_text(Lexer *);
static state_func lex_number(Lexer *);
static state_func lex_identifier(Lexer *);
static state_func lex_binary(Lexer *);
static state_func lex_opening_paren(Lexer *);
static state_func lex_closing_paren(Lexer *);
static state_func lex_opening_brace(Lexer *);
static state_func lex_closing_brace(Lexer *);

static void emit(Lexer *, TokenKind);
static char next(Lexer *);
static char peek(Lexer *);
static bool accept(Lexer *, string);
static void accept_run(Lexer *, string);
static void backup(Lexer *);
static void skip_spaces(Lexer *);
static void lexer_ignore(Lexer *);

const string SIGNS = "+-";
const string DIGITS = "0123456789";
const string IDCHARS = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static map<string, TokenKind> keywords = {};

vector<Token> lex(string inp) {
	Lexer *l = lexer_new(inp);
	vector<Token> tokens;
	
	if (keywords.empty()) {
		keywords.insert(make_pair("fn", TokenKind::Fn));
		keywords.insert(make_pair("let", TokenKind::Let));
		keywords.insert(make_pair("const", TokenKind::Const));
	}

	tokens = lexer_run(l);

	delete l;
	return tokens;
}

Lexer *lexer_new(string inp) {
	Lexer *l = new Lexer();
	l->input = inp;
	l->start = 0;
	l->pos = 0;
	l->tokens = {};

	return l;
}

vector<Token> lexer_run(Lexer *l) {
	state_func state;

	for (state = (state_func) lex_text; state != nullptr;)
		state = (state_func) state(l);

	return l->tokens;	
}

state_func lex_text(Lexer *l) {
	while (true) {
		char cur = peek(l);
		
		if (cur == '(')
			return (state_func) lex_opening_paren;

		if (cur == ')')
			return (state_func) lex_closing_paren;
		
		if (cur == '{')
			return (state_func) lex_opening_brace;
		
		if (cur == '}')
			return (state_func) lex_closing_brace;

		if (isdigit(cur) || cur == '+' || cur == '-') {
			if (l->pos > l->start)
				emit(l, TokenKind::Text);
			return (state_func) lex_number;
		}

		if (isalpha(cur) || cur == '_') {
			if (l->pos > l->start)
				emit(l, TokenKind::Text);
			return (state_func) lex_identifier;
		}
		
		if (next(l) == '\0')
			break;

		if (cur == '\n' || cur == ' ')
			lexer_ignore(l);
	}
	
	emit(l, EndOfFile);
	return nullptr;
}

state_func lex_number(Lexer *l) {
	accept(l, SIGNS);	
	accept_run(l, DIGITS);

	if (accept(l, "."))
		accept_run(l, DIGITS);

	emit(l, TokenKind::Number);
	return (state_func) lex_binary;
}

state_func lex_identifier(Lexer *l) {
	string id;

	accept_run(l, IDCHARS);

	id = l->input.substr(l->start, l->pos - l->start);

	if (keywords.find(id) != keywords.end())
		emit(l, keywords[id]);
	else
		emit(l, TokenKind::Identifier);

	return (state_func) lex_binary;
}

state_func lex_binary(Lexer *l) {
	char ch;
	
	skip_spaces(l);	
	ch = next(l);

	switch (ch) {
	case '+':
		emit(l, TokenKind::Plus);
		break;
	case '-':
		emit(l, TokenKind::Minus);
		break;
	case '*':
		emit(l, TokenKind::Star);
		break;
	case '/':
		emit(l, TokenKind::Slash);
		break;
	case '%':
		emit(l, TokenKind::Percent);
		break;
	case ',':
		emit(l, TokenKind::Comma);
		break;
	case ':':
		emit(l, TokenKind::Colon);
		break;
	case '=':
		emit(l, TokenKind::Equals);
		break;
	default:
		backup(l);
	}

	return (state_func) lex_text;
}

state_func lex_opening_paren(Lexer *l) {
	l->pos++;
	emit(l, TokenKind::OpeningParen);
	return (state_func)lex_binary;
}

state_func lex_closing_paren(Lexer *l) {
	l->pos++;
	emit(l, TokenKind::ClosingParen);
	return (state_func) lex_binary;
}

state_func lex_opening_brace(Lexer *l) {
	l->pos++;
	emit(l, TokenKind::OpeningBrace);
	return (state_func) lex_text;
}

state_func lex_closing_brace(Lexer *l) {
	l->pos++;
	emit(l, TokenKind::ClosingBrace);
	return (state_func) lex_text;
}

void emit(Lexer *l, TokenKind kind) {
	string lexeme = l->input.substr(l->start, l->pos - l->start);
	l->tokens.push_back(Token{kind, lexeme});
	l->start = l->pos;
}

char next(Lexer *l) {
	char ch;

	if (l->pos >= l->input.length()) {
		l->width = 0;
		return '\0';
	}
	
	ch = l->input[l->pos];
	l->width = 1;
	l->pos += l->width;
	return ch;
}

char peek(Lexer *l) {
	if (l->pos >= l->input.length())
		return '\0';
	return l->input[l->pos];
}

bool accept(Lexer *l, string valid) {
	char ch = next(l);

	if (valid.find(ch) != string::npos)
		return true;

	backup(l);
	return false;
}

void accept_run(Lexer *l, string valid) {
	char ch = next(l);

	while (valid.find(ch) != string::npos)
		ch = next(l);
	
	backup(l);
}

void backup(Lexer *l) {
	l->pos -= l->width;
}

void skip_spaces(Lexer *l) {
	accept_run(l, " ");
	lexer_ignore(l);
}

void lexer_ignore(Lexer *l) {
	l->start = l->pos;
}