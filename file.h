#pragma once 
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

namespace qsortp_debug 
{
	class FileWrite; 
	void printTuples(tuple<int, int> *tuples, int count);
	
	template<class T>
	void printArray(vector<T> &v)
	{
		for(auto i=0; i<v.size(); i++)
		{
			cout << "index: " << i << " " << v[i] << endl;
		}
	};
};


class qsortp_debug::FileWrite
{

	private: 
		ofstream myfile;


	public: 
		FileWrite(const char* fileName)
		{
			myfile.open (fileName);
		}

		~ FileWrite()
		{
			myfile.close();
		}
	
		ofstream& operator << (const char* str)
		{	 		
	 		myfile << str; 		

	 		return myfile;
		}	

		ofstream& operator << (const float f)
		{	 		
	 		myfile << f; 		

	 		return myfile;
		}	
};


void qsortp_debug::printTuples(tuple<int, int> *tuples, int count)
{
	for(auto i=0; i<count; i++)
	{
		auto start = get<0>(tuples[i]);
		auto end = get<1>(tuples[i]);

		cout << "Index: " << i << " Start: " << start << " End: " << end << endl;
	}
};




