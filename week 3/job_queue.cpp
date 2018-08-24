#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>


using std::vector;
using std::cin;
using std::cout;
using std::string;


class JobQueue {
private:
	int num_workers_;
	vector<int> jobs_;

	string relativePath;
	string text;
	int temp;

	vector<int> assigned_workers_;
	vector<long long> start_times_;

	struct ThreadNumber {
		/*ThreadNumber(long long threadNumber, long long finishTime) : 
			threadNumber(threadNumber),
			finishTime(finishTime)
		{
		}*/
		long long threadNumber;
		long long finishTime;
	};

	vector<ThreadNumber> prQFinshTimes;

	void WriteResponse() const {
		for (int i = 0; i < jobs_.size(); ++i) {
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData() {
		int m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> jobs_[i];
	}

	void ReadFileData()
	{
		relativePath = "../../tests/08";
		std::ifstream sampleFile; 
		sampleFile.open(relativePath);
		int m, i = 0;
		if (sampleFile.is_open())
		{
			getline(sampleFile, text);
			std::stringstream  lineStream(text);
			for (int j = 0; j < 2; j++)
			{
				lineStream >> temp;
				if (j == 0)
					num_workers_ = temp;
				else
					m = temp;
			}
			jobs_.resize(m);

			getline(sampleFile, text);
			std::stringstream  lineStream2(text);
			while (lineStream2 >> temp)
			{
				jobs_[i] = temp;
				i++;
			}
		}
		sampleFile.close();
	}

	void siftDown(int i)
	{
		int minIndex = i;
		int leftChildIndex = 2 * i + 1, rightChildIndex = 2 * i + 2;
		if (prQFinshTimes.size() > leftChildIndex && prQFinshTimes[leftChildIndex].finishTime <= prQFinshTimes[minIndex].finishTime)
		{
			
			if (prQFinshTimes[leftChildIndex].finishTime < prQFinshTimes[minIndex].finishTime)
			{
				minIndex = leftChildIndex;
			}
			else if (prQFinshTimes[leftChildIndex].threadNumber < prQFinshTimes[minIndex].threadNumber)
			{
				minIndex = leftChildIndex;
			}
		}
		if (prQFinshTimes.size() > rightChildIndex && prQFinshTimes[rightChildIndex].finishTime <= prQFinshTimes[minIndex].finishTime)
		{

			if (prQFinshTimes[rightChildIndex].finishTime < prQFinshTimes[minIndex].finishTime)
			{
				minIndex = rightChildIndex;
			}
			else if (prQFinshTimes[rightChildIndex].threadNumber < prQFinshTimes[minIndex].threadNumber)
			{
				minIndex = rightChildIndex;
			}
		}
		if (i != minIndex)
		{
			std::swap(prQFinshTimes[i], prQFinshTimes[minIndex]);
			siftDown(minIndex);
		}

	}

	void AssignJobs() {
		// TODO: replace this code with a faster algorithm.
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		vector<long long> next_free_time(num_workers_, 0);
		for (int i = 0; i < jobs_.size(); ++i) {
			int duration = jobs_[i];
			int next_worker = 0;
			for (int j = 0; j < num_workers_; ++j) {
				if (next_free_time[j] < next_free_time[next_worker])
					next_worker = j;
			}
			assigned_workers_[i] = next_worker;
			start_times_[i] = next_free_time[next_worker];
			next_free_time[next_worker] += duration;
		}
	}

	void AssignJobsMSM() 
	{
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		prQFinshTimes.resize(num_workers_);
		for (int i = 0; i < num_workers_; i++)
		{
			prQFinshTimes[i].finishTime = 0;
			prQFinshTimes[i].threadNumber = i;
		}
		for (int i = 0; i < jobs_.size(); ++i)
		{
			//assigned_workers_[i] = next_free_time[0];
			assigned_workers_[i] = prQFinshTimes[0].threadNumber;
			start_times_[i] = prQFinshTimes[0].finishTime;
			prQFinshTimes[0].finishTime += jobs_[i];
			siftDown(0);
		}
	}

	void CheckFileResoponse()
	{
		std::ifstream checkFile;
		relativePath += ".a";
		checkFile.open(relativePath);

		if (checkFile.is_open())
		{
			for (int i = 0; i < jobs_.size(); ++i)
			{
				getline(checkFile, text);					// inputs are the parents against the index (input position)
				std::stringstream  lineStream(text);
				bool hit = true;
				while (lineStream >> temp)
				{
					if (hit)
					{
						if (temp != assigned_workers_[i])
							cout << "Job Number " << i << " , Assigned Worker is wrong";
						hit = false;
					}
					else
					{
						if (temp != start_times_[i])
							cout << "Job Number " << i << " Start Time is wrong";
						hit = true;
					}
				}
			}
			checkFile.close();
		}
	}


public:
	void Solve() {
		ReadData();
		//ReadFileData();
		//AssignJobs();
		AssignJobsMSM();
		WriteResponse();
		//CheckFileResoponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	return 0;
}
