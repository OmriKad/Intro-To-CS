#include <stdio.h>

void main() {
    int id;
    int length;
    int width;
    float topping1 = 0.0;
    float topping2 = 0.0;
    int delivery;
    float total;
    // Welcome page with customer ID request. 
    printf("Welcome to MTA-Pizza!\n\n");
    printf("*****\n ***\n  *\n\n");
    printf("Please enter your ID number:\n");
    scanf_s("%d", &id);
    // Menu info print.
    printf("\nOur menu:\n");
    printf("*********\n");
    printf("Basic pizza: 60.00 NIS for 40X40 size pizza\n");
    printf("Toppings for basic size pizza:\n");
    printf("Olives: 10 NIS\n");
    printf("Mushrooms: 12 NIS\n\n");
    // The customer chooses pizza size and stored accordingly. The total basic price (toppings not included) is calculated and adds up.  
    printf("Please enter your pizza's length (cm): ");
    scanf_s("%d", &length);
    printf("Please enter your pizza's width (cm): ");
    scanf_s("%d", &width);
    total = ((width * length) / 1600) * 60;
    // Customer chooses optional toppings and the area they cover the pizza. Price is added accordingly to the selected area. 
    printf("\nPlease choose the toppings:\n");
    printf("\nOlives - Enter 1 for the whole pizza\n0.5 for half\n0.25 for quarter\nor 0 for none: ");
    scanf_s("%f", &topping1);
    total += ((width * length * topping1) / 1600) * 10;
    printf("\nMushrooms - Enter 1 for the whole pizza\n0.5 for half\n0.25 for quarter\nor 0 for none: ");
    scanf_s("%f", &topping2);
    total += ((width * length * topping2) / 1600) * 12;
    // Optional delivery.
    printf("\nDo you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
    scanf_s("%d", &delivery);
    total += delivery * 15;
    // Total order info is printed for the customer.
    printf("\nYour order details:\n");
    printf("*******************\n");
    // The ID value is formated to show only 9 digits and 0 fillings if necessary.
    printf("ID number: %09d\n", id);
    printf("Pizza size: %dx%d\n", length, width);
    // Total price is formated to show 2 digits after decimal point precision.
    printf("Total price: %.2f\n", total);
    // The 17% tax is added to the float and then the expression is casted into an integer to round down the price.
    printf("Total price with tax (rounded down): %d\n", (int)(total * 1.17));
    printf("Thank you for your order!");
}