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

		case OpType::ADD: {
			if (node->left->is_double_return ||
				node->right->is_double_return) {
				node->is_double_return = true;
				double val1 = node->left->double_return;
				double val2 = node->right->double_return;
				node->double_return = val1 + val2;
			}
			else if (node->left->is_int_return &&
				node->right->is_int_return) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				node->int_return = val1 + val2;
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
			break;
		}
		case OpType::SUB: {
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
			break;
		}
		case OpType::MUL: {
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
			break;
		}
		case OpType::DIV: {
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
			break;
		}
		case OpType::MOD: {
			if (node->left->is_int_return && node->right->is_int_return) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				node->int_return = val1 % val2;
			}
			else {
				std::cerr << "compiler: Modulus operator requires integer inputs at ln:" << node->ln << " col:" << node->col << std::endl;
				exit(1);
			}
			break;
		}
		case OpType::EQ: {
			if ((node->left->is_int_return && node->right->is_int_return)) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				if (val1 == val2) {
					node->int_return = 1;
				}
				else {
					node->int_return = 0;
				}

			}
			else if ((node->left->is_double_return && node->right->is_int_return)) {
				node->is_int_return = true;
				double val1 = node->left->int_return;
				int val2 = node->right->int_return;
				if (val1 == val2) {
					node->int_return = 1;
				}
				else {
					node->int_return = 0;
				}
			}
			else if ((node->left->is_double_return && node->right->is_double_return)) {
				node->is_int_return = true;
				double val1 = node->left->int_return;
				double val2 = node->right->int_return;
				if (val1 == val2) {
					node->int_return = 1;
				}
				else {
					node->int_return = 0;
				}
			}
			else if ((node->left->is_int_return && node->right->is_double_return)) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				double val2 = node->right->int_return;
				if (val1 == val2) {
					node->int_return = 1;
				}
				else {
					node->int_return = 0;
				}
			}
			else {
				std::cerr << "Compiler: Invalid value for the operation at ln:" << node->ln << " col:" << node->col << std::endl;
				exit(1);
			}
			break;
		}
		case OpType::NOT_EQ: {
			if ((node->left->is_int_return && node->right->is_int_return)) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				if (val1 == val2) {
					node->int_return = 0;
				}
				else {
					node->int_return = 1;
				}

			}
			else if ((node->left->is_double_return && node->right->is_int_return)) {
				node->is_int_return = true;
				double val1 = node->left->int_return;
				int val2 = node->right->int_return;
				if (val1 == val2) {
					node->int_return = 0;
				}
				else {
					node->int_return = 1;
				}
			}
			else if ((node->left->is_double_return && node->right->is_double_return)) {
				node->is_int_return = true;
				double val1 = node->left->int_return;
				double val2 = node->right->int_return;
				if (val1 == val2) {
					node->int_return = 0;
				}
				else {
					node->int_return = 1;
				}
			}
			else if ((node->left->is_int_return && node->right->is_double_return)) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				double val2 = node->right->int_return;
				if (val1 == val2) {
					node->int_return = 0;
				}
				else {
					node->int_return = 1;
				}
			}
			else {
				std::cerr << "Compiler: Invalid value for the operation at ln:" << node->ln << " col:" << node->col << std::endl;
				exit(1);
			}
			break;
		}
		case OpType::L_AND: {
			//we first convert left and right to boolean (int 1 or 0) values
			node->left->is_int_return = true;
			node->right->is_int_return = true;
			if (node->left->is_str_return) {
				if (node->left->str_return == "") {
					node->left->int_return = 0;
				}
				else {
					node->left->int_return = 1;
				}
			}
			else if (node->left->is_double_return) {
				if (node->left->double_return == 0) {
					node->left->int_return = 0;
				}
				else {
					node->left->int_return = 1;
				}
			}
			else {
				std::cerr << "Compiler: Invalid input values for operation at ln:" << node->ln << " col:" << node->col;
				exit(1);
			}

			if (node->right->is_str_return) {
				if (node->right->str_return == "") {
					node->right->int_return = 0;
				}
				else {
					node->right->int_return = 1;
				}
			}
			else if (node->right->is_double_return) {
				if (node->right->double_return == 0) {
					node->right->int_return = 0;
				}
				else {
					node->right->int_return = 1;
				}
			}
			else {
				std::cerr << "Compiler: Invalid input values for operation at ln:" << node->ln << " col:" << node->col;
				exit(1);
			}


			//Now we are ready to do the comparison.
			if (node->left->int_return && node->right->int_return) {
				node->int_return = 1;
			}
			else {
				node->int_return = 0;
			}
			break;
		}
		case OpType::L_OR: {
			//we first convert left and right to boolean (int 1 or 0) values
			node->left->is_int_return = true;
			node->right->is_int_return = true;
			if (node->left->is_str_return) {
				if (node->left->str_return == "") {
					node->left->int_return = 0;
				}
				else {
					node->left->int_return = 1;
				}
			}
			else if (node->left->is_double_return) {
				if (node->left->double_return == 0) {
					node->left->int_return = 0;
				}
				else {
					node->left->int_return = 1;
				}
			}
			else {
				std::cerr << "Compiler: Invalid input values for operation at ln:" << node->ln << " col:" << node->col;
				exit(1);
			}

			if (node->right->is_str_return) {
				if (node->right->str_return == "") {
					node->right->int_return = 0;
				}
				else {
					node->right->int_return = 1;
				}
			}
			else if (node->right->is_double_return) {
				if (node->right->double_return == 0) {
					node->right->int_return = 0;
				}
				else {
					node->right->int_return = 1;
				}
			}
			else {
				std::cerr << "Compiler: Invalid input values for operation at ln:" << node->ln << " col:" << node->col;
				exit(1);
			}


			//Now we are ready to do the comparison.
			if (node->left->int_return || node->right->int_return) {
				node->int_return = 1;
			}
			else {
				node->int_return = 0;
			}
			break;
		}
		case OpType::B_OR: {
			//Binary Operation onlly works on integers and chars (which is also an int in cpp)

			node->is_int_return = true;
			bool is_left_char = node->left->is_str_return && node->left->str_return.length() == 1;
			bool is_right_char = node->right->is_str_return && node->right->str_return.length() == 1;

			if ((is_left_char || node->left->is_int_return) &&
				(is_right_char || node->right->is_int_return)) {
				//first , if there is any char, we first convert the char to 
				//int 

				if (is_left_char) {
					node->left->int_return = static_cast<int>(node->right->str_return[0]);
				}

				if (is_right_char) {
					node->left->int_return = static_cast<int>(node->left->str_return[0]);
				}

				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				node->int_return = val1 | val2;
			}
			else {
				std::cerr << "Compiler: Invalid value for the operation at ln:" << node->ln << " col:" << node->col;
			}

			break;
		}
		case OpType::B_AND: {
			node->is_int_return = true;
			bool is_left_char = node->left->is_str_return && node->left->str_return.length() == 1;
			bool is_right_char = node->right->is_str_return && node->right->str_return.length() == 1;

			if ((is_left_char || node->left->is_int_return) &&
				(is_right_char || node->right->is_int_return)) {
				//first , if there is any char, we first convert the char to 
				//int 

				if (is_left_char) {
					node->left->int_return = static_cast<int>(node->right->str_return[0]);
				}

				if (is_right_char) {
					node->left->int_return = static_cast<int>(node->left->str_return[0]);
				}

				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				node->int_return = val1 & val2;
			}
			else {
				std::cerr << "Compiler: Invalid value for the operation at ln:" << node->ln << " col:" << node->col;
			}
			break;
		}
		case OpType::LT:
			break;
		case OpType::GT:
			break;
		case OpType::LTE:
			break;
		case OpType::GTE:
			break;
		case OpType::ASSIGN:
			break;

		}

		//End Operation, clear the return vals.
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
	}p
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

			//TODO: might need to expnd this
			if (iterate_args(node) == BREAK){
				break;
			}
			else if (iterate_args(node) == CONTINUE) {
				continue;
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



