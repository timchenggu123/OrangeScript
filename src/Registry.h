#ifndef REGISTRY_H
#define REGISTRY_H


#include <map>
#include <string>
#include <List>
#include "Variable.h"

class Registry {
public:
	Registry();
	~Registry();
	void new_child_scope();
	void destroy_child_scope();
	Variable* getVariable(std::string label);
	
	bool registerVariable(std::string label, Variable* variable);
	Variable* searchCache(std::string label);
	void addToCache(std::string label, Variable* variable);
	void clearCache();
private:
	int cache_size = 20; //this is fairly aribitrary, may need to change it.
	std::list < std::map<std::string, Variable*>*> *LUT_stack;
	std::map<std::string, Variable*> *LUT_cache;
	std::map<std::string, int> *LUT_cache_precedence;


};


#endif // !REGISTRY_H