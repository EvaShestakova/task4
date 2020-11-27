#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include "Node.h"
#include "LowestPriority.h"
using namespace std;
using queue_t = priority_queue<Node::pointer, vector<Node::pointer>, LowestPriority>;

ifstream::pos_type getsize(const string& fn);

void readfile(const string& fl, vector<int>& freq);

void makecode(Node::pointer& node, string str, vector<string>& codes);

void fillqueue(vector<int>& freq, queue_t& queue);

void buildtree(queue_t& queue);

string message2code(const string& filename, const vector<string>& codes);

void writefile(const string& filename, vector<int>& freq, const queue_t& queue, const string& message); 

void read_decoding_file(string& filename, vector<int>& freq, string& message); 

void make_char(const Node::pointer& root, const string& message, const string& filename);

void write_decoding_file(const string& filename, const string& text);

void zip(const string& filename);

void unzip(string& filename);
