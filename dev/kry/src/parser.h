#ifndef KRY_PARSER_H
#define KRY_PARSER_H

typedef unsigned int uint;

enum StmtKind {
	StmtFuncDef = 0,
	StmtReturn,
};

enum ExprKind {
	IntLiteral = 0,
};

class Stmt {
public:
	StmtKind kind;
};

class Expr {
public:
	ExprKind kind;
};

struct Parameter {
	std::string name;
	KryType type;

	Parameter(std::string, KryType);
};

class StmtFuncDef : public Stmt {
public:
	std::string name;
	KryType type;
	std::vector<Parameter> pars;
	std::vector<Stmt *> body;

	StmtFuncDef(std::string, KryType, std::vector<Parameter>,
			    std::vector<Stmt *>);
};

class StmtReturn : public Stmt {
public:
	Expr *value;
	
	StmtReturn(Expr *);
};

class ExprIntLiteral : public Expr {
public:
	int value;

	ExprIntLiteral(int);
};

class Parser {
public:
	Parser(std::vector<Token>);

	std::vector<Stmt *> parse();

	void error_check();
private:
	std::vector<std::string> errors;
	std::vector<std::string> warnings;
	std::vector<Token> tokens;
	uint pos;

	Token consume(TokenKind);
	Token expect(char);
	bool eat(TokenKind);
	Token peek();
	bool is_error(Token);

	void fatal(std::string);
	void error(std::string);
	void warning(std::string);
};

#endif
