#include "Registry.h"

Registry::Registry() :
	LUT_stack(new std::list < std::map<std::string, Variable*>*>),
	LUT_cache(new std::map<std::string, Variable*>()),
	LUT_cache_precedence(new std::map<std::string, int>())
{

}

Registry::~Registry()
{
	//TODO: needs to check to see if the stack is empty
	//if not, there might be a risk of memory leak
	delete LUT_stack;
	delete LUT_cache;
	delete LUT_cache_precedence;
}

void Registry::new_child_scope()
{
	LUT_stack->push_back(new std::map<std::string, Variable*>);

}

void Registry::destroy_child_scope()
{
	std::map<std::string, Variable*>* child = LUT_stack->back();
	LUT_stack->pop_back();

	if (LUT_cache->size() != 0) {
		std::map<std::string, Variable*>::iterator it;
		std::list<std::string>* list_to_delete = new std::list<string>;
		for (it = LUT_cache->begin(); it != LUT_cache->end(); it++) {
			//we loop through cache and check to see if it exists in child
			//If so, add to list_to_be_deleted;
			if (child->count(it->first) != 0) {
				list_to_delete->push_back(it->first);
			}
		}
		std::list<std::string>::iterator it1;
		for (it1 = list_to_delete->begin(); it1 != list_to_delete->end(); it1++) {
			LUT_cache->erase(*it1);
			LUT_cache_precedence->erase(*it1);
		}

		delete list_to_delete;
	}
	//we first clear the cache entries that are now out of scope

	//we now delete the variable pointers in the actual map
	if (child->size() != 0) {
		std::map<std::string, Variable*>::iterator it;
		for (it = child->begin(); it != child->end(); it++)
		{
			delete it->second;
			it->second = nullptr;
		}
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
	//this function registers new variables. we first search to see if the 
	//label has already been registered. If it has, then we will delete the old variable pointer
	//and replace it with the new one. The function will return false this case. 
	//If the label has not been registered, we simply register the label and the 
	//variable pointer. The function will return true in this case. 

	Variable* exist = getVariable(label);
	if (exist != nullptr) {
		delete exist;
	}
	std::map<std::string, Variable*>* current_scope = LUT_stack->back();
	current_scope->insert(std::pair < std::string, Variable*>(label, variable));
	addToCache(label, variable);
		
	return exist == nullptr ? true: false;
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
