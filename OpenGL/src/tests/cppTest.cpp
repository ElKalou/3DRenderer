#include <iostream>
#include <vector>
#include <functional>

#define LOG(x) std::cout << x << std::endl

class Entity {
private:
	int b;
public:
	Entity(int& i) : b{ i } { 
		LOG(b); 
		i++;
	}
	void ChangeB(int newB) {
		b = newB;
		LOG(b);
	}

	void DisplayB() {
		LOG(b);
	}
};

void Sum(const std::vector<int> values,void(*func)(int)) {
	int r = 0;
	for (auto v : values) {
		func(v);
	}
}

void Print(int x) {
	LOG(x);
}

int main() {
	
	std::cout << "Hello" << std::endl;

	std::vector<int> a = { 1,4,5,6 };

	void(*function)(int) = Print;

	Sum(a, [](int v) {LOG(v); });

	std::cin.get();
	return 1;
}
