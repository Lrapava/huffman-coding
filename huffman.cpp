// Lrapava, Date: 1636806718

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <set>

// Each char takes up 1 byte (8 bits) of ram
// This means that there are 2^8 = 256 possible values of char
// I couldn't see most of them in the terminal
// So, to make output a bit shorter, I decided to display
// visible characters only by default

#define VISIBLE_ONLY true

int charNum = (int)('~') - (int)('!'), charStart = (int)('!'), charEnd = (int)('~') + 1;

std::vector <std::string> GenerateCodes(std::string s) {
	std::vector <std::pair <int, std::pair<int, int>>> graph;
	std::set <std::pair <int, int>> st;
	int f[256]{0}; 
	
	for (char c : s) f[(int)c]++;
	for (int i = 0; i < 256; i++) {
		graph.push_back({f[i], {-1, -1}});
		st.insert({f[i], i});
	}

	while (st.size() > 1) {
		auto fst = *(st.begin()); st.erase(st.begin());
		auto snd = *(st.begin()); st.erase(st.begin());
		graph.push_back({fst.first + snd.first, {fst.second, snd.second}});
		st.insert({fst.first + snd.first, graph.size() - 1});
	}

	std::vector <std::string> codes(graph.size(), ""), res(256);
	std::queue <std::pair <int, int>> q;
	
	q.push({graph.size() - 1, -1});

	while (q.size() > 0) {
		auto x = q.front(); q.pop();
		if (graph[x.first].second.first != -1) {
			q.push({graph[x.first].second.first, x.first});
			codes[graph[x.first].second.first] = "0";
		}
		if (graph[x.first].second.second != -1) {
			q.push({graph[x.first].second.second, x.first});
			codes[graph[x.first].second.second] = "1";
		}
		if (x.second != -1) codes[x.first] += codes[x.second];
	}

	for (int i = 0; i < 256; i++) {
		res[i] = codes[i];
		std::reverse(res[i].begin(), res[i].end());
	}

	return res;
	
}

int main() {
	std::cout << "Huffman encoding\nPlease enter some text:\n";
	std::string s; getline(std::cin, s);
	auto code = GenerateCodes(s);
	
	if (VISIBLE_ONLY) {
		for (int i = charStart; i < charEnd; i++) {
			std::cout << (char)(i) << " -> " << code[i] << "  ";
			for (int j = code[i].size(); j < 11; j++) std::cout << " ";
			if ((i - charStart) % 5 == 4) std::cout << "\n";
		}
	} else {
		for (int i = 0; i < 256; i++)
			std::cout << (char)(i) << " -> " << code[i] << "\n";
	}

	std::string data;
	for (char c : s) data += code[(int)c];

	std::cout << "\nData: " << data << "\n";
	std::cout << "Length of data (in bits): " << data.size() << "\n";
	std::cout << "Length of original message (in characters): " << s.size() << "\n";

}
