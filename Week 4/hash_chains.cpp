#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <fstream>
//#include <sstream>

using std::string;
using std::vector;
using std::cin;
using std::getline;

struct Query {
	string type, s;
	size_t ind;
};

struct hashTable {
	vector<string> elems;
};

class QueryProcessor {
	int bucket_count;
	vector<hashTable> myHashTable;

	

	size_t hash_func(const string& s) const {   
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			//hash = (hash * multiplier + s[i]) % prime;
			hash = ((hash * multiplier + s[i]) % prime + prime) % prime;
		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {
		myHashTable.resize(bucket_count);
	}



	Query readQuery() const {
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}
	/*Query readQueryFromFile(std::ifstream &sampleFile) const {
		Query query;
		getline(sampleFile, query.type);
		if (query.type != "check")
			getline(sampleFile, query.s);
		else
		{
			string text = "sample text to allocate more data.....";
			getline(sampleFile, text);
			query.ind = std::stoi(text);
		}
		return query;
	}*/

	void writeSearchResult(bool was_found) const {
		std::cout << (was_found ? "yes\n" : "no\n");
	}

	void processQueryMSM(const Query& query) {
		if (query.type == "check") {
			// use reverse order, because we append strings to the end
			for (int i = static_cast<int>(myHashTable[query.ind].elems.size()) - 1; i >= 0; --i)
				std::cout << myHashTable[query.ind].elems[i] << " ";
			std::cout << "\n";

		} 
		else {
			size_t temp = hash_func(query.s);
			vector<string>::iterator it = std::find(myHashTable[temp].elems.begin(), myHashTable[temp].elems.end(), query.s);
			if (query.type == "find")
				writeSearchResult(it != myHashTable[temp].elems.end());
			else if (query.type == "add") {
				if (it == myHashTable[temp].elems.end())
					myHashTable[temp].elems.push_back(query.s);
			}
			else if (query.type == "del") {
				if (it != myHashTable[temp].elems.end())
					myHashTable[temp].elems.erase(it);
			}
		}
	}

	//void processFileQueryMSM(const Query& query, std::ifstream &checkFile) {
	//	string tempAnswer = "";
	//	
	//	if (query.type == "check") {
	//		// use reverse order, because we append strings to the end
	//		for (int i = static_cast<int>(myHashTable[query.ind].elems.size()) - 1; i >= 0; --i)
	//			tempAnswer += myHashTable[query.ind].elems[i] + " ";
	//		tempAnswer = "\n";

	//	}
	//	else {
	//		size_t temp = hash_func(query.s);
	//		vector<string>::iterator it = std::find(myHashTable[temp].elems.begin(), myHashTable[temp].elems.end(), query.s);
	//		if (query.type == "find")
	//			tempAnswer = (it != myHashTable[temp].elems.end()) ? "yes\n" : "no\n";
	//		else if (query.type == "add") {
	//			if (it == myHashTable[temp].elems.end())
	//				myHashTable[temp].elems.push_back(query.s);
	//		}
	//		else if (query.type == "del") {
	//			if (it != myHashTable[temp].elems.end())
	//				myHashTable[temp].elems.erase(it);
	//		}
	//	}
	//	if (tempAnswer != "")
	//	{
	//		string text;
	//		getline(checkFile, text);
	//		if (text != tempAnswer)
	//			std::cout << "Wrong Answer = " << tempAnswer << " Correct = " << text << std::endl;
	//		else
	//			std::cout << "Right Answer = " << tempAnswer << std::endl;
	//	}
	//}

	void processQueries() {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			processQueryMSM(readQuery());
	}

	/*void processFileQueries(std::ifstream &checkFile, std::ifstream &inputFile) {
		int n;
		string text;
		getline(inputFile, text);
		n = std::stoi(text);
		for (int i = 0; i < n; ++i)
			processFileQueryMSM(readQueryFromFile(inputFile), checkFile);
	}*/
};

int main() {
	std::ios_base::sync_with_stdio(false);
	int bucket_count;

	//////////////////for file test cases//////////////////////////
	//string relativePath = "../../tests/06";

	//
	//std::ifstream inputFile, checkFile;
	//inputFile.open(relativePath);
	//checkFile.open(relativePath + ".a");

	//if (!inputFile.is_open() || !checkFile.is_open())
	//{
	//	std::cout << "Error opening the files \n";
	//	return 0;
	//}
	//string text = "sample text to allocate more data.....";
	//getline(inputFile, text);
	//bucket_count = std::stoi(text);
	//QueryProcessor proc(bucket_count);
	//proc.processFileQueries(checkFile, inputFile);
	//checkFile.close();
	//inputFile.close();
	/////////////////////for file test cases//////////////////////////


	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQueries();
	return 0;
}
