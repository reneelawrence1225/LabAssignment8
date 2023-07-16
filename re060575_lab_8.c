#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapify(int arr[], int n, int i)
{
	int biggest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if(left < n && arr[left] > arr[biggest]){
		biggest = left;
	}

	if(right < n && arr[right] > arr[biggest]){
		biggest = right;
	}

	if(biggest != i){
		int t = arr[i];
		arr[i] = arr[biggest];
		arr[biggest] = t;

		heapify(arr, n, biggest);
	}
}

void heapSort(int arr[], int n)
{	
	//change array
	for(int i = n / 2 - 1; i >= 0; i--){
		heapify(arr, n, i);
	}

	for(int i = n - 1; i > 0; i--){
		//move root to end
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		//then heapify this
		heapify(arr, i, 0);
	}
}
//end of heap sort


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int arr[], int l, int m, int r)
{
	int i, j , k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	for(i = 0; i < n1; i++){
		L[i] = arr[l + i];
	}

	for(j = 0; j < n2; j++){
		R[j] = arr[m + 1 + j];
	}

	i = 0;
	j = 0;
	k = l;

	while(i < n1 && j < n2){
		if(L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while(i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}


}

void mergeSort(int pData[], int l, int r)
{
	if(l < r){
		// get the mid point
		int m = (l+r)/2;
		// Sort first and second halves
		mergeSort(pData, l, m);
		mergeSort(pData, m+1, r);
		// printf("Testing l=%d r=%d m=%d\n", l, r, m);
		merge(pData, l, m, r);

	}
}
//end of merge sort

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");

	//used to be 100
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}