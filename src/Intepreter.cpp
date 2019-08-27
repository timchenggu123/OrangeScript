#include "Intepreter.h"
#include "Ast.h"
Intepreter::Intepreter()
{
}

Intepreter::~Intepreter()
{
}

void Intepreter::execute(Ast::Exp * root)
{
	if (root->expType != Ast::CODE_BLK) {
		std::cerr << "parser: code block at root node";
		exit(0);
	}

	post_order_walk(root);
}

int Intepreter::getInstructionType(std::string label)
{
	if (label == "break") {
		return BREAK;
	}
	else if (label == "continue") {
		return CONTINUE;
	}
	return -999;
}

int Intepreter::post_order_walk(Ast::Exp * node)
{
	if (Ast::isCodeBlock(node)) {
		return code_block_walk(node);
	}
	else if (node->left == nullptr &&
		node->right == nullptr) {
		intepret_node(node);
	}
	else if (node->expType == Ast::BINARY){
		post_order_walk(node->left);
		post_order_walk(node->right);
		intepret_node(node);
	}
	else if (node->expType == Ast::UNARY) {
		post_order_walk(node->left);
		intepret_node(node);
	}
	return 0;
}

void Intepreter::intepret_node(Ast::Exp * node)
{
	//TODO:Complete this
	switch (node->expType) {
	case Ast::BINARY: {
		switch (node->opType) {
		case OpType::ADD:
			if (node->left->is_double_return ||
				node->right->is_double_return) {
				node->is_double_return = true;
				double val1 = node->left->double_return;
				double val2 = node->right->double_return;
				node->double_return = val1 + val2;
			}
			else if(node->left->is_int_return &&
					node->right->is_int_return){
				node->is_int_return = true;
				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				node->int_return= val1 + val2;
			}
			else if (node->left->is_str_return &&
				node->right->is_str_return) {
				node->is_str_return = true;
				std::string val1 = node->left->str_return;
				std::string val2 = node->right->str_return;
				node->str_return = val1 + val2;
			}
			else {
				//throwing an error otherwise. 
				std::cerr << "Compiler: invalid value for the operation at ln:" << node->ln << " col:" << node->col << std::endl;
				exit(1);
			}
			
		case OpType::SUB:
			if (node->left->is_double_return ||
				node->right->is_double_return) {
				node->is_double_return = true;
				double val1 = node->left->double_return;
				double val2 = node->right->double_return;
				node->double_return = val1 - val2;
			}
			else if (node->left->is_int_return &&
				node->right->is_int_return) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				node->int_return = val1 - val2;
			}
			else {
				//throwing an error otherwise. 
				std::cerr << "Compiler: invalid value for the operation at ln:" << node->ln << " col:" << node->col << std::endl;
				exit(1);
			}
		case OpType::MUL:
			if (node->left->is_double_return ||
				node->right->is_double_return) {
				node->is_double_return = true;
				double val1 = node->left->double_return;
				double val2 = node->right->double_return;
				node->double_return = val1 * val2;
			}
			else if (node->left->is_int_return &&
				node->right->is_int_return) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				node->int_return = val1 * val2;
			}
			else {
				//throwing an error otherwise. 
				std::cerr << "Compiler: invalid value for the operation at ln:" << node->ln << " col:" << node->col << std::endl;
				exit(1);
			}
		case OpType::DIV:
			if (node->left->is_double_return ||
				node->right->is_double_return) {
				node->is_double_return = true;
				double val1 = node->left->double_return;
				double val2 = node->right->double_return;
				if (val2 == 0) {
					std::cerr << "Compiler: Div by zero error at ln:" << node->ln << " col:" << node->col;
				}
				node->double_return = val1 / val2;
			}
			else if (node->left->is_int_return &&
				node->right->is_int_return) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				node->int_return = val1 / val2;
			}
			else {
				//throwing an error otherwise. 
				std::cerr << "Compiler: Invalid value for the operation at ln:" << node->ln << " col:" << node->col << std::endl;
				exit(1);
			}
		case OpType::MOD:
		case OpType::EQ:
		case OpType::NOT_EQ:
		case OpType::L_AND:
		case OpType::L_OR:
		case OpType::B_OR:
		case OpType::B_AND:
		case OpType::LT:
		case OpType::GT:
		case OpType::LTE:
		case OpType::GTE:
		case OpType::ASSIGN:

		}

		Ast::clearReturnVal(node->left);
		Ast::clearReturnVal(node->right);
		break;
	}
	case Ast::UNARY:
		Ast::clearReturnVal(node);
		break;
	case Ast::INTEGER:
		break;
	case Ast::DECIMAL:
		break;
	case Ast::STRING:
		break;
	case Ast::VARIABLE:
		break;
	}
}

int Intepreter::code_block_walk(Ast::Exp * node)
{

	switch (node->expType) {
	case Ast::FOR: {

		Ast::Exp* ctrl = node->left;
		post_order_walk(ctrl);
		if (ctrl->is_int_return) {
			for (int i = 1; i < ctrl->int_return; i++) {
				iterate_args(node);
			}
		}
		else {
			std::cerr << "Intepreter: Expected an integer value at ln:" << node->ln << " col:" << node->col;
			exit(1);
		}

		break;
	}

	case Ast::WHILE: {

		Ast::Exp* condition = node->left;
		post_order_walk(condition);
		while (true)
		{
			if (condition->is_int_return) {
				if (condition->int_return == 0) {
					break;
				}
			}
			else if (condition->is_double_return) {
				if (condition->double_return == 0) {
					break;
				}
			}
			else if (condition->is_str_return) {
				if (condition->str_return == "") {
					break;
				}
			}
			else if (condition->is_symbolic_return) {
				//TODO grab the variable table and check variable value
			}

			if (iterate_args(node) == 1){
				break;
			}
		}


	}

	}
}

int Intepreter::iterate_args(Ast::Exp*node) {
	//a return value of 1 means exit the current code block

	std::list<Ast::Exp*>* arguments = node->arguments;
	std::list<Ast::Exp*>::iterator it;
	for (it = arguments->begin(); it != arguments->end(); it++) {
		Ast::Exp* e = *it;
		if (e->expType == Ast::INSTR) {
			return e->int_attr;
		}
		code_block_walk(e);
	}
	return 0;
}



