# PCP
To compile and run :

g++ main.cpp -o pcp
./pcp

Input filename MUST be input.txt

Format of input code:
Line 1: Maximum size of queue. It should be between 1000 and 5000.
Line 2: Maximum total number of states. It should be between 1000 and 5000. 
Line 3: A flag indicating the type of output.
'0' will output all the states generated, while '1' will only output the answer sequence of dominos (if found).
Remaining lines: Dominos: Number, top, bottom.

Example 1:
3000
5000
0
1 c cca
2 ac ba
3 bb b
4 ac cb

Example 2:
2000
4000
1
1 aa aaa
2 aabb ab
3 aab baaba
4 aabaa aba
5 aba baa
6 ba baba

Example 3:
3000
3000
1
1 ab a
2 a bac
3 cab a
