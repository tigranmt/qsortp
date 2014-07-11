#include <iostream> 
#include <fstream>
#include <vector>
#include <random>
#include "qsortp.h"
#include "debug.h"
using namespace std;
using namespace qsortp_debug;




//Sequential sort 
void SequentialQuickSort(int elementsCount)
{
	vector<Vertex> a;
	cout << "Start Sequential Sort " << endl;
	cout<<"Generate vector for "<< elementsCount << " elements"<<endl;
	fillWithRandomVertex(a, elementsCount); //generates vector 

	cout << "Array elements count is: " << a.size() << endl; 
	cout << "Array is sorted: " << isSorted(a) <<endl;
	cout<<"------------------------" <<endl; 


	auto start = omp_get_wtime();

	//STL version of sequential sort
	sort(a.begin(), a.end());

	auto end   = omp_get_wtime();		
	
	cout<<"Done Sequential in: " << (end-start) << " sec"<< endl;

	cout << "Array elements count is: " << a.size() << endl; 
	cout << "Array is sorted: " << isSorted(a) <<endl;

	cout << "Done Sequential Sort " << endl;
	cout << "------------------" <<endl << endl;
}


//Parallel quick sort
void ParallelQuickSort(int elementsCount)
{
	try {
		
		vector<Vertex> a;
		cout << "Start Parallel  Sort " << endl;
		cout<<"Generate vector for "<< elementsCount << " elements"<<endl;
		fillWithRandomVertex(a, elementsCount); //generate random values
	

		cout<<"Done" <<endl; 
		cout << "Array elements count is: " << a.size() << endl; 
		cout << "Array is sorted: " << isSorted(a) <<endl;
		cout<<"------------------------" <<endl; 

		qsortp<Vertex> qs;
		
		auto start = omp_get_wtime();		
		qs.SortP(a, 0, a.size()-1);  //parallel quick sort implementation 
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

	const int count = 6000000;	
	SequentialQuickSort(count);
	ParallelQuickSort(count);
 
    getchar(); 
    
	return 0;
}