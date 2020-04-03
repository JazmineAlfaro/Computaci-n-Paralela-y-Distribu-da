#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

int** initialize_matrix(int len, int max){
	int** mat = new int*[len];
	mat[0] = new int[len * len];
	srand( (unsigned)time(NULL) );
	
	for(int i=1;i<len;++i)
		mat[i] = mat[i-1] + len;
	
	for(int i=0;i<len;++i)
		for(int j=0;j<len;++j)
			mat[i][j] = rand() % max + 1;
			
	return mat;
}

int* initialize_array(int len, int max){
	int* arr = new int[len];
	srand( (unsigned)time(NULL) );
	
	for(int i=0;i<len;++i)
		arr[i] = rand() % max + 1;
	
	return arr;
}

int* initialize_array(int len){
	int* arr = new int[len];
	srand( (unsigned)time(NULL) );
	
	for(int i=0;i<len;++i)
		arr[i] = 0;
		
	return arr;
}

void func1(int** mat, int* arr1, int* arr2, int len){
	for (int i = 0; i < len ; ++i)
		for (int j = 0; j < len ; ++j)
			arr2[i] += mat[i][j] * arr1[j];
}

void func2(int** mat, int* arr1, int* arr2, int len){
	for (int j = 0; j < len ; ++j)
		for (int i = 0; i < len ; ++i)
			arr2[i] += mat[i][j] * arr1[j];
}


int main(int argc, char *argv[]) {
	int len = 5000;
	int max = 100;
	int** mat = initialize_matrix(len, max);
	int* arr1 = initialize_array(len,max);
	int* arr2 = initialize_array(len);
	
	cout<<"N: "<<len<<endl;
	
	std::clock_t c1, c2;
	double d1 ,d2;
	
	c1 = std::clock();
	func1(mat, arr1,arr2,len);
	d1 = ( std::clock() - c1 ) / (double) CLOCKS_PER_SEC;
	cout<<"Función 1: "<< d1 <<'\n';
	
	c2 = std::clock();
	func2(mat, arr1,arr2,len);
	d2 = ( std::clock() - c2 ) / (double) CLOCKS_PER_SEC;
	cout<<"Función 2: "<< d2 <<'\n';
	
	
	/*
	//Print Matrix
	for (int i = 0; i < len ; ++i){
		for (int j = 0; j < len ; ++j)
			cout<<mat[i][j]<<" ";
		cout<<endl;
	}
	//Print Arrays
	for (int i = 0; i < len ; ++i){
	cout<<arr1[i]<<" ";
	//cout<<arr2[i]<<" ";
	}
	*/
	
	return 0;
}

