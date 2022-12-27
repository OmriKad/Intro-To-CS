#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_NAME_LEN 21
#define MAX_FULL_NAME_LEN 28
#define MAX_COURSES 10
#define GROUP_STUDENT_NUMBER 6
#define GROUP_NUMBER 3

typedef struct CourseInfo
{
int courseNum;
int grade;
} COURSE_INFO;

struct Student
{
char name[MAX_NAME_LEN];
int identity;
int nofCourses; //number of courses taken in semesterA
COURSE_INFO course_info[MAX_COURSES];
};
typedef struct Student STUDENT;

int getStudentNames(STUDENT stuData[][GROUP_STUDENT_NUMBER], int rows, int cols, int courseNum, char stuNames[][MAX_FULL_NAME_LEN])
{
    printf("Names of students in course#%d:\n", courseNum);
    int numOfStudents = 0;
    for(int group = 0; group < rows; group++)
    {
        for(int student = 0; student < cols; student++)
        {
            for(int course = 0; course < stuData[group][student].nofCourses; course++)
            {
                if(stuData[group][student].course_info[course].courseNum == courseNum)
                {
                    char tempStr[MAX_FULL_NAME_LEN] = {'\0'};
                    switch (group)
                    {
                    case 0:
                        strcat(tempStr, "GroupA ");
                        break;
                    case 1:
                        strcat(tempStr, "GroupB ");
                        break;
                    case 2:
                        strcat(tempStr, "GroupC ");
                        break;
                    }
                    strcat(tempStr, stuData[group][student].name);
                    strcpy(stuNames[numOfStudents], tempStr);
                    printf("%s\n", tempStr);
                    numOfStudents++;
                    break;
                }
            }
        }
    }
    return numOfStudents;
}

void lois2Lane(char stuNames[][MAX_FULL_NAME_LEN], int student, int index)
{
    stuNames[student][index + 1] = 'a'; 
    stuNames[student][index + 2] = 'n';
    stuNames[student][index + 3] = 'e';
}

int hasLois(char arr[])
{
    int index = 0;
    for(index; index < strlen(arr); index++)
    {
        if(arr[index] == 'L')
        {
            if(arr[index + 1] == 'o')
            {
                if(arr[index + 2] == 'i')
                {
                    if(arr[index + 3] == 's')
                            return index;
                        
                }
            }
        }
    }
    return -1;
}

int hasLex(char arr[])
{
    int index = 0;
    for(index; index < strlen(arr); index++)
    {
        if(arr[index] == 'L')
        {
            if(arr[index + 1] == 'e')
            {
                if(arr[index + 2] == 'x')
                    return 1;
            }
        }
    }
    return 0;
}

int getMax(int arr[], int lim)
{
    int index = 1;
    int maxIndex = 0;
    int max = 0;
    for(index; index < lim; index++)
        {
            if(arr[index] > max)
            {
                max = arr[index];
                maxIndex = index;
            }
        }
    arr[maxIndex] = 0;
    return max;
}       

int main()
{
    printf("********************\n* Welcome Students *\n********************\n");
    STUDENT groups[GROUP_NUMBER][GROUP_STUDENT_NUMBER];
    for(int group = 0; group < GROUP_NUMBER; group++)
    {
        char groupName[8];
        switch(group)
        {
            case 0:
                strcpy(groupName, "GROUP A");
                break;
            case 1:
                strcpy(groupName, "GROUP B");
                break;
            case 2:
                strcpy(groupName, "GROUP C");
                break;
        }
        printf("Enter students data for %s:\n", groupName);
        printf("___________________________\n");
        for(int student = 0; student < GROUP_STUDENT_NUMBER; student++)
        {
            char firstName[MAX_FULL_NAME_LEN];
            char lastName[MAX_FULL_NAME_LEN];
            char fullName[MAX_FULL_NAME_LEN];
            printf("Enter student first name and last name (seperated by spaces): ");
            scanf("%s", firstName);
            strcpy(fullName, firstName);
            strcat(fullName, " ");
            scanf("%s", lastName);
            strcat(fullName, lastName);
            strcpy(groups[group][student].name, fullName);
            printf("Enter student ID: ");
            scanf("%d", &groups[group][student].identity);
            printf("\nEnter number of courses taken in semester A: ");
            scanf("%d", &groups[group][student].nofCourses);
            for(int course = 0; course < groups[group][student].nofCourses; course++)
            {
                printf("Enter Course number and grade: ");
                scanf("%d %d", &groups[group][student].course_info[course].courseNum, &groups[group][student].course_info[course].grade);
            }
        }
    }

    int askedCourseNum, numOfStudents;
    char stuNames[GROUP_NUMBER * GROUP_STUDENT_NUMBER][MAX_FULL_NAME_LEN] = {'\0'};
    printf("Enter a course number: ");
    scanf("%d", &askedCourseNum);
    numOfStudents = getStudentNames(groups, GROUP_NUMBER, GROUP_STUDENT_NUMBER, askedCourseNum, stuNames);

    printf("\nNames after changing \"Lois\" to \"Lane\":\n");
    for(int student = 0; student < numOfStudents; student++)
    {
        int letterIndx = 7;
        int startIndex = 7;
        while(stuNames[student][letterIndx] != '\0')
        {
            char tempStr[MAX_NAME_LEN] = {'\0'};
            int tempIndx = 0;
            for(letterIndx ,tempIndx; stuNames[student][letterIndx] != ' ' && stuNames[student][letterIndx] != '\0'; letterIndx++, tempIndx++)
                tempStr[tempIndx] = stuNames[student][letterIndx];
            int offset = hasLois(tempStr);
            if(offset != -1)
                lois2Lane(stuNames, student, startIndex + offset); 
            startIndex = letterIndx + 1;
            letterIndx++;
        }
        printf("%s\n", stuNames[student]);
    }

    printf("\nNames after deleting names with \"Lex\":\n");
    for(int student = 0; student < numOfStudents; student++)
    {
        int letterIndx = 0;
        int startIndex = 0;
        while(stuNames[student][letterIndx] != '\0')
        {
            char tempStr[MAX_NAME_LEN] = {'\0'};
            int tempIndx = 0;
            for(letterIndx ,tempIndx; stuNames[student][letterIndx] != ' ' && stuNames[student][letterIndx] != '\0'; letterIndx++, tempIndx++)
                tempStr[tempIndx] = stuNames[student][letterIndx];
            if(hasLex(tempStr) == 1)
            {
                stuNames[student][0] = '\0';
                for(int temp = student; temp <= numOfStudents; temp++)
                    strcpy(stuNames[temp], stuNames[temp + 1]);
                numOfStudents--;
                letterIndx = -1;
            }
            startIndex = letterIndx + 1;
            letterIndx++;
        }
    }
    for(int student = 0; student < numOfStudents; student++)
        printf("%s\n", stuNames[student]);
    
    int grades[GROUP_NUMBER][GROUP_STUDENT_NUMBER + 1] = {'\0'};
    printf("\nGrades in course#%d:\n", askedCourseNum);
    for(int group = 0; group < GROUP_NUMBER; group++)
    {
        grades[group][0] = 0;
        if(group == 0)
            printf("GroupA: ");
        else if(group == 1)
            printf("GroupB: ");
        else
            printf("GroupC: ");
        int index = 1;
        for(int student = 0; student < GROUP_STUDENT_NUMBER; student++)
        {
            for(int course = 0; course < groups[group][student].nofCourses; course++)
            {
                if(groups[group][student].course_info[course].courseNum == askedCourseNum)
                {
                    grades[group][index] = groups[group][student].course_info[course].grade;
                    printf("%d ", groups[group][student].course_info[course].grade);
                    grades[group][0]++;
                    index++;
                }
            }
        }
        printf("\n");
    }

    int max = 0, secondMax = 0, group = 0;
    printf("\nMaximum grades in course#%d:\n", askedCourseNum);
    for(group; group < GROUP_NUMBER; group++)
        {
            if(group == 0)
                printf("GroupA: ");
            else if(group == 1)
                printf("GroupB: ");
            else
                printf("GroupC: ");
            max = getMax(grades[group], grades[group][0] + 1);
            secondMax = getMax(grades[group], grades[group][0] + 1);
            if(max == 0 && secondMax == 0)
                printf("no grades found in group\n");
            else if(max != 0 && secondMax == 0)
                printf("max grade is: %d (no second max found)\n", max);
            else
                printf("max grade is: %d and second max is: %d\n", max, secondMax);
        }
}