qsortp
======

Quick Sort parallel implementaiton with OpenMP


Parallel implementation of Quick Sort is failry simple and streightforward. 
The basic idea is: 

1) Devide given unsorted array in unsorted chuncks in that way that for every chunk there is one corresponding core on the machine. 
Example: if you have an array of 1000 elements and run your program on quad core processor, that array
will be devided in 4 chunks(sub arrays) with 250 elements each. 

2) Every chunk(sub array) is sorted using original quick sort algoritm implementation, or std:sort. 

3) Every, at this point, sorted couple of subarrays is merged/reduced into single soted array till everything is merged/reduced into the one, single array. 



On the Intel Core i5 2.90Ghz, 4 cores, 8GM RAM with Windows7 64bit, sorting unsorted, random list of 6.000.000 Vertex structures

- With sequential quick sort takes: 6.40 sec 
- With parallel   quick sort takes: 2.10 sec 


almost 300% faster.


