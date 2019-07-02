#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#include <string>
#include <cctype>

class Trie;

class Trie_node
{
  private:
	Trie_node **children;
	bool is_terminal;
	static int const CHARACTERS = 26;

  public:
	Trie_node();
	Trie_node *child(int) const;

	bool member(std::string const &, int) const;

	bool insert(std::string const &, int);
	bool erase(std::string const &, int, Trie_node *&);
	void clear();

	friend class Trie;

	// if ptr is a pointer to a Trie_node object
	// in one of the friendly classes, you should:
	//    use   ptr->next_   to modify it
	//    use   ptr->next()      to access it
};

Trie_node::Trie_node() : children(nullptr),
						 is_terminal(false)
{
	// empty constructor
}

Trie_node *Trie_node::child(int n) const
{
	if (children == nullptr)
	{
		return nullptr;
	}
	else
	{
		return children[n];
	}
}

bool Trie_node::member(std::string const &str, int depth) const
{

	if (depth == str.length())
	{
		return is_terminal;
	}
	int index = (int)str[depth];
	index = index - 65;
	if (child(index) != nullptr)
	{
		return child(index)->member(str, ++depth);
	}
	return false;
}

bool Trie_node::insert(std::string const &str, int depth)
{
	if (depth == str.length())
	{	
		if (is_terminal){
			return false;
		}
		this -> is_terminal = true;
		return true;
	}
	int index = (int)str[depth];
	index = index - 65;
	if (child(index) == nullptr)
	{
		if (children == nullptr)
		{
			children = new Trie_node *[CHARACTERS];
			for (int i = 0; i < 26; i++){
				children[i] = nullptr;
			}
		}
		children[index] = new Trie_node();
		return child(index)->insert(str, ++depth);
	}else
	{
		return child(index)->insert(str, ++depth);
	}
	
	return false;
}

bool Trie_node::erase(std::string const &str, int depth, Trie_node *&ptr_to_this)
{
	if (depth == str.length())
	{	
		is_terminal = false;
		// if is leaf node, delete. 
		if (children == nullptr){
			delete ptr_to_this;
			ptr_to_this = nullptr;
			return true;
		}
		for (int i = 0; i < CHARACTERS ; i++){
			if (child(i) != nullptr){
				return true;
			}
		}
		delete[] children;
		children = nullptr;
		delete ptr_to_this;
		ptr_to_this = nullptr;
		return true;
	}

	int index = (int)str[depth];
	index = index - 65;
	if (child(index) != nullptr){
		if (child(index)->erase(str, ++depth, children[index])){
			//if the current node is a terminal node, do nothing and return
			if (is_terminal){
				return true;
			}
			// if any children found, do nothing and return
			for (int i = 0; i < CHARACTERS ; i++){
				if (child(i) != nullptr){
					return true;
				}
			}

			// if the children is empty, delete node and children[]
			delete[] children;
			children = nullptr;
			delete ptr_to_this;
			ptr_to_this = nullptr;
			return true;

		}else
		{
			return false;
		}
	}
	return false;
}

void Trie_node::clear()
{
	if (children != nullptr)
	{
		for (int i = 0; i < 26; i++)
		{
			if (children[i] != nullptr){
				children[i]->clear();
			}
		}
		delete[] children;
		children = nullptr;
	}
	delete this;
}


#endif
