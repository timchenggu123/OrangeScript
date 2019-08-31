#include "Registry.h"

Registry::Registry() :
	LUT_stack(new std::list < std::map<std::string, Variable*>*>),
	LUT_cache(new std::map<std::string, Variable*>)
{

}

Registry::~Registry()
{
	//TODO: needs to check to see if the stack is empty
	//if not, there might be a risk of memory leak
	delete LUT_stack;
}

void Registry::new_child_scope()
{
	LUT_stack->push_back(new std::map<std::string, Variable*>);

}

void Registry::destroy_child_scope()
{
	std::map<std::string, Variable*>* child = LUT_stack->back();
	LUT_stack->pop_back();

	//we first clear the cache entries that are now out of scope
	std::map<std::string, Variable*>::iterator it1;
	for (it1 = LUT_cache->begin(); it1 != LUT_cache->end(); it1++) {
		if (child->count(it1->first) != 0) {
			LUT_cache->erase(it1->first);
			LUT_cache_precedence->erase(it1->first);
		}
	}

	//we now delete the variable pointers in the actual map
	std::map<std::string, Variable*>::iterator it;
	for (it = child->begin(); it != child->end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
	delete child;

}

Variable* Registry::getVariable(std::string label)
{
	Variable* cache_result = searchCache(label);
	if (cache_result != nullptr) {
		return cache_result;
	}
	else {
		std::list < std::map<std::string, Variable*>*>::iterator it;
		for (it = LUT_stack->begin(); it != LUT_stack->end(); it++) {
			std::map<std::string, Variable*>* map = *it;
			if (map->count(label) != 0) {
				addToCache(label, map->find(label)->second);
				return map->find(label)->second;
			}
		}

		//TODO: throw segment fault here. 
		return nullptr;
	}
}

bool Registry::registerVariable(std::string label, Variable * variable)
{
	if (getVariable(label) != nullptr) {
		std::map<std::string, Variable*>* current_scope = LUT_stack->back();
		current_scope->insert(std::pair < std::string, Variable*>(label, variable));
		return true;
	}
	else {
		return false;
	}
	
}

Variable* Registry::searchCache(std::string label)
{
	if (LUT_cache->count(label) != 0) {

		Variable* v = LUT_cache->find(label)->second;

		int* precedence = &LUT_cache_precedence->find(label)->second;
		//we update the cache access precedence
		if (*precedence != 1) {
			*precedence = 1;
			std::map<std::string, int>::iterator it;
			for (it = LUT_cache_precedence->begin(); it != LUT_cache_precedence->end(); it++) {
				it->second++;
			}
		}

		return v ;
	}
	else {
		return nullptr;
	}

}

void Registry::addToCache(std::string label, Variable * variable)
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

	LUT_cache->insert(std::pair<std::string, Variable*>(label, variable));
	LUT_cache_precedence->insert(std::pair<std::string, int>(label, 1));

}

void Registry::clearCache()
{
	std::map<std::string, Variable*>::iterator it;
	for (it = LUT_cache->begin(); it != LUT_cache->end(); it++) {
		delete it->second;
		it->second = nullptr;
	}

	LUT_cache->clear();
	LUT_cache_precedence->clear();

}
