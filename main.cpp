#include <iostream> 
#include <fstream>
#include <vector>
#include <random>
#include "qsortp.h"
#include "file.h"
using namespace std;
using namespace qsortp_debug;

struct Vertex 
{
	private:
		float x,y,z;
	public:
		
		Vertex() {}
		Vertex(float a, float b, float c):x(a),y(b),z(c){}

		bool operator > (const Vertex& other){
			float thisDistance = getDistanceFrom0(*this);
			float otherDistance = getDistanceFrom0(other);
			return thisDistance > otherDistance;
		}

		bool operator < (const Vertex& other){			
			float thisDistance = getDistanceFrom0(*this);
			float otherDistance = getDistanceFrom0(other);
			return thisDistance < otherDistance;
		}

		static float getDistanceFrom0(const Vertex& v) {
			return sqrt(pow(v.x,2) + pow(v.y,2) + pow(v.z,2));
		}
};

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
}

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
}


void fillWithRandomFloat(vector<float> &arr, int count)
{
	//random generator
	for(auto i=count; i>0; i--) {
    	auto value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    	arr.push_back(value);
	}
	//inverse sequence 
	/*for(auto i=count; i>0; i--)
    	arr.push_back(i);*/
}

void fillWithRandomVertex(vector<Vertex> &arr, int count)
{
	for(auto i=count; i>0; i--) {
    	auto x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		auto y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		auto z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		Vertex value(x,y,z);
    	arr.push_back(value);
	}
}

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
}


void SequentialQuickSort(int elementsCount)
{
	vector<Vertex> a;
	cout << "Start Sequential Sort " << endl;
	cout<<"Generate vector for "<< elementsCount << " elements"<<endl;
	fillWithRandomVertex(a, elementsCount);

	cout << "Array elements count is: " << a.size() << endl; 
	cout << "Array is sorted: " << isSorted(a) <<endl;
	cout<<"------------------------" <<endl; 


	auto start = omp_get_wtime();

	//STL version 
	sort(a.begin(), a.end());

	auto end   = omp_get_wtime();		
	
	cout<<"Done Sequential in: " << (end-start) << " sec"<< endl;

	cout << "Array elements count is: " << a.size() << endl; 
	cout << "Array is sorted: " << isSorted(a) <<endl;

	cout << "Done Sequential Sort " << endl;
	cout << "------------------" <<endl << endl;
}



void ParallelQuickSort(int elementsCount)
{
	try {
		
		vector<Vertex> a;
		cout << "Start Parallel  Sort " << endl;
		cout<<"Generate vector for "<< elementsCount << " elements"<<endl;
		fillWithRandomVertex(a, elementsCount);
	

		cout<<"Done" <<endl; 
		cout << "Array elements count is: " << a.size() << endl; 
		cout << "Array is sorted: " << isSorted(a) <<endl;
		cout<<"------------------------" <<endl; 

		qsortp<Vertex> qs;
		
		auto start = omp_get_wtime();		
		qs.SortP(a, 0, a.size()-1); 
		auto end   = omp_get_wtime();
		
		//printvector(a);
		auto diff = end-start;
		cout<<"Done Parallel in: " << (end-start)<< " sec"<< endl;

		cout << "Array elements count is: " << a.size() << endl; 
		cout << "Array is sorted: " << isSorted(a) <<endl;

		cout << "Done Parallel Sort" << endl;
		cout << "------------------" <<endl << endl;
	}
	catch(std::exception ex) {
		cout << "Exception: " << ex.what() << endl;
		getchar();
		
	}
}

int main() 
{

	const int count = 10000000;	
	SequentialQuickSort(count);
	ParallelQuickSort(count);
 
    getchar(); 
    
	return 0;
}