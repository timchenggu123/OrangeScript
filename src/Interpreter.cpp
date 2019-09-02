#include "Interpreter.h"
#include "Ast.h"
Interpreter::Interpreter() :
	_registry(new Registry())
	
{
}

Interpreter::~Interpreter()
{
}

void Interpreter::execute(Ast::Exp * root, FunRegistry* fun_registry)
{
	if (root->expType != Ast::CODE_BLK) {
		std::cerr << "Intepreter: no code block at root node";
		exit(0);
	}
	_fun_registry = fun_registry;
	post_order_walk(root);
}

int Interpreter::getInstructionType(std::string label)
{
	if (label == "break") {
		return BREAK;
	}
	else if (label == "continue") {
		return CONTINUE;
	}
	return -999;
}

void Interpreter::post_order_walk(Ast::Exp * node)
{

	if (Ast::isCodeBlock(node)) {
		 code_block_walk(node);
	}
	else if (node->left == nullptr &&
		node->right == nullptr) {
		interpret_node(node);
	}
	else if (node->expType == Ast::BINARY){
		post_order_walk(node->left);
		post_order_walk(node->right);
		interpret_node(node);
	}
	else if (node->expType == Ast::UNARY) {
		post_order_walk(node->left);
		interpret_node(node);
	}
}

void Interpreter::interpret_node(Ast::Exp * node)
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
						node->left->int_return = node->right->str_return[0];
					}

					if (is_right_char) {
						node->left->int_return = node->left->str_return[0];
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
						node->left->int_return = node->right->str_return[0];
					}

					if (is_right_char) {
						node->left->int_return = node->left->str_return[0];
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
			case OpType::LT:{	
				if ((node->left->is_int_return && node->right->is_int_return)) {
					node->is_int_return = true;
					int val1 = node->left->int_return;
					int val2 = node->right->int_return;
					if (val1 < val2) {
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
					if (val1 < val2) {
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
					if (val1 < val2) {
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
					if (val1 < val2) {
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
			
			case OpType::GT:
			{				
				if ((node->left->is_int_return && node->right->is_int_return)) {
				node->is_int_return = true;
				int val1 = node->left->int_return;
				int val2 = node->right->int_return;
				if (val1 > val2) {
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
				if (val1 > val2) {
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
				if (val1 > val2) {
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
				if (val1 > val2) {
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
			case OpType::LTE:
			{
				if ((node->left->is_int_return && node->right->is_int_return)) {
					node->is_int_return = true;
					int val1 = node->left->int_return;
					int val2 = node->right->int_return;
					if (val1 <= val2) {
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
					if (val1 <= val2) {
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
					if (val1 <= val2) {
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
					if (val1 <= val2) {
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
			case OpType::GTE:
			{
				if ((node->left->is_int_return && node->right->is_int_return)) {
					node->is_int_return = true;
					int val1 = node->left->int_return;
					int val2 = node->right->int_return;
					if (val1 >= val2) {
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
					if (val1 >= val2) {
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
					if (val1 >= val2) {
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
					if (val1 >= val2) {
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
			case OpType::ASSIGN: {
				if (!node->left->is_symbolic_return) {
					std::cerr << "Compiler: Assignment operation requires a symbolic variable on the left hand side at ln:" << node->ln << " col:" << node->col;
				}
				else {
					Variable* v = _registry->getVariable(node->left->str_attr); //the variable label is stored in str_attr;
					if (v == nullptr) {
						//we have the choice of throwing an error or declaring a new variable
						//we choose to declare a variable for now.
						//TODO: might need future modification

						if (node->right->is_double_return) {
							Variable* x = new Decimal(node->right->double_return, node->str_attr);
							_registry->registerVariable(node->left->str_attr, x);

						} else if (node->right->is_int_return) {
							
							Variable* x = new Integer(node->right->int_return, node->str_attr);
							_registry->registerVariable(node->left->str_attr, x);
							int abc = 1;

						}
						else if (node->right->is_str_return) {
							Variable* x = new String(node->right->str_return, node->str_attr);
							_registry->registerVariable(node->left->str_attr, x);
						}
						else if (node->right->is_symbolic_return) {
							//TODO: complete symbolic assignment that is not of the 3 basic types. 
							int a = 1; //just so I have something to set a break point on.
						}

					}
					else {

						if (node->right->is_double_return) {
							if (v->_getType() == Ast::DECIMAL) {
								Decimal* x = dynamic_cast<Decimal*>(v);
								x->setVal(node->right->double_return);
							}
							else {
								//TODO: might need to add a warning message
								Variable* x = new Decimal(node->right->double_return, node->str_attr);
								_registry->registerVariable(node->left->str_attr, x);
							}

						}
						else if (node->right->is_int_return) {
							if (v->_getType() == Ast::INTEGER) {
								Integer* x = dynamic_cast<Integer*>(v);
								x->setVal(node->right->int_return);
							}
							else {
								//TODO: might need to add a warning message
								Variable* x = new Integer(node->right->int_return, node->str_attr);
								_registry->registerVariable(node->left->str_attr, x);
							}

						}
						else if (node->right->is_str_return) {
							if (v->_getType() == Ast::STRING) {
								String* x = dynamic_cast<String*>(v);
								x->setVal(node->right->str_attr);
							}
							else {
								//TODO: might need to add a warning message
								Variable* x = new String(node->right->str_return, node->str_attr);
								_registry->registerVariable(node->left->str_attr, x);
							}
						}
						else if (node->right->is_symbolic_return) {
							//TODO: complete symbolic assignment that is not of the 3 basic types. 
							int a = 1; //just so I have something to set a break point on.
						}
					}
				}
			}

				break;

			}

			//End Operation, clear the return vals.
			Ast::clearReturnVal(node->left);
			Ast::clearReturnVal(node->right);
			break;
		}
		case Ast::UNARY:
			//TODO:complete this
			Ast::clearReturnVal(node->left);
			break;
		case Ast::CALL: {
			//TODO: modify this. Only supports print right now for testing purposes

			if (node->str_attr == "_print") {
				Ast::Exp* arg = node->arguments->back();
				post_order_walk(arg);
				if (arg->is_int_return) {
					std::cout << arg->int_return << std::endl;
				}
				else if (arg->is_double_return) {
					std::cout << arg->double_return << std::endl;

				}
				else if (arg->is_str_return) {
					std::cout << arg->str_return << std::endl;
				}
			}
			else {
				Ast::Exp* fun = _fun_registry->getFunction(node->left->str_attr);
				
				if (node->arguments->size() != fun->arguments->size()) {
					std::cerr << "Compiler: size of arugments mismatch at ln:" << node->ln << " col:" << node->col;
				}
				else {
					runFunction(fun, node);
				}

			}


			break;
		}
		case Ast::INTEGER:
			node->is_int_return = true;
			node->int_return = node->int_attr;

			break;
		case Ast::DECIMAL:
			node->is_double_return = true;
			node->double_return = node->double_attr;
			break;
		case Ast::STRING:
			node->is_str_return = true;
			node->str_attr = node->str_attr;
			break;

		case Ast::VARIABLE: {
			// if the variable is of the 3 basic data types (int, double or string) we just decay it into one of the 3 data types.
			//TODO: add other dataTypes;

			std::string label = node->str_attr;
			Variable* v = _registry->getVariable(label);
			if (v == nullptr) {

				node->is_symbolic_return = true;
			}else{
				switch (v->_getType()) {
				case Ast::INTEGER: {
					Integer* x = dynamic_cast<Integer*>(v);
					node->is_int_return = true;
					node->int_return = x->getVal();
					break;
				}
				case Ast::DECIMAL: {
					Decimal* x = dynamic_cast<Decimal*>(v);
					node->is_double_return = true;
					node->double_return = x->getVal();
					break;
				}
				case Ast::STRING: {
					String* x = dynamic_cast<String*>(v);
					node->is_str_return = true;
					node->str_return = x->getVal();
					break;
				} default: {
					std::cerr << "Compiler: Unknown Variable Type ln:" << node->ln << " col:" << node->col;
					exit(1);
				}
				}
			}

		}
	}
}

void Interpreter::code_block_walk(Ast::Exp * node)
{

	switch (node->expType) {
		case Ast::FOR: {

			Ast::Exp* ctrl = node->left;
			post_order_walk(ctrl);
			if (ctrl->is_int_return) {
				for (int i = 0; i < ctrl->int_return; i++) {
					_registry->new_child_scope();

					int instruction = execute_args(node);
					if ( instruction == BREAK) {
						break;
					}
					else if (instruction == CONTINUE){
						continue;
					}

					_registry->destroy_child_scope();
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

				_registry->new_child_scope();

				int instruction = execute_args(node);
				if (instruction == BREAK) {
					break;
				}
				else if (instruction == CONTINUE) {
					continue;
				}

				_registry->destroy_child_scope();

				
			}

			break;
		}

		case Ast::IF: {
			Ast::Exp* condition = node->left;
			post_order_walk(condition);
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
			

			_registry->new_child_scope();

			execute_args(node);

			_registry->destroy_child_scope();

			break;
		}

		case Ast::CODE_BLK: {
			_registry->new_child_scope();

			execute_args(node);

			_registry->destroy_child_scope();

			break;
		}

	}
}

int Interpreter::execute_args(Ast::Exp*node) {
	//a return value of 1 means exit the current code block

	std::list<Ast::Exp*>* arguments = node->arguments;
	std::list<Ast::Exp*>::iterator it;
	for (it = arguments->begin(); it != arguments->end(); it++) {
		Ast::Exp* e = *it;
		if (e->expType == Ast::INSTR) {
			return e->int_attr;
		}
		post_order_walk(e);
	}
	return 0;
}

void Interpreter::runFunction(Ast::Exp * function, Ast::Exp * node)
{
	//we temporarily save the current registry and initialize a new independent registry 
	//for the function
	Registry* temp = _registry;
	_registry = new Registry();
	_registry->new_child_scope();

	//Declaring and initializing parameters
	std::list<Ast::Exp*>::iterator it1 = function->arguments->begin();
	std::list<Ast::Exp*>::iterator it2 = node->arguments->begin();
	for (; it1 != function->arguments->end() && it2 != function->arguments->end(); it1++, it2++) {
		Ast::Exp* param = *it1;
		Ast::Exp* val = *it2;
		post_order_walk(val);


		if (val->is_double_return) {
			Variable* x = new Decimal(val->double_return, param->str_attr);
			_registry->registerVariable(param->str_attr, x);

		}
		else if (val->is_int_return) {

			Variable* x = new Integer(val->int_return, param->str_attr);
			_registry->registerVariable(param->str_attr, x);
			int abc = 1;

		}
		else if (val->is_str_return) {
			Variable* x = new String(val->str_return, param->str_attr);
			_registry->registerVariable(param->str_attr, x);
		}
		else if (val->is_symbolic_return) {
			//TODO: complete symbolic assignment that is not of the 3 basic types. 
		}

	}

	//the codeBlock containing the function body is stored in the left
	execute_args(function->left);

	//we now destory the function registry and set the _registry pointer
	//to point back to the main registry
	_registry->destroy_child_scope();
	delete _registry;
	_registry = temp;
}



