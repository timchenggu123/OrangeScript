#ifndef FUNREGISTRY_H
#define FUNREGISTRY_H


#include <map>
#include <string>
#include <List>
#include "AbstractDataType.h"
#include "Ast.h"

class FunRegistry {
public:
	FunRegistry();
	~FunRegistry();
	Ast::Exp* getFunction(std::string label);

	bool registerFunction(std::string label, Ast::Exp* function);
	Ast::Exp* searchCache(std::string label);
	void addToCache(std::string label, Ast::Exp* function);
	void clearCache();
private:
	int cache_size = 20; //this is fairly aribitrary, may need to change it.
	std::map<std::string, Ast::Exp*> *LUT;
	std::map<std::string, Ast::Exp* > *LUT_cache;
	std::map<std::string, int> *LUT_cache_precedence;


};


#endif // !REGISTRY_H