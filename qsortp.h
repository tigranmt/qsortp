#pragma once 
#include <vector> 
#include <algorithm> 
#include <memory>
#include <tuple>
#include <stack>

/*****************************************************************************************************************************
	Implementation of QuickSort (http://it.wikipedia.org/wiki/Quicksort) on multiple cores using OpenMP (http://openmp.org/wp/)
	2014, Guly
*******************************************************************************************************************************/
#include <cmath>
#include "omp.h"

using namespace std;

//tuple for handling range of indices to process in single parallel thread
typedef tuple<int, int> IntTuple;



template<class T>
class qsortp
{

	private:		

		//merges 2 SORTED sequences into single one (participates in  parallel execution)
		void mergeSerial(vector<T> &arr, int start, int middle, int end)
		{
			int s=start, e=middle, t=0;
		
			int size = end-start + 1;
			unique_ptr<T[]> temp(new T[size]);
			bool inserted = false;

			while(s<middle && e<end) 
			{
				if(arr[s]<arr[e]) 
				{
					temp[t++] = arr[s];
					s+=1;
					inserted = true;
				}
				else
				{
					temp[t++] = arr[e];
					e+=1;
					inserted = true;
				}			
			}

			while(s < middle) { //fill remaining elements, if any
				temp[t++] = arr[s];
				s+=1;
			}           

			while(e < end){     //fill remaining elements, if any				
				temp[t++] = arr[e];
				e+=1;
			}

			if(inserted) 
			{
				t=0;
				
				//now fill original vector
				for(auto i=start; i<end; i++)
				{
					arr[i] = temp[t++]; //temp element count == end-start
				}
			}			

		}

		//merges multiple SORTED sequences in single one on multicores (participates in parallel execution)
		void reduceResultP(vector<T> &arr, IntTuple *indexRanges, int count)
		{
			/*indexRanges in always multiple of 2 (cores count=> threads count)*/			
			
			cout<< "Start reducer: "<< endl;

			int countOriginal = count; 
			while(count>1) //evaluate if there is still something to merge and reduce
			{		
			

				int reducedCount =count/2; 			
				unique_ptr<int[]> newRanges(new int[count]);				
				
				#pragma omp parallel for num_threads(reducedCount)
					for(int i=0; i<=reducedCount; i+=2)
					{				
						auto tuple = indexRanges[i];				

						auto start = get<0>(tuple);
						auto middle = get<1>(tuple);

						//invalid value in the tuple, so skip this element
						if(start <0 || middle <0) continue;
					
						auto next_tuple = indexRanges[i+1];
						auto end = get<1>(next_tuple);											
						
						mergeSerial(arr, start, middle, end);	//merge couple	of ranges

					    newRanges[i] = start;    //save reduce points 
						newRanges[i + 1] = end;  //save reduce points 
					}

				
				if(count > 1) 
				{					
    
					count = count/2; //reduce count by half

					int iRange = 0;
					for(auto i=0; i<=count; i+=2)
					{
						auto start = newRanges[i]; 
						auto end   = newRanges[i+1];

						IntTuple t = make_tuple(start, end); 
						indexRanges[iRange++] =  t;
					}

					//populate the rest of array with invalid values, which will be tracked in the {for} above (so avoid ridemensioning array)
					for(auto j=count; j<countOriginal; j++) 
					{
						IntTuple temp(-1,-1);  //generate invalid value 
						indexRanges[j] = temp;  //set invalid value into the no more used index
					}

				}
			}			

		}


		//partition sequence (participates in quick sort)
		int partition(vector<T> &arr, int start, int end)
		{
			if(start < end)
			{

				auto pivotIndex = (start + end)/2; 
				auto pivotValue = arr[pivotIndex];
				//auto pivotValue = arr[end];
				while(start < end) 
				{

					if(arr[start] < pivotValue)
						start++;

					if(arr[end] > pivotValue)
						end--;

					if(start < end) 
					{
						//swap 
						auto temp = arr[start]; 
						arr[start] = arr[end];
						arr[end] = temp;
						start++; 
						end--;
					}

				}
			}

			return end;
		}


	public: 

		void qsort()
		{
		}
	
		void Sort(vector<T> &arr, int start, int end)
		{			
			if(arr.size() <= 1) return;
				
			// check(arr);

			 if(start < end) 
			 {
		     	int part = partition(arr, start, end); 
		     	Sort(arr, start, part); 
		     	Sort(arr, part+1, end); 
		     }
		}
		

		void SortP(vector<T> &arr, int start, int end)
		{
			if(arr.size() <= 1) return;

			//check(arr);

			int threadCount=1;
			int arrSize = arr.size();			
			int step = 0;

			//get available threads count and calculate step based on that value
			#pragma omp parallel  
			{
				#pragma omp master 
				{
					threadCount = omp_get_num_threads();
					step = arrSize/threadCount;
				}

				#pragma omp flush(step, threadCount)
			}
			

			//define sequence of tuples which holds the chunk range indices


			unique_ptr<IntTuple[]> indexRanges(new IntTuple[threadCount]);
			
			
			#pragma omp parallel for shared(indexRanges, arr, arrSize)
				for(int i=0; i<threadCount; i++) 
				{
					int start = i*step; //get start
					int end = start + step;	//get end			
					 // find reminder, if ANY relevant


					int threadid = omp_get_thread_num();

					//if this is a last thread add reminded elements to its calculation
					if(threadid == (threadCount-1)) {
						int reminder = arrSize - end;
						end += reminder;
					}

					IntTuple t = make_tuple(start, end);	
					indexRanges[i] = t; 

					//cout<< "threadid: " << omp_get_thread_num() << " start: " << start << " end:" << end <<  endl;

					//execute STL version (NON QUICK SORT)
					sort(arr.begin() + start, arr.begin() + end);					

					//quick sort only on the given range of array (custom implementation)
					//Sort(arr, start,  end);
				}
				
			/****Reduce multiple sorted chunks into single array***/
			reduceResultP(arr, &indexRanges[0], threadCount);	

		}

};