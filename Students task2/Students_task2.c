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

/* The function receive STUDENT multi-dim array of students, rows & cols borders, asked course num and an empty char array for storing the data that is being printed for following modulations.
The func returns the number of students learning the given course. */
int getStudentNames(STUDENT stuData[][GROUP_STUDENT_NUMBER], int rows, int cols, int courseNum, char stuNames[][MAX_FULL_NAME_LEN])
{
    printf("Names of students in course#%d:\n", courseNum);
    int numOfStudents = 0; // Counter of students learning the course.
    for(int group = 0; group < rows; group++) // For each group, each student and each course, check if the student course num corresponds with the query.
    {
        for(int student = 0; student < cols; student++)
        {
            for(int course = 0; course < stuData[group][student].nofCourses; course++)
            {
                if(stuData[group][student].course_info[course].courseNum == courseNum)
                {
                    char tempStr[MAX_FULL_NAME_LEN] = {'\0'}; // The student has a course num with the wanted query, a string is initialized.
                    switch (group) // The format specifies the Group name at the beginning.
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
                    strcat(tempStr, stuData[group][student].name); // The name is being concatenated.
                    strcpy(stuNames[numOfStudents], tempStr); // The completed string is copied into the result array.
                    printf("%s\n", tempStr); // Result is also being printed.
                    numOfStudents++; // Increment of found students by 1.
                    break; // Because a student could learn the same course twice in a semester, the loop breaks in order to not cause doubles.
                }
            }
        }
    }
    return numOfStudents; 
}

// The function receive a strings array of students, student index and the char index in his name and changed the values from  Lois to Lane. 
void lois2Lane(char stuNames[][MAX_FULL_NAME_LEN], int student, int index)
{
    stuNames[student][index + 1] = 'a'; 
    stuNames[student][index + 2] = 'n';
    stuNames[student][index + 3] = 'e';
}

// The function takes a string and checks if it has Lois in it or in a substring of it. if no Lois was found returns -1, else returns the index of the Lois beginning.
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

// The function takes a string and checks if it has Lex in it. If so returns 1, else returns 0.
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

// The function takes an int arr and border of the array, and returns the Max num of the array. 
int getMax(int arr[], int lim)
{
    int index = 1; // The 0 index is reserved for the summing of student. Therfore starts at 1.
    int maxIndex = 0; // Index of the Max (default is 0).
    int max = 0; // Current Max (default is 0).
    for(index; index < lim; index++) // For each grade, if current looked upon grade is higher then the current, it is updated with it's index.
        {
            if(arr[index] > max)
            {
                max = arr[index];
                maxIndex = index;
            }
        }
    arr[maxIndex] = 0; // The highest num is changed to 0 for future search for second max. 
    return max; // Max num is returned.
}       

int main()
{
    // Welcome message.
    printf("********************\n* Welcome Students *\n********************\n");
    STUDENT groups[GROUP_NUMBER][GROUP_STUDENT_NUMBER]; // Creating a multi-dimensional array of STUDENT type. Rows as groups and columns as students. 
    for(int group = 0; group < GROUP_NUMBER; group++)
    {
        char groupName[8]; // A string for for group prefix.
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
        // Asks the user to enter data for group n out of 3.
        printf("Enter students data for %s:\n", groupName);
        printf("___________________________\n");
        // Runs over the loop and for each student out of 6, request info from the user. 
        for(int student = 0; student < GROUP_STUDENT_NUMBER; student++)
        {
            char firstName[MAX_FULL_NAME_LEN]; // String for the first name.
            char lastName[MAX_FULL_NAME_LEN]; // String for the last name.
            char fullName[MAX_FULL_NAME_LEN]; // String for Concatenated name.
            printf("Enter student first name and last name (seperated by spaces): ");
            scanf("%s", firstName); // As scanf works until it hits a whitespace, we store the info at firstName.
            strcpy(fullName, firstName); // Using strcpy to also set the fullName.
            strcat(fullName, " "); // Adding whitespace manually.
            scanf("%s", lastName); // Scans the rest of the name and stores at last name.
            strcat(fullName, lastName); // Concatenates last name to full name.
            strcpy(groups[group][student].name, fullName); // copying the full name to the current student name field in the current group.
            printf("Enter student ID: ");
            scanf("%d", &groups[group][student].identity); // Receiving ID num and storing accordingly.
            printf("\nEnter number of courses taken in semester A: ");
            scanf("%d", &groups[group][student].nofCourses); // Receiving num of courses and storing accordingly.
            for(int course = 0; course < groups[group][student].nofCourses; course++) // For each course runs and gets course number and grade.
            {
                printf("Enter Course number and grade: ");
                scanf("%d %d", &groups[group][student].course_info[course].courseNum, &groups[group][student].course_info[course].grade);
            }
        }
    }

    // Asked course print section.
    int askedCourseNum, numOfStudents;
    char stuNames[GROUP_NUMBER * GROUP_STUDENT_NUMBER][MAX_FULL_NAME_LEN] = {'\0'}; // Initializing a null char multi-dim char array for printing strings.
    printf("Enter a course number: ");
    scanf("%d", &askedCourseNum); // Receive the course query and store in the variable. 
    numOfStudents = getStudentNames(groups, GROUP_NUMBER, GROUP_STUDENT_NUMBER, askedCourseNum, stuNames); // Calling the getStudentName func and store the returned number of student who learned the asked course.

    // Lois to Lane changing section.
    printf("\nNames after changing \"Lois\" to \"Lane\":\n");
    for(int student = 0; student < numOfStudents; student++) // For each student out of the found number of students learning the course, inspects if the student has Lois in his name and changes to Lane.
    {
        int letterIndx = 7; // The index of the adding letter index. Starts at 7 bc the Group name is irrelevant.
        int startIndex = 7; // The start of the name index, for usage of later purposes. ''    ''  ''  ''.
        while(stuNames[student][letterIndx] != '\0') // The sign of the end of the student name string.
        {
            char tempStr[MAX_NAME_LEN] = {'\0'}; // A temp string to hold first then last name info.
            int tempIndx = 0; // The index of the start of the temp string.
            for(letterIndx ,tempIndx; stuNames[student][letterIndx] != ' ' && stuNames[student][letterIndx] != '\0'; letterIndx++, tempIndx++) // As long as the char isn't a whitespace or null keep adding chars to the temp string.
                tempStr[tempIndx] = stuNames[student][letterIndx];
            int offset = hasLois(tempStr); // hasLois is called with temp string.
            if(offset != -1) // The offset is not -1 so it has a Lois in it.
                lois2Lane(stuNames, student, startIndex + offset); // lois2Lane is called to change the string chars.
            startIndex = letterIndx + 1; // Both startIndex and letterIndx are being placed at the beginning of the next word of the string.
            letterIndx++;
        }
        printf("%s\n", stuNames[student]); // The final string is printed.
    }

    // Has lex section.
    printf("\nNames after deleting names with \"Lex\":\n");
    for(int student = 0; student < numOfStudents; student++) // For each student searches if it has Lex in his name. If so, modifies the student char and closes the gaps in the array.
    {
        int letterIndx = 0; // Same manner as previous.
        int startIndex = 0;
        while(stuNames[student][letterIndx] != '\0')
        {
            char tempStr[MAX_NAME_LEN] = {'\0'};
            int tempIndx = 0;
            for(letterIndx ,tempIndx; stuNames[student][letterIndx] != ' ' && stuNames[student][letterIndx] != '\0'; letterIndx++, tempIndx++)
                tempStr[tempIndx] = stuNames[student][letterIndx];
            if(hasLex(tempStr) == 1) // Checks if name has Lex in it.
            {
                stuNames[student][0] = '\0'; // Lex was found, the current student name string, first char, is being changed to null.
                for(int temp = student; temp <= numOfStudents; temp++) // All the students from the current student all the way to end are being copied back to close the gaps.
                    strcpy(stuNames[temp], stuNames[temp + 1]);
                numOfStudents--; // One less student in the total sum.
                letterIndx = -1; // The letter index is being set to -1 for after being incremented to 0.
            }
            startIndex = letterIndx + 1;
            letterIndx++;
        }
    }
    for(int student = 0; student < numOfStudents; student++) // Printing the updated array of students.
        printf("%s\n", stuNames[student]);
    
    // Grades section.
    int grades[GROUP_NUMBER][GROUP_STUDENT_NUMBER + 1] = {'\0'}; // An int mult-dim array is being created for storing grades. the +1 is for extra space for storing the number of student at each course at index 0.
    printf("\nGrades in course#%d:\n", askedCourseNum);
    for(int group = 0; group < GROUP_NUMBER; group++) // For each group, placing a 0 at index 0. Prints the corresponding group name.
    {
        grades[group][0] = 0;
        if(group == 0)
            printf("GroupA: ");
        else if(group == 1)
            printf("GroupB: ");
        else
            printf("GroupC: ");
        int index = 1; // Index of where grades writing begins.
        for(int student = 0; student < GROUP_STUDENT_NUMBER; student++) // For each student in the group, and for each course the student has learned, if the course num corresponds:
        {
            for(int course = 0; course < groups[group][student].nofCourses; course++)
            {
                if(groups[group][student].course_info[course].courseNum == askedCourseNum)
                {                                                               
                    grades[group][index] = groups[group][student].course_info[course].grade; // The grade of the student is being added to the array.
                    printf("%d ", groups[group][student].course_info[course].grade); // Also being printed.
                    grades[group][0]++; // A student learning the course was found so index 0 is incremented by 1.
                    index++; // For next found grade.
                }
            }
        }
        printf("\n");
    }

    // Find max Grade section.
    int max = 0, secondMax = 0, group = 0; // Variables to hold current max num, second max num and the group index.
    printf("\nMaximum grades in course#%d:\n", askedCourseNum);
    for(group; group < GROUP_NUMBER; group++) // For each group, searches the max and second max num and printing the results.
        {
            if(group == 0)
                printf("GroupA: ");
            else if(group == 1)
                printf("GroupB: ");
            else
                printf("GroupC: ");
            max = getMax(grades[group], grades[group][0] + 1); // First call to find the max.
            secondMax = getMax(grades[group], grades[group][0] + 1); // Second call to find the second max.
            if(max == 0 && secondMax == 0) // Only happens when no grades were found.
                printf("no grades found in group\n");
            else if(max != 0 && secondMax == 0) // When only 1 max was found.
                printf("max grade is: %d (no second max found)\n", max);
            else // Necessarily has 2 max nums to be printed.
                printf("max grade is: %d and second max is: %d\n", max, secondMax);
        }
}