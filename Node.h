#pragma once
#include <fstream>
#include <iostream>
#include <memory>
using uchar = unsigned char;
using namespace std;

class Node
{
private:
	string name{ "" };
	uchar ch{ 0 };
	int freq{ 0 };
	string code_string{""};
public:
	using pointer = shared_ptr<Node>;

	pointer left{ nullptr };
	pointer right{ nullptr };
	pointer parent{ nullptr };

	Node() = default;
	Node(uchar uch, int f) : ch(uch), freq(f) {}
	Node(const string& n, int f) : name(n), freq(f) {}

	//bool operator<(const Node& oth) const;

	friend ostream& operator<<(ostream& os, const Node& node);

	bool isleaf()const { return (left == nullptr && right == nullptr); }
	uchar getbyte() const { return ch; }
	string getname() const;
	int getfreq()const { return freq; }
	void setfreq(int f) { freq = f; }
	string code() const { return code_string; }
	void code(const string& c) { code_string = c; }
};

ostream& operator<<(ostream& os, const Node& node);
