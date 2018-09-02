#include <iostream>
#include <string>
#include <vector>


using std::string;
typedef unsigned long long ull;

struct Data {
	string pattern, text;
};

Data read_input() {
	Data data;
	std::cin >> data.pattern >> data.text;
	return data;
}

void print_occurrences(const std::vector<ull>& output) {
	for (ull i = 0; i < output.size(); ++i)
		std::cout << output[i] << " ";
	std::cout << "\n";
}


ull polyHash(const string& s, const int& x, const ull& p)
{
	///////////calculating polynomial Hash //////////////////////
	ull pHash = 0;
	for (long long i = static_cast<long long> (s.size()) - 1; i >= 0; --i)
		pHash = (pHash * x + s[i]) % p;
	return pHash;
}

std::vector<ull> preComputeHash(const string& s, const int substringSize, const int& x, const ull& p)
{
	///////////calculating polynomial Hash //////////////////////
	int textLength = s.size();
	std::vector< ull> H(textLength - substringSize + 1);
	string lastsubstring = s.substr(textLength - substringSize, substringSize);   //need to find other way instead of substring

	H[textLength - substringSize] = polyHash(lastsubstring, x, p);
	ull y = 1;
	for (ull i = 0; i < substringSize; i++)
		y = y*x % p;

	for (long long i = textLength - substringSize - 1; i >= 0; i--)
		H[i] = (x*H[i + 1] + s[i] - (y * s[i + substringSize] % p) + p) % p;

	return H;
}

bool isEqual(string s1, string s2) {
	if (s1.size() != s2.size())
		return false;
	for (int i = 0; i < s1.size(); ++i) 
		if (s1[i] != s2[i])
			return false;
	return true;
}

std::vector<int> get_occurrences(const Data& input) {
	const string& s = input.pattern, t = input.text;
	std::vector<int> ans;
	for (size_t i = 0; i + s.size() <= t.size(); ++i)
		if (t.substr(i, s.size()) == s)
			ans.push_back(i);
	return ans;
}

std::vector<ull> get_occurrences_MSM(const Data& input) {
	static const size_t multiplier = 263;
	static const ull prime = 1000000007;  // 100000000019 1000000007  1000000000100011
	const string& p = input.pattern, t = input.text;
	std::vector<ull> ans;

	ull pHash = polyHash(input.pattern, multiplier, prime);
	std::vector< ull> PreComputedHashes = preComputeHash(input.text, input.pattern.size(), multiplier, prime);

	for (ull i = 0; i + p.size() <= t.size(); ++i)
	{
		if (PreComputedHashes[i] != pHash)
			continue;
		if (isEqual(t.substr(i, p.size()), p))
			ans.push_back(i);
	}
	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	//print_occurrences(get_occurrences(read_input()));
	print_occurrences(get_occurrences_MSM(read_input()));
	return 0;
}
