#include<unordered_map>
#include<tuple>

template<class T, class T1>
class LRUCache {
public:
	std::unordered_map<T, std::tuple<T,T,T1>> cache; //<int, std::tuple<int*,int>> corresponds to int key, int prev_key, int next_key, int val;
	int _capacity;
	int _size;
	int _head;
	int _tail;

	LRUCache(int capacity) :
		cache({}),
		_capacity(capacity),
		_size(0),
		_head(-1),
		_tail(-1)
	{
	}

	T1 get(T key) {
		if (cache.count(key) == 0) {
			return -1;
		}
		else {
			//connecting previous node with the next;
			int prev_key = std::get<0>(cache[key]);
			int next_key = std::get<1>(cache[key]);
			if (prev_key == -1 && next_key == -1) {
				return std::get<2>(cache[key]);
			}
			if (_head == key) {
				return std::get<2>(cache[key]);
			}

			if (_tail == key) {
				_tail = prev_key;
				std::get<1>(cache[_tail]) = -1;
			}
			else {
				std::get<1><cache[prev_key]> = next_key;
				std::get<0>(cache[next_key]) = prev_key;
			}

			//move the current node to top
			std::get<0>(cache[_head]) = key;
			std::get<1>(cache[key]) = _head;
			std::get<0>(cache[key]) = -1;
			_head = key;

			return std::get<2>(cache[key]);
		}
	}

	void put(T key, T1 value) {
		if (get(key) != -1) {
			std::get<2>(cache[key]) = value;
			return;
		}

		if (_size == 0) {
			cache.insert(std::pair<int, std::tuple<int, int, T>>(key, std::make_tuple( -1,-1,value )));
			_head = key;
			_tail = key;
			_size++;
		}
		else if (_size < _capacity) {
			cache.insert(std::pair<int, std::tuple<int, int, T>>(key, std::make_tuple( -1,_head,value )));
			std::get<0>(cache[_head]) = key;
			_head = key;
			_size++;

		}
		else {
			//popping the tail
			if (_capacity == 1) {
				cache.erase(_head);
				cache.insert(std::pair<int, std::tuple<int, int, T>>(key, std::make_tuple( -1,-1,value )));
				_head = key;
				_tail = key;
				return;
			}
			int invalid_key = _tail;
			_tail = std::get<0>(cache[_tail]);
			std::get<1>(cache[_tail]) = -1;
			cache.erase(invalid_key);

			//insert the new node to top
			cache.insert(std::pair<int, std::tuple<int, int, T>>(key, std::make_tuple (-1, _head, value )));
			std::get<0>(cache[_head]) = key;
			_head = key;

		}

		void remove(int key) {
			if (cache.count(key) == 0) {
				return;
			}
			else {
				//connecting previous node with the next;
				int prev_key = std::get<0>(cache[key]);
				int next_key = std::get<1>(cache[key]);

				if (prev_key == -1 && next_key == -1) {
					cache.erase(key);
				}
				else if (_head == key) {
					_head = next_key;
					std::get<0>(cache[_head]) = -1;
					cache.erase(key);
				}

				else if (_tail == key) {
					_tail = prev_key;
					std::get<1>(cache[_tail]) = -1;
					cache.erase(key);
				}
				else {
					std::get<1><cache[prev_key]> = next_key;
					std::get<0>(cache[next_key]) = prev_key;
					cache.erase(key);
				}

				return;
			}
		}
	}
};