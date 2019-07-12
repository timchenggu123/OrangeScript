#ifndef TRIE_NODE_H
#define TRIE_NODE_H

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




#endif
