#ifndef PARSER
#define PARSER
#include <deque>
#include <string.h>
#include <ctype.h>
#include <exception>
#include <iostream>

class Parser{
	enum LEXEM{
		NUM,
		PLUS,
		MUL,
		LB,
		RB,
		DONE
	};

	int num_value;
	std::deque<char> buffer;
	LEXEM lookahead;

	private:
	void match(int t){
		if(lookahead == t){
			lookahead = lexan();
		}else{
			//throw std::exception("syntax error");
		}
	}	

	public:
	Parser():num_value(0), lookahead(DONE){}

	int eval(const char* str){
		std::deque<char> tmp(str, str + strlen(str));
		buffer.swap(tmp);
		lookahead = lexan();
		return expr();
	}

	/*
	 * expr -> term rest
	 */
	int expr(){
		int result = term();
		switch(lookahead){
			case PLUS:
				match(lookahead); return result + term();
			default:
				return result;
		}

		return result;	
	}

	int term(){
		int result = factor();
		switch(lookahead){
			case MUL:
				match(lookahead); return result * factor();
			default:
				return result;
		}
	}


	int factor(){
		int result = 0;
		switch(lookahead){
			case NUM:
				result = getValue(); match(NUM); break;
			case LB:
				match(LB); result = expr(); match(RB); break;
		}
		return result;
	}
	

	LEXEM lexan(){
		if(buffer.empty())
			return DONE;
		else{
			char peek = buffer.front();
			buffer.pop_front();
			if(isdigit(peek)){
				int v = 0;
				do {
					v = v*10 + (peek - '0');
					if(buffer.empty()){ break;}
					else{
						peek = buffer.front();
						buffer.pop_front();
					}
				}while(isdigit(peek));
				num_value = v;
				buffer.push_front(peek);
				return NUM;
			}else if(peek == '+'){
				return PLUS;
			}else if(peek == '*'){
				return MUL;
			}else if(peek == '('){
				return LB;
			}else if(peek == ')'){
				return RB;
			}
		}
	}

	int getValue(){
		return num_value;
	}

};
#endif
