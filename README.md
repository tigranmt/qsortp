qsortp
======

Quick Sort parallel implementaiton with OpenMP


Parallel implementation of Quick Sort is failry simple and streightforward. 
The basic idea is: 

1) Devide given unsorted array un unsorted chuncks in that way that for every chunck there is one core on the machine. 
   Puting even more simple: if you have an array of 1000 elements and run your program on quad core processor, that array
   will be devide in 4 sub arrays with 250 elements each. 

2) Every chuck (subarray) is sorted using original quick sort algoritm implementation, or std:sort. 

3) Every, at this point, sorted couple of subarrays is merged in single soted array. 
