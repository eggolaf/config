#ifndef KRY_LEXER_H
#define KRY_LEXER_H

enum TokenKind {
	EndOfFile = 0,
	Error,

	OpeningParen,
	ClosingParen,
	OpeningBrace,
	ClosingBrace,

	Plus,
	Minus,
	Star,
	Slash,
	Percent,

	Comma,
	Colon,
	Equals,

	Const,
	Let,
	Fn,

	Text,
	Number,
	Identifier
};

struct Token {
	TokenKind kind;
	std::string lexeme;
};

std::vector<Token> lex(std::string);

#endif