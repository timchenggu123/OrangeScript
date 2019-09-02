#include "FunRegistry.h"

FunRegistry::FunRegistry() :
	LUT(new std::map<std::string, Ast::Exp*>),
	LUT_cache(new std::map<std::string, Ast::Exp*>()),
	LUT_cache_precedence(new std::map<std::string, int>())
{

}

FunRegistry::~FunRegistry()
{
	//TODO: needs to check to see if the stack is empty
	//if not, there might be a risk of memory leak
	delete LUT;
	delete LUT_cache;
	delete LUT_cache_precedence;
}


Ast::Exp* FunRegistry::getFunction(std::string label)
{
	Ast::Exp* cache_result = searchCache(label);
	if (cache_result != nullptr) {
		return cache_result;
	}
	else {

		if (LUT->count(label) != 0) {
			addToCache(label, LUT->find(label)->second);
			return LUT->find(label)->second;
		}

		//TODO: throw segment fault here. 
		return nullptr;
	}
}

bool FunRegistry::registerFunction(std::string label, Ast::Exp * function)
{
	//this function registers new variables. we first search to see if the 
	//label has already been registered. If it has, then we will delete the old variable pointer
	//and replace it with the new one. The function will return false this case. 
	//If the label has not been registered, we simply register the label and the 
	//variable pointer. The function will return true in this case. 

	Ast::Exp* exist = getFunction(label);
	if (exist != nullptr) {
		delete exist;
	}
	LUT->insert(std::pair < std::string, Ast::Exp*>(label, function));
	addToCache(label, function);

	return exist == nullptr ? true : false;
}


Ast::Exp* FunRegistry::searchCache(std::string label)
{
	if (LUT_cache->count(label) != 0) {

		Ast::Exp* v = LUT_cache->find(label)->second;

		int* precedence = &LUT_cache_precedence->find(label)->second;
		//we update the cache access precedence
		if (*precedence != 1) {
			*precedence = 1;
			std::map<std::string, int>::iterator it;
			for (it = LUT_cache_precedence->begin(); it != LUT_cache_precedence->end(); it++) {
				it->second++;
			}
		}

		return v;
	}
	else {
		return nullptr;
	}

}

void FunRegistry::addToCache(std::string label, Ast::Exp * function)
{
	if (LUT_cache_precedence->size() > 0) {
		std::map<std::string, int>::iterator it;
		std::string replace;
		int max_precedence;

		for (it = LUT_cache_precedence->begin(); it != LUT_cache_precedence->end(); it++) {
			if (it->second > max_precedence) {
				replace = it->first;
				max_precedence = it->second;
				it->second++;
			}
			else {
				it->second++;
			}
		}

		LUT_cache->erase(replace);
		LUT_cache_precedence->erase(replace);
	}

	LUT_cache->insert(std::pair<std::string, Ast::Exp*>(label, function));
	LUT_cache_precedence->insert(std::pair<std::string, int>(label, 1));

}

void FunRegistry::clearCache()
{
	std::map<std::string, Ast::Exp*>::iterator it;
	for (it = LUT_cache->begin(); it != LUT_cache->end(); it++) {
		delete it->second;
		it->second = nullptr;
	}

	LUT_cache->clear();
	LUT_cache_precedence->clear();

}
