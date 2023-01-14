#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10
#define MAX_INT_SIZE 10
#define FUNC_COUNT 9
#define EXIT 0

// Add your recursive functions declarations here
bool isEven(int num, int dig);
bool isEvenHelper(int num, int dig, int count);
int howManyPaths(int x, int y);
int biggestLowPower(int x, int num);
int partSum(int num);
void intToStr(int num, char s[]);
int intToStrHelper(int num, char s[], int index);
void fillMaxPrefixesArray (int numbers[], int n, int maxPrefixesArray[]);
int fillMaxPrefixesArrayHelper(int numbers[], int n, int currMax);
void getMinToStart (int numbers[], int n);
int getMinToStartHelper(int numbers[], int n, int currMin);
void combineArrays (int sortedArr1[], int size1, int sortedArr2[], int size2);
int combineArraysHelper(int sortedArr1[], int size1, int sortedArr2[], int size2);
int countSmaller(int arr[], int start, int end, int num);
int countSmallerHelper(int arr[], int start, int end, int num, int sum);


// Testing functions
int readArray(int data[], int maxSize);
void printArray(int data[], int size);
void bubbleSort(int arr[], int size);
void swap(int arr[], int i, int j);
void checkQ1();
void checkQ2();
void checkQ3();
void checkQ4();
void checkQ5();
void checkQ6();
void checkQ7();
void checkQ8();
void checkQ9();

/*********** main - don't make any changes here !!! ***************************/
void main()
{
	int funcNum;
	bool exit = false;

	while (!exit)
	{
		printf("Enter the number of function you want to check (1-%d) or %d to exit the program: ", FUNC_COUNT, EXIT);
		scanf("%d", &funcNum);

		switch (funcNum)
		{
		case 1:
			checkQ1();
			break;
		case 2:
			checkQ2();
			break;
		case 3:
			checkQ3();
			break;
		case 4:
			checkQ4();
			break;
		case 5:
			checkQ5();
			break;
		case 6:
			checkQ6();
			break;
		case 7:
			checkQ7();
			break;
		case 8:
			checkQ8();
			break;
		case 9:
			checkQ9();
			break;
		case EXIT:
			exit = true;
			break;
		default:
			printf("Invalid choice.\n");
		}
		printf("\n");
	}

}

/***************** Testing functions - don't make any changes here!!! ***************/
void checkQ1()
{
	int num, dig;

	printf("Enter a positive integer: ");
	scanf("%d", &num);
	printf("Enter a digit: ");
	scanf("%d", &dig);
	if (isEven(num, dig))
	{
		printf("%d appears even number of times in %d\n", dig, num);
	}
	else
	{
		printf("%d appears odd number of times in %d\n", dig, num);
	}
}

void checkQ2()
{
	int x, y;

	printf("Enter two non-negative integers: ");
	scanf("%d%d", &x, &y);
	printf("There are %d paths from (0,0) to (%d,%d)\n", howManyPaths(x, y), x, y);
}

void checkQ3()
{
	int x, num;

	printf("Enter two positive integers: ");
	scanf("%d%d", &x, &num);
	printf("The biggest power of %d which is smaller than %d is %d\n", x, num, biggestLowPower(x, num));
}

void checkQ4()
{
	int num;

	printf("Enter a positive integer: ");
	scanf("%d", &num);
	printf("The partial sum of %d digits is %d\n", num, partSum(num));
}

void checkQ5()
{
	int num;
	char string[MAX_INT_SIZE + 1];

	printf("Enter a positive integer: ");
	scanf("%d", &num);
	intToStr(num, string);
	printf("The string representing the integer %d is %s\n", num, string);
}

void checkQ6()
{
	int numbers[SIZE];
	int maxPrefixes[SIZE];
	int size;

	size = readArray(numbers, SIZE);
	fillMaxPrefixesArray(numbers, size, maxPrefixes);
	printf("Max prefixes array: ");
	printArray(maxPrefixes, size);
}

void checkQ7()
{
	int numbers[SIZE];
	int size;

	size = readArray(numbers, SIZE);
	getMinToStart(numbers, size);
	printf("The minimal number is: %d\n", numbers[0]);

	// check if all other numbers are still inb array
	bubbleSort(numbers, size);
	printf("The sorted array: ");
	printArray(numbers, size);
}

void checkQ8()
{
	int arr1[SIZE], arr2[2 * SIZE];
	int size1, size2;

	size1 = readArray(arr1, SIZE);
	size2 = readArray(arr2, 2 * SIZE - size1);

	// sort arrays
	bubbleSort(arr1, size1);
	bubbleSort(arr2, size2);

	combineArrays(arr1, size1, arr2, size2);
	printf("The combined sorted array: ");
	printArray(arr2, size1 + size2);
}

void checkQ9()
{
	int numbers[SIZE];
	int size, num;

	// read numbers from user (assumption: numbers are different from each other)
	size = readArray(numbers, SIZE);
	bubbleSort(numbers, size);

	printf("Please enter an integer: ");
	scanf("%d", &num);

	printf("There are %d numbers in array that are smaller than %d\n", countSmaller(numbers, 0, size - 1, num), num);
}

// This function reads a series of integers from user into data array. 
// The function will first ask the user to enter the number of integers he wishes
// to enter to array. If number is bigger than maxSize, then only the first masSize
// numbers will be read.
// The fucntion returns the arrays logical size (number of elements inserted into array).
int readArray(int data[], int maxSize)
{
	int count;
	int i;	// number of elements inserted into array

	printf("How many numbers would you like to enter to array ? (no more than %d) ", maxSize);
	scanf("%d", &count);
	if (count > maxSize)
	{
		count = maxSize;
	}
	printf("Please enter %d integers: ", count);

	for (i = 0; i < count; i++)
	{
		scanf("%d", &data[i]);	// read current input number		
	}

	return count;
}

// This function prints the first size elements of data array (integers).
void printArray(int data[], int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");
}

// This functions sorts arr in increasing order using bubble sort algorithm
void bubbleSort(int arr[], int size)
{
	int i, j;

	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(arr, j, j + 1);
}

void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

/******************************* Recursive functions **************************/
// Add recursive functions implementation here
bool isEven(int num, int dig)
{
	int counter = 0;
	bool answer = isEvenHelper(num, dig, counter);
}

bool isEvenHelper(int num, int dig, int count)
{
	if(num == 0 && count % 2 == 0)
		return true;
	else if(num != 0 && num % 10 == dig)
		return isEvenHelper(num / 10, dig, count+=1);
	else if(num != 0 && num % 10 != dig)
		return isEvenHelper(num / 10, dig, count);
	else
		return false;
}

int howManyPaths(int x, int y)
{
	if(x == 0 || y == 0)
		return 1;
	
	return howManyPaths(x, y - 1) + howManyPaths(x - 1, y);
}


int biggestLowPower(int x, int num)
{
	if((num / x) < 1)
		return 1;
	else
		return x * biggestLowPower(x, num / x);
}


int partSum(int num)
{
	if((num / 10) == 0)
		return 0;
	num /= 10;
	return num % 10 + partSum(num);
}

void intToStr(int num, char s[])
{
	s[0] = '0';
	s[1] = '\0';
	intToStrHelper(num, s , 0);
}

int intToStrHelper(int num, char s[], int index)
{
	if(num == 0)
	{
		return 0;
	}
	index = intToStrHelper(num / 10, s, index);
	s[index] = (num % 10) + '0';
	index+= 1;
	s[index] = '\0';
	return index;
}

void fillMaxPrefixesArray(int numbers[], int n, int maxPrefixesArray[])
{	
	if(n == 1)
	{
		maxPrefixesArray[n-1] = numbers[n-1]; 
		return;
	}
	fillMaxPrefixesArray(numbers, n-1, maxPrefixesArray);
	maxPrefixesArray[n-1] = fillMaxPrefixesArrayHelper(numbers, n, 0);
	return;
}

int fillMaxPrefixesArrayHelper(int numbers[], int n, int currMax)
{
	if(n == 1)
	{ 
		currMax = numbers[n-1];
		return currMax;
	}
	currMax = fillMaxPrefixesArrayHelper(numbers, n-1, currMax);
	if(numbers[n-1] > currMax)
		currMax = numbers[n-1];
	return currMax;
}

void getMinToStart(int numbers[], int n)
{
	getMinToStartHelper(numbers, n, 0);
}

int getMinToStartHelper(int numbers[], int n, int currMin)
{
	if(n == 1)
		return numbers[n-1];
	currMin = getMinToStartHelper(numbers, n-1, currMin);
	if(currMin > numbers[n-1])
	{
		int temp = numbers[0];
		numbers[0] = numbers[n-1];
		numbers[n-1] = temp;
		currMin = numbers[0];
	}
	return currMin;
}

void combineArrays(int sortedArr1[], int size1, int sortedArr2[], int size2)
{
	combineArraysHelper(sortedArr1, size1, sortedArr2, size2);
	bubbleSort(sortedArr2, size2 + size1);
}

int combineArraysHelper(int sortedArr1[], int size1, int sortedArr2[], int size2)
{
	if(size1 == 0)
		return size2;
	size2 = combineArraysHelper(sortedArr1, size1 - 1, sortedArr2, size2);
	sortedArr2[size2] = sortedArr1[size1 - 1];
	size2 += 1;
	return size2;
}

int countSmaller(int arr[], int start, int end, int num)
{
	return countSmallerHelper(arr, start, end, num, 0);
}

int countSmallerHelper(int arr[], int start, int end, int num, int sum)
{
	if(start == end + 1)
		return 0;
	sum = countSmallerHelper(arr, start + 1, end, num, sum);
	if(arr[start] < num)
		sum+=1;
	return sum;
}