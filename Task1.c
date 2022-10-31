#include <stdio.h>

int main() {
    int id;
    printf("Welcome to MTA-Pizza!\n\n");
    printf("*****\n ***\n  *\n\n");
    printf("Please enter your ID number:\n");
    scanf_s("%d", &id);
    printf("\nOur menu:\n");
    printf("*********\n");
    printf("Basic pizza: 60.00 NIS for 40X40 size pizza\n");
    printf("Toppings for basic size pizza:\n");
    printf("Olives: 10 NIS\n");
    printf("Mushrooms: 12 NIS\n\n");
    printf("Your order details:\n");
    printf("*******************\n");
    printf("ID number: %09d\n", id);
    printf("Thank you for your order!");
}