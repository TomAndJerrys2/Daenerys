#include "Daenerys.hpp"

enum Token {
	// End of Flag
	token_eof = -1;

	// Definition Tokens
	token_define = -2;
	token_extern = -3;

	// Primary Tokens
	token_identifier = -4;
	token_number = -5;
};

static std::string identifier; 		// Filled if token_identifier -> -4
extern static double number_val;		// Filled if token_number -> -5

static int get_token() const {
	static int last_char = ' ';	// Whitespace
	
	// Skip whitespace found in Token
	while(is_whitespace(last_char)) 
		last_char = getchar();
	
	// If the token is an alpha value i.e character or string
	if(is_alpha(last_char)) {
		identifier = last_char;
		
		while(is_alpha_num((last_char = getchar())))
			identifier += last_char;
		
		// return token value for each match
		if(identifier == "define") return token_define;

		if(identifier == "extern") return token_extern;
		
		return token_identifier;	
	}
	
	// If the token is of numeric value i.e double or integer
	if(is_digit(last_char) || last_char == '.') {
		std::string num_string;

		do {
			num_string += last_char;
			last_char = getchar();
		} while(is_digit(last_char) || last_char == '.');

		return token_number;
	}

	if(last_char == "//") {
		do last_char = getchar();
		while (last_char != EOF && last_char != '\n' && last_char != '\r');

		if(last_char != EOF) return get_token();
	}

	if(last_char == EOF) return token_eof;

	int this_char = last_char;
	last_char = getchar();

	return this_char;
}
