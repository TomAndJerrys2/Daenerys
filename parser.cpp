#include "Daenerys.hpp"

class ExpressAST {

	public:
		virtual ~ExpressAST() = default;
};
	
// Base class for Numeric values and constants
class NumberExpression : public ExpressAST {

	protected:
		double value;

	public:
		NumberExpression(double val) : value(val) {}
};

// Base class for expressions that can change
class VariableExpression : public {

	protected:
		std::string var_name;

	public:
		VariableExpression(const std::string & var_n) : var_name(var_n) {}
};

// Base class for Binary operators
class BinaryExpression : ExpressAST {
	
	protected:
		char bin_op;
		unique_ptr<ExpressAST> LHS, RHS;

	public:
		BinaryExpression(char op, unique_ptr<ExpressAST> LHS, unique_ptr<ExpressAST> RHS)
			: bin_op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

// Base class for function calls and callers
class CallExpressionAST(const std::string & caller, std::vector<unique_ptr<ExpressAST>> args) {
	
	protected:
		std::string caller;
		std::vector<unique_ptr<ExpressAST>> args;

	public:
		CallExpressionAST(const std::string & caller, std::vector<unique_ptr<ExpressAST>> arguments)
			: caller(caller), args(std::move(arguments)) {}
};

// Base class for representing function prototypes i.e signature declarations
// without the necessary body until linking
class PrototypeAST {
	
	protected:
		std::string protoype_name;
		std::vector<std::string> args;

	public:
		PrototypeAST(const std::string & name, std::vector<std::string> arguments)
			: prototype_name(name), args(arguments) {}

		const std::string & get_prototype_name() const { return prototype_name; }
};

// Base class for representing a function definition
// for an exisiting prototype
class FunctionAST {
	
	protected:
		unique_ptr<PrototypeAST> prototype;	// i.e add(i8, i8)
		unique_ptr<ExpressAST> definition;	// i.e { return x + y; }
	
	public:
		FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<ExpressAST> def)
			: prototype(std::move(proto)), definition(std::move(def)) {} 
};

// -- Token Precedence --
static int CurrentToken;
static int GetNextToken() { return CurrentToken = GetToken(); }

static std::map<char, uint8_t> BinaryPrecedence;

static int GetTokenPrecedence() {
	if(!isascii(CurrentToken)) return -1;

	int TokenPrec = BinaryPrecedence[CurrentToken];

	if(TokenPrec <= 0) return -1;

	return TokenPrec;
}

// Logging errors based on the precedence of the binary operation used
unique_ptr<ExpressionAST> LogError(const char* str) {	
	fprintf(stderr, "Error: %s\n", str);
	return nullptr;
}

unique_ptr<ExpressionAST> LogErrorP(const char* str) {	
	fprintf(str);
	return nullptr
}

static std::unique_ptr<ExpressionAST> ParseExpression();

static std::unique_ptr<ExpressionAST> ParseNumberExpression() {
	auto res = std::make_unique<NumberExpressionAST>(number_value);
	GetNextToken();
	return std::move(res);
}

static std::unique_ptr<ExpressionAST> ParseParentExpression() {
	GetNextToken();
	auto expr = ParseExpression();

	if(!expr) return nullptr;

	if(CurrentToken != ')') return LogError("Expected end with ')'");

	GetNextToken();
	return expr;
}


