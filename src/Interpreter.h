#ifndef  INTERPRETER_H
#define INTERPRETER_H
#include <map>
#include "Parser.h"
#include "Ast.h"
#include "DataTypes.h"
#include "Registry.h"
#include "FunRegistry.h"
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
	void execute(Ast::Exp* root, FunRegistry* fun_registry);
	static int getInstructionType(std::string label);
private:
	void post_order_walk(Ast::Exp* node);
	void interpret_node(Ast::Exp* node);
	void code_block_walk(Ast::Exp* node);
	int execute_args(Ast::Exp * node);
	void runFunction(Ast::Exp* function, Ast::Exp* node);
	Registry* _registry;
	FunRegistry* _fun_registry;

	; //gpt stands for Pointer Loop Up Table. 
};


#endif 

