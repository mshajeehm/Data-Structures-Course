#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>


using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
using std::string;
using std::getline;

class HeapBuilder {
private:
	vector<int> data_;
	vector< pair<int, int> > swaps_;
	string relativePath;
	string text;
	int temp;

	void WriteResponse() const {
		cout << swaps_.size() << "\n";
		for (int i = 0; i < swaps_.size(); ++i) {
			cout << swaps_[i].first << " " << swaps_[i].second << "\n";
		}
	}
	void CheckFileResoponse()
	{
		std::ifstream checkFile;
		relativePath += ".a";
		checkFile.open(relativePath);

		if (checkFile.is_open())
		{
			getline(checkFile, text);
			if ((swaps_.size()) == stoi(text)) {
				std::cout << "Total count is True" << std::endl;
			}
			else
			{
				std::cout << "Total count is False" << text << std::endl;
			}
			for (int i = 0; i < swaps_.size(); ++i) 
			{
				getline(checkFile, text);					// inputs are the parents against the index (input position)
				std::stringstream  lineStream(text);
				bool hit = true;
				while (lineStream >> temp)
				{
					if (hit)
					{
						if (temp != swaps_[i].first)
							cout << "Swap Number " << i << " , Left is wrong";
						hit = false;
					}
					else
					{
						if (temp != swaps_[i].second)
							cout << "Swap Number " << i << " Right is wrong";
						hit = true;
					}
				}
			}
			checkFile.close();
		}
	}

	void ReadData() {
		int n;
		cin >> n;
		data_.resize(n);
		for (int i = 0; i < n; ++i)
			cin >> data_[i];
	}
	void ReadFileData() {

		relativePath = "../../tests/04";
		std::ifstream sampleFile;  int i = 0;
		sampleFile.open(relativePath);

		if (sampleFile.is_open())
		{
			getline(sampleFile, text);

			int n = std::stoi(text);
			data_.resize(n);

			getline(sampleFile, text);					// inputs are the parents against the index (input position)
			std::stringstream  lineStream(text);
			while (lineStream >> temp)
			{
				data_[i] = temp;
				i++;
			}
		}
		sampleFile.close();
	}

	void siftDown(int i) 
	{
		int minIndex = i;
		int leftChildIndex = 2 * i + 1, rightChildIndex = 2 * i + 2;
		if (data_.size() > leftChildIndex && data_[leftChildIndex] < data_[minIndex])
		{
			minIndex = leftChildIndex;
		}
		if (data_.size() > rightChildIndex && data_[rightChildIndex] < data_[minIndex])
		{
			minIndex = rightChildIndex;
		}
		if (i != minIndex)
		{
			swap(data_[i], data_[minIndex]);
			swaps_.push_back(make_pair(i, minIndex));
			siftDown(minIndex);
		}

	}
	void GenerateSwaps() {
		swaps_.clear();
		// The following naive implementation just sorts 
		// the given sequence using selection sort algorithm
		// and saves the resulting sequence of swaps.
		// This turns the given array into a heap, 
		// but in the worst case gives a quadratic number of swaps.
		//
		// TODO: replace by a more efficient implementation

		/*for (int i = 0; i < data_.size(); ++i) {
			for (int j = i + 1; j < data_.size(); ++j) {
				if (data_[i] > data_[j]) {
					swap(data_[i], data_[j]);
					swaps_.push_back(make_pair(i, j));
				}
			}
		}*/
		///////////MSM Code ////////////
		int maxPossibleElem = pow(2, floor(log2(data_.size()) + 1)) - 1;

		for (int i = (maxPossibleElem /2)-1; i >= 0; i--)
		{
			//int parent = data_[i], leftChild = data_[2 * i + 1], rightChild = data_[2 * i + 2];
			siftDown(i);
		}
	}

public:
	void Solve() {
		ReadData();
		//ReadFileData();
		GenerateSwaps();
		WriteResponse();
		//CheckFileResoponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	HeapBuilder heap_builder;
	heap_builder.Solve();
	return 0;
}
