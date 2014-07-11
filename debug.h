/**************************************************************************************************************
Helper namespace for debug purposes
***************************************************************************************************************/
#pragma once 
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

namespace qsortp_debug 
{
	class FileWrite; 
	struct Vertex;
	void printTuples(tuple<int, int> *tuples, int count);
	void fillWithRandomFloat(vector<float> &arr, int count);
	void fillWithRandomVertex(vector<Vertex> &arr, int count);

	template<class T>
	void printvector(vector<T> &arr) 
	{
		auto size = arr.size();
		cout<<"Size of array: " << size <<endl;
		for(auto i=0; i<size; i++) 
		{
			cout<<"i:" << i << " [" << arr[i] << "]" <<",";
		}

		cout<<endl;
	};

	template <class T>
	void writofile(vector<T> &arr, const char* fname)
	{
		 cout << "Save to file: " << fname;
		 FileWrite myfile(fname);  	
		 for(auto i=0; i<arr.size(); i++) 
		 {
	 		myfile << "[" << i << "] " << arr[i] <<", ";
		 }	

		 cout<<"Done"<<endl;
	};

	//checks if array is sorted
	template<class T>
	bool isSorted(vector<T> &arr)
	{
		if(arr.size()<=1)
			return true; 

		for(auto i=1;i<arr.size()-1; i++)
		{
			if(arr[i] > arr[i+1])
				return false; 
		}

		return true;
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

//Sample Vertex class 
struct qsortp_debug:: Vertex 
{
	private:
		float x,y,z;
	public:
		
		Vertex() {}
		Vertex(float a, float b, float c):x(a),y(b),z(c){}


		//MoreThen  implementation for sorting support 
		bool operator > (const Vertex& other){
			float thisDistance = getDistanceFrom0(*this);
			float otherDistance = getDistanceFrom0(other);
			return thisDistance > otherDistance;
		}

		//LessThen  implementation for sorting support 
		bool operator < (const Vertex& other){			
			float thisDistance = getDistanceFrom0(*this);
			float otherDistance = getDistanceFrom0(other);
			return thisDistance < otherDistance;
		}

		//Calculates distance from (0,0,0)
		static float getDistanceFrom0(const Vertex& v) {
			return sqrt(pow(v.x,2) + pow(v.y,2) + pow(v.z,2));
		}
};



//generates random foats and push to vector
void qsortp_debug::fillWithRandomFloat(vector<float> &arr, int count)
{
	//random generator
	for(auto i=count; i>0; i--) {
    	auto value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    	arr.push_back(value);
	}
	//inverse sequence 
	/*for(auto i=count; i>0; i--)
    	arr.push_back(i);*/
};

//generates random Vertex and push them to vector
void qsortp_debug::fillWithRandomVertex(vector<Vertex> &arr, int count)
{
	for(auto i=count; i>0; i--) {
    	auto x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		auto y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		auto z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		Vertex value(x,y,z);
    	arr.push_back(value);
	}
};


	




