#ifndef  INTEPRETER_H
#define INTEPRETER
#include <map>
#include "Parser.h"
#include "Ast.h"
#include "Variable.h"
#include "Registry.h"
class Intepreter
{
public:
	Intepreter();
	~Intepreter();
	enum Instructions {
		NULL_INSTR,
		BREAK,
		CONTINUE
	};
	void execute(Ast::Exp* root);
	static int getInstructionType(std::string label);
private:
	void post_order_walk(Ast::Exp* node);
	void intepret_node(Ast::Exp*node);
	void code_block_walk(Ast::Exp* node);
	int execute_args(Ast::Exp * node);
	Registry* _registry;
	; //gpt stands for Pointer Loop Up Table. 
};


#endif 

