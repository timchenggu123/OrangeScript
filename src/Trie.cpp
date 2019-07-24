#include <stdexcept>
#include "Trie.h"
#include <iostream>
#include <string>
#include <cctype>

Trie::Trie() :
	root_node(nullptr),
	trie_size(0) {
	// empty constructor
}

Trie::~Trie() {
	clear();
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	if (size() == 0) {
		return true;
	}
	return false;
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member(std::string const &str) const {
	std::string str1 = str;
	for (int i = 0; i < str1.length(); i++) {
		str1[i] = toupper(str1[i]);
		int value = (int)str1[i];
		if (value < 65 || value >90) {
			std::cerr << "Trie Error: invalid argument";
		}
	}
	if (root() == nullptr) {
		return false;
	}
	return root_node->member(str1, 0);
}

bool Trie::insert(std::string const &str) {
	std::string str1 = str;
	for (int i = 0; i < str1.length(); i++) {
		str1[i] = toupper(str1[i]);
		int value = (int)str1[i];
		if (value < 65 || value >90) {
			std::cerr << "Trie Error: invalid argument";
		}
	}
	if (root() == nullptr) {
		root_node = new Trie_node();
	}
	if (root()->insert(str1, 0)) {
		++trie_size;
		return true;
	}
	return false;
}

bool Trie::erase(std::string const &str) {
	std::string str1 = str;
	for (int i = 0; i < str1.length(); i++) {
		str1[i] = toupper(str1[i]);
		int value = (int)str1[i];
		if (value < 65 || value >90) {
			std::cerr << "Trie Error: invalid argument";
		}
	}

	if (size() == 0) {
		return false;
	}

	if (member(str1)) {
		Trie_node *ptr = nullptr;
		if (root()->erase(str1, 0, ptr)) {
			trie_size = trie_size - 1;
			if (trie_size == 0) {
				clear();
			}
			return true;
		}
	}
	return false;
}

void Trie::clear() {
	if (root() != nullptr) {
		root()->clear();
		root_node = nullptr;
	}
	trie_size = 0;
}
