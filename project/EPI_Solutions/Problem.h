#pragma once
#include <string>
#include <iostream>

class Problem {
public:
	explicit Problem(const std::string& name) : name_(name) {
		std::cout << std::endl;
		std::cout << "==================================================================" << std::endl;
		std::cout << name_ << std::endl;
		std::cout << "==================================================================" << std::endl;
	};
	virtual ~Problem() = default;
private:
	std::string name_ = "";
};