#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_NUM_OF_COURSES 10
#define MAX_NUM_OF_EXERCISES 13
#define MAX_NUM_OF_UNITE 20
#define PASS_SCORE 60

struct CourseInfo
{
int courseNum;
int grade;
};
typedef struct CourseInfo COURSE_INFO;

// This function takes an int array and int item, goes through the array and if the item is found returns 1. else returns 0.
int itemInArray(int arr[], int size, int item)
{
    int index = 0;
    for(index; index < size; index++)
    {
        if(item == arr[index])
            return 1;
    }
    return 0;
}

// Insertion sort function is O(n^2) at worst case (Decreasing array so n shifts for n items).
void insertionSort(int arr[], int size)
{
    // Going through the array, for every item "inserts" it to the correct position via shifts.
    for(int j = 1; j < size; j++)
    {
        // key variable in case of a required shift so the value won't be lost.
        int key = arr[j];
        int i = j - 1;
        // The shifting operation if needed.
        while(i >= 0 && arr[i] > key)
        {
            arr[i+1] = arr[i];
            i--;
        }
        // Placing the key it's correct position.
        arr[i + 1] = key;
    }
}

// This function is based on insetion sort as described. Only here the function sorts COURSE_INFO types based on their courseNum value.
void sortCourses(COURSE_INFO data[], int size)
{
    for(int j = 1; j < size; j++)
    {
        COURSE_INFO key = data[j];
        int i = j - 1;
        while(i >= 0 && data[i].courseNum > key.courseNum)
        {
            data[i+1] = data[i];
            i--;
        }
        data[i + 1] = key;
    }
}

// This function takes sorted COURSE_INFO array and outputs their content in a specified format.
void printCourses(COURSE_INFO data[], int size)
{
    printf("Course# Grade\n");
    printf("======= =====\n");
    for(int i = 0; i < size; i++)
    {
        printf("%d\t%d\n", data[i].courseNum, data[i].grade);
    }
}

/* The function takes COURSE_INFO arrays, adding to interCourse array the intersection items of both arrays and return the size of it.
Because the loop does n comparison for n items, it is O(n^2).*/
int intersect(COURSE_INFO dataA[], int sizeA, COURSE_INFO dataB[], int sizeB, int interCourse[])
{
    // Indices: i - array1, j - array2, k - interCourse.
    int i, j, k = 0;
    // Running on array1.
    for(i = 0; i < sizeA; i++)
    {
        // Running on array2.
        for(j = 0; j < sizeB; j++)
        {
            // The condtition of intersection. Also checks if current item is already present in interCourse.
            if(dataA[i].courseNum == dataB[j].courseNum && itemInArray(interCourse, i, dataA[i].courseNum) == 0)
            {
                interCourse[k] = dataA[i].courseNum;
                k++;
            }
        }
    }
    // Size of interCourse.
    return k;
}

/* The function takes COURSE_INFO arrays, adding to uniteCourse array the items of either array and return the size of it.
Because the loop runs on n = max(size arrayA, size arrayB) seperatly 2 times, it is O(2n) => O(n).*/
int unite(COURSE_INFO dataA[], int sizeA, COURSE_INFO dataB[], int sizeB, int uniteCourse[])
{
    // Indices.
    int i = 0, j = 0 ;
    // Adds all items in arrayA to the uniteCourse.
    for(i; i < sizeA; i++)
    {
        uniteCourse[j] = dataA[i].courseNum;
        j++;
    }
    // Adds items in arrayB that only not already in uniteCourse.
    for(i = 0; i < sizeB; i++)
    {
        if(itemInArray(uniteCourse, j, dataB[i].courseNum) == 0)
        {
            uniteCourse[j] = dataB[i].courseNum;
            j++;
        }
    }
    // The size of uniteCourse.
    return j;
}

// The function recives an int array and prints it's content. Running over the whole array hence time complexity is O(n).
void printCNum(int data[], int size)
{
    for(int i = 0; i < size; i++)
        printf("%d ", data[i]);
}

// The function recives a COURSE_INFO array and returns the course with the lowest grade in the semester.
COURSE_INFO findMinGrade(COURSE_INFO data[], int size)
{
    int i = 0, j = 0;
    // A variable that stores the minimum grade. Initially set to the first item in the array.
    int minGrade = data[i].grade;
    // Runs over the array, if lower item was found the j index and minGrade are updated.
    for(i = 1; i < size; i++)
    {
        if(data[i].grade < minGrade)
        {
            minGrade = data[i].grade;
            j = i;
        }
    }
    // Return the lowest grade item.
    return data[j];
}

// The function goes through the grades array and returns the first grade couple that the first one is lower then PASS_SCORE and the second is greater.
int findFailPass(int grades[], int size)
{
    int i = 0;
    for(i; i + 1 < size; i++)
    {
        if(grades[i] < PASS_SCORE && grades[i + 1] >= PASS_SCORE)
            return i;
    }
}

/* The functions reoeders the grades array so all items less then the limit show beforehand. Returns the index of the last less then limit item.
As The function only goes over each array once, it does it 3 times so O(n) for time complexity.*/
int reorderGrades(int grades[], int size, int limit)
{
    // In case the limit given is 0, no grade can be lower then 0.
    if(limit == 0)
        return -1;
    // Initialize 2 array for items less/greater then the limit and set all items to 0. 
    int gradesLtLim[MAX_NUM_OF_EXERCISES];
    int gradesGtLim[MAX_NUM_OF_EXERCISES];
    // Indices: i,l - general running use, k,j - adding items to gradesGt/LtLim by continious sequence
    int i = 0, j = 0, k = 0, l = 0;
    for(i; i < MAX_NUM_OF_EXERCISES; i++)
        {
            gradesLtLim[i] = 0;
            gradesGtLim[i] = 0;
        }
    // The loop adds items to both new arrays accordig to greater/less then the limit.
    for(i = 0; i < size; i++)
    {
        if(grades[i] >= limit)
        {
            gradesGtLim[k] = grades[i];
            k++;
        }
        else
        {
            gradesLtLim[j] = grades[i];
            j++;
        }
    }
    // Changing the original grades values, first going over gradesLtLim, then gradesGtLim.
    for(i = 0; i < j; i++)
        grades[i] = gradesLtLim[i];
    for(i; i < k + j; i++, l++)
        grades[i] = gradesGtLim[l];
    // Returns the index of the last item less then the limit.
    return j;
}

int main()
{
    // A General messege.
    printf(" Welcome students!!\nand bye bye Pizzeria\n\n");
    int numOfCoursesA;
    int numOfCoursesB;
    int numOfExercises;
    COURSE_INFO semA_Arr[MAX_NUM_OF_COURSES];
    COURSE_INFO semB_Arr[MAX_NUM_OF_COURSES];
    int uniteCourses[MAX_NUM_OF_UNITE];
    int interCourses[MAX_NUM_OF_COURSES];
    int exercises[MAX_NUM_OF_EXERCISES];
    
    // For each emester asks the user to enter no. of courses, for each asks to enter course number and grade.
    printf("Please enter number of courses in semester A: \n");
    scanf("%d", &numOfCoursesA);
    for(int i = 0; i < numOfCoursesA; i++)
    {
        printf("Enter course number and grade: \n");
        scanf("%d%d", &semA_Arr[i].courseNum, &semA_Arr[i].grade);
    }
    printf("Please enter number of courses in semester B: \n");
    scanf("%d", &numOfCoursesB);
    for(int i = 0; i < numOfCoursesB; i++)
    {
        printf("Enter course number and grade: \n");
        scanf("%d%d", &semB_Arr[i].courseNum, &semB_Arr[i].grade);
    }

    // Sorting the courses by course number.
    sortCourses(semA_Arr, numOfCoursesA);
    sortCourses(semB_Arr, numOfCoursesB);

    // Printing the courses info.
    printf("\nSorted courses of semester A:\n");
    printCourses(semA_Arr, numOfCoursesA);
    printf("\nSorted courses of semester B:\n");
    printCourses(semB_Arr, numOfCoursesB);
    printf("\n");

    // Calling unite/inter functions to store accordingly. Recieves the size of each.
    int uniteNum = unite(semA_Arr ,numOfCoursesA, semB_Arr, numOfCoursesB, uniteCourses);
    int interNum = intersect(semA_Arr ,numOfCoursesA, semB_Arr, numOfCoursesB, interCourses);

    // As uniteCourses and interCourses are int arrays, they are sent to be orders via regular insertionSort.
    insertionSort(uniteCourses, uniteNum);
    insertionSort(interCourses, interNum);

    // Prints the uniteCourses and interCourses arrays.
    printf("courses taken in semester A or semester B: ");
    printCNum(uniteCourses, uniteNum);
    printf("\ncourses taken in semester A and semester B: ");
    printCNum(interCourses, interNum);
    printf("\n\n");

    // Calls findMinGrade and recieves the matching item. Then prints the contents.
    COURSE_INFO minGrade = findMinGrade(semA_Arr, numOfCoursesA);
    printf("Minimum grade in semester A is: %d in course #%d\n", minGrade.grade, minGrade.courseNum);

    // Asks the user for number of exercises then asks for grades.
    printf("How many exercises were given in course #%d? \n",minGrade.courseNum);
    scanf("%d", &numOfExercises);
    printf("Enter exercises grades: \n");
    for(int i = 0; i < numOfExercises; i++)
        scanf("%d", &exercises[i]);
    // Sets the first grade to 30, and the last to 100.
    exercises[0] = 30;
    exercises[numOfExercises - 1] = 100;
    // Prints the grades.
    printf("Exercise grades: ");
    printCNum(exercises, numOfExercises);

    // Prints the Fail-Pass index.
    printf("\nIndex of Fail-Pass is: %d\n", findFailPass(exercises, numOfExercises));

    // Asks the user for limit grade, calls reorder grades and recives matching index, prints the subset that is all less then the limit.
    printf("Please enter a limit grade: \n");
    int limit, gradesAfterLimit;
    scanf("%d", &limit);
    gradesAfterLimit = reorderGrades(exercises, numOfExercises, limit);
    printf("After reordering grades, the grades smaller than %d are: ", limit);
    printCNum(exercises, gradesAfterLimit);
}