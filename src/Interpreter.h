#ifndef  INTERPRETER_H
#define INTERPRETER_H
#include <map>
#include "Parser.h"
#include "Ast.h"
#include "Variable.h"
#include "Registry.h"
class Interpreter
{
public:
	Interpreter();
	~Interpreter();
	enum Instructions {
		NULL_INSTR,
		BREAK,
		CONTINUE
	};
	void execute(Ast::Exp* root);
	static int getInstructionType(std::string label);
private:
	void post_order_walk(Ast::Exp* node);
	void interpret_node(Ast::Exp* node);
	void code_block_walk(Ast::Exp* node);
	int execute_args(Ast::Exp * node);
	Registry* _registry;
	; //gpt stands for Pointer Loop Up Table. 
};


#endif 

