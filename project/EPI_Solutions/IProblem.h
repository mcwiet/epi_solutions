#pragma once
#include <string>
#include <iostream>

class IProblem {
public:
	explicit IProblem(const std::string& name) : name_(name) {};
	virtual ~IProblem() = default;

	void PrintName() {
		std::cout << "==================================================================" << std::endl;
		std::cout << "C5 P1" << std::endl;
		std::cout << "==================================================================" << std::endl;
	}
private:
	std::string name_ = "";
};