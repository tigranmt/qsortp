qsortp
======

Quick Sort parallel implementaiton with OpenMP


Parallel implementation of Quick Sort is failry simple and streightforward. 
The basic idea is: 

1) Devide given unsorted array in unsorted chuncks in that way that for every chunk there is one corresponding core on the machine. 

Example: if you have an array of 1000 elements and run your program on quad core processor, that array
will be devided in 4 chunks(sub arrays) with 250 elements each.  

Naturally in cases when the quantity of elements is not devidable on quantity of cores without reminder, all but last threads are loaded with the same amount of elements to sort, the last one, instead, takes care of its amount + reminder. 
Example: we have 13 elements to sort on 4 cores, that means that 3 core will get 3 element, where 4th core will get 
3 + reminder(1) = 4 elements to sort.

2) Every chunk(sub array) is sorted using original quick sort algoritm implementation, or std:sort. 

3) Every, at this point, sorted couple of subarrays is merged/reduced into single soted array till everything is merged/reduced into the one, single array. 



With Intel Core i5 2.90Ghz, 4 cores, 8GM RAM, Windows7 64bit, sorting unsorted, random list of 6.000.000 Vertex structures

- With sequential quick sort it takes: 6.40 sec 
- With parallel   quick sort it takes: 2.10 sec 


almost 3x times faster.


