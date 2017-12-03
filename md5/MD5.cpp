#include<iostream>
#include<string>
#include"MD5.h"

using namespace std;

int main()
{
	string input;
	while (getline(cin, input))
	{
		unsigned long int A = 0x67452301;
		unsigned long int B = 0xEFCDAB89;
		unsigned long int C = 0x98BADCFE;
		unsigned long int D = 0x10325476;
		int num = input.size();
		int N = num / 64;
		int R = num % 64;
		if (R == 56)
			N += 2;
		else
			N += 1;
		char * str = initial(input, N);
		MD5(A, B, C, D, N, str);
		//A=A+B+C+D;
		//cout<<hex<<"  "<<A<<hex<<"  "<<B<<hex<<"  "<<C<<hex<<"  "<<D<<endl;
		printf("%08x %08x %08x %08x\n", A, B, C, D);
	}
	//cout<<A;
	return 0;
}