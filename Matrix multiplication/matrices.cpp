#include <iostream>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void initialize(vector<vector<int>>& A, int len, int max = 0){
	A.resize(len);
	for(int i=0;i<len;++i){
		A[i].resize(len);
	}
	
	for(int i=0;i<len;++i)
		for(int j=0;j<len;++j)
		A[i][j] = rand() % max + 1;
		
}

vector<vector<int>> multimat_naive(vector<vector<int>> A, vector<vector<int>> B, int len)
{
	vector<vector<int>> C;
	C.resize(len);
	for(int i=0;i<len;++i){
		C[i].resize(len);
	}
	std::clock_t c1;
	double d1 ;
	
	c1 = std::clock();
	
	for (int i = 0; i < len;++i ){
		for (int j = 0; j < len;++j ){
			for (int k = 0; k < len;++k){
				C[i][j] += A[i][k] * B[k][j];
				
			}
		}
	}
	
	d1 = ( std::clock() - c1 ) / (double) CLOCKS_PER_SEC;
	cout<<"Matrix size (naive): "<< len <<'\n';
	cout<<"Time (naive): "<< d1 <<'\n';
	
	std::ofstream out;
	out.open("matrix.txt", std::ios::app);
	out<<"Matrix size (naive):  "<< len <<'\n';
	out<<"Time (naive): "<< d1 <<'\n';
	out<<'\n';
	out.close();
	
	
	return C;
}

	
vector<vector<int>> multimat_block(vector<vector<int>> A, vector<vector<int>> B, int len){
	vector<vector<int>> C;
	C.resize(len);
	for(int i=0;i<len;++i){
		C[i].resize(len);
	}
	
	std::clock_t c1;
	double d1 ;
	
	c1 = std::clock();
	
	int block_size = 128;
	
	for (int k = 0; k < len; k += block_size)
		for (int j = 0; j < len; j += block_size)
			for (int i = 0; i < len; i += block_size)
				for (int ii = i; ii < min(i + block_size, len); ++ii)
					for (int jj = j; jj < min(j + block_size, len); ++jj)
						for (int kk = k; kk < min(k + block_size, len); ++kk)
							C[ii][jj] += A[ii][kk] * B[kk][jj];

	d1 = ( std::clock() - c1 ) / (double) CLOCKS_PER_SEC;
	
	std::ofstream out;
	out.open("matrix.txt", std::ios::app);
	out<<"Matrix size(block): "<< len <<'\n';
	out<<"Time(block): "<< d1 <<'\n';
	out<<'\n';
	out.close();

	cout<<"Matrix size(block): "<< len <<'\n';
	cout<<"Time(block): "<< d1 <<'\n';
	
	return C;
}
		
		
int main(int argc, char *argv[]) {
	
	int len = 1000;
	
	vector<vector<int>> A;
	vector<vector<int>> B;
	vector<vector<int>> C;
	initialize(A,len,1);
	initialize(B,len,1);
	
	C = multimat_naive(A, B, len);
	cout<<endl;

	C.clear();
	
	C = multimat_block(A, B, len);
	cout<<endl;
	
	A.clear();
	B.clear();
	C.clear();
	return 0;
}
