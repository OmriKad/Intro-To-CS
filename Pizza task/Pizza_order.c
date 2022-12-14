// Omri Kadmon
// 209017383

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define VAT 1.17
#define DELIVERY_PRICE 15.0
#define BASE_LEN 40.0
#define BASE_WID 50.0
#define BASE_PRICE 70.0
#define OLIVE_PRICE 10.0
#define MUSH_PRICE 12.0
#define TOMATO_PRICE 9.0
#define PINAP_PRICE 14.0
#define REGULAR_DOUGH 0.0
#define VEGAN_DOUGH 5.0
#define WW_DOUGH 3.0
#define GF_DOUGH 4.0

typedef struct Pizza {
    float length; // pizza length (cm)
    float width; // pizza width (cm)
    char doughType; // dough type ('r'/'v'/'w'/'f')
    double olives; // olives amount (0/1/0.5/0.25)
    double mushrooms; // mushrooms amount (0/1/0.5/0.25)
    double tomatoes; // tomatoes amount (0/1/0.5/0.25)
    double pineapple; // pineapple amount (0/1/0.5/0.25)
    double toppings_sum; // Represents the pizza toppings as a fraction (can't exceed 1)
    char q1; // topping type on first quarter ('O'/'M'/'T'/'P')
    char q2; // topping type on second quarter ('O'/'M'/'T'/'P')
    char q3; // topping type on third quarter ('O'/'M'/'T'/'P')
    char q4; // topping type on fourth quarter ('O'/'M'/'T'/'P')
    double price; // pizza price (without tax)
}PIZZA;

// An int id is entered, checks if the number length exceedes 9 digits.
int idLen(int id)
{
    int counter = 0;
    for (counter; id != 0; counter ++)
        {
            id /= 10;
        }
    if (counter > 9 || counter == 0)
        return 0;
    return 1;
}

// Checks if the check digit is correct by the protocol.
int checkDigit(int id)
{
    int mult = 1, sum = 0, dig, checkDig;
    checkDig = id % 10; // Far right digit of id num.
    id /= 10;
    while (id) // Every iteration the far right digit is being multiplied with alternating 1 or 2 and added to a sum.  
    {
        dig = id % 10;
        if (mult == 1)
        {
            if ((dig * 2) >= 10)
            {
                sum += ((dig * 2) - 9);
                mult = 2;
            }
            else
            {
                sum += dig * 2;
                mult = 2;
            }
        }
        else
        {
            sum += dig;
            mult = 1;
        }
        id /= 10;
    }
    if ((sum + checkDig) % 10 == 0) // The rule for correct check digit. If correct 1 is returned, else 0.
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Asks the user for an id number, checks for validity with "idLen" & "checkDigit", if passed returns the number else prompts to try again.
int getIdNumber()
{
    int id;
    printf("Please enter your ID number:\n");
    scanf("%d", &id);
    while (idLen(id) == 0 || checkDigit(id) == 0)
    {
        if (idLen(id) == 0)
        {
            printf("Invalid ID number! Try again.\n");
            printf("Please enter your ID number:\n");
            scanf("%d", &id);
        }
        else if (checkDigit(id) == 0)
        {
            printf("Invalid check digit! Try again.\n");
            printf("Please enter your ID number:\n");
            scanf("%d", &id);
        }
    }
    return id;
}

// Menu info print.
void printMenu()
{
    printf("\nOur menu:\n");
    printf("*********\n");
    printf("Basic pizza: %.2f NIS for %dx%d size pizza\n\n", BASE_PRICE, (int)BASE_LEN, (int)BASE_WID);
    printf("Toppings for basic size pizza:\n");
    printf("Olives: %d NIS\n", (int)OLIVE_PRICE);
    printf("Mushrooms: %d NIS\n", (int)MUSH_PRICE);
    printf("Tomatoes: %d NIS\n", (int)TOMATO_PRICE);
    printf("Pineapple: %d NIS\n\n", (int)PINAP_PRICE);
    printf("Dough type for basic size pizza:\n");
    printf("Regular: %d NIS\n", (int)REGULAR_DOUGH);
    printf("Vegan: %d NIS\n", (int)VEGAN_DOUGH);
    printf("Whole wheat: %d NIS\n", (int)WW_DOUGH);
    printf("Gluten free: %d NIS\n\n", (int)GF_DOUGH);
}

//  Choose the number of pizzas for order as an int. If a non positive number is entered the user is prompted to try again.
int getNumOfPizzas()
{
    int num_of_pizzas;
    printf("How many pizzas would you like to order? ");
    scanf("%d", &num_of_pizzas);
    while (num_of_pizzas <= 0)
    {
        printf("Invalid choice! Try again.\n");
        printf("How many pizzas would you like to order? ");
        scanf("%d", &num_of_pizzas);
    }
    return num_of_pizzas;
}

// Choose pizza sizes and store accordingly. The total basic price (toppings not included) is calculated and adds up.  
PIZZA getPizzaDimensions()
{   
    PIZZA pizza; // Pizza initializtion.
    pizza.q1 = ' ', pizza.q2 = ' ', pizza.q3 = ' ', pizza.q4 = ' '; // Q's fields are set to ' ' as a default.
    pizza.price = 0;
    pizza.toppings_sum = 0.0;
    int flag = 0; // Flag to mark valid exit of while loops.

    while(flag == 0)
    {
        printf("Please enter your pizza's length (cm): ");
        scanf("%f", &pizza.length);
        if ((pizza.length - (int)pizza.length) != 0 || (pizza.length < 10) || (pizza.length > 40) || ((int)pizza.length % 2 != 0)) // Valid pizza length is an even int that is 10-40 (inclusice).
        {
            printf("Invalid length! Try again.\n");
        }
        else
            flag = 1;
    }
    flag = 0;
    while(flag == 0)
    {
        printf("Please enter your pizza's width (cm): ");
        scanf("%f", &pizza.width);
        if ((pizza.width - (int)pizza.width) != 0 || (pizza.width < 10) || (pizza.width > 80) || ((int)pizza.width % 2 != 0)) // Valid pizza width is an even int that is 10-80 (inclusice).
        {
            printf("Invalid width! Try again.\n");
        }
        else
            flag = 1;    
    }
    pizza.price += ((pizza.width * pizza.length) / (BASE_LEN * BASE_WID)) * BASE_PRICE; // Price is being calculated as the ratio of selected sizes and basic sizes, times the basic price.
    return pizza;
}

// Choose dough type.
PIZZA getDoughType(PIZZA pizza)
{
    int flag = 0; // Flag to mark valid exit of while loops.
    double doughPrice;
    while(flag == 0)
    {
        printf("\nPlease enter the pizza's dough type:\nr - for regular\nv - for vegan\nw - for whole wheat\nf - for gluten-free\n");
        scanf(" %c", &pizza.doughType);
        switch (pizza.doughType)
        {
        case 'r':
        {
            doughPrice = REGULAR_DOUGH;
            flag = 1;
            break;
        }
        case 'v':
        {
            doughPrice = VEGAN_DOUGH;
            flag = 1;
            break;
        }
        case 'w':
        {
            doughPrice = WW_DOUGH;
            flag = 1;
            break;
        }
        case 'f':
        {
            doughPrice = GF_DOUGH;
            flag = 1;
            break;
        }
        default:
        {
            printf("Invalid choice! Try again.\n");
        }
        }
    }
    pizza.price += ((pizza.width * pizza.length) / (BASE_LEN * BASE_WID)) * doughPrice;
    return pizza;
}

// Part of the topping selection phase - responsible for the pizza fraction control as the toppings cannot exceed 1. If an error occures the user promted to try again.
void toppingSelect(double *pizzaTopPtr, double *pizzaSumPtr, double *pizzaPricePtr, double length, double width, int topping)
{
    int flag = 0, choise;
    switch (topping) // Topping is recieved by previous function as an int (there are only 4 toppings available)
    {
        case 1:
        {
            printf("\nOlives (choose 0-3):\n");
            break;
        }
        case 2:
        {
            printf("\nMushrooms (choose 0-3):\n");
            break;
        }
        case 3:
        {
            printf("\nTomatos (choose 0-3):\n");
            break;
        }
        case 4:
        {
            printf("\nPineapple (choose 0-3):\n");
            break;
        }
    }
    while(flag == 0) // Guards for faulty inputs, prompts to try again.
    {
        printf("0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
        scanf("%d", &choise);
        switch (choise) // Switches based on user input, if false breaks and the guard bounces it back to here. If true the value is written using the pointer of the topping recieved.
        {
            case 0:
            {
                *pizzaTopPtr = 0;
                flag = 1;
                break;
            }
            case 1:
            {
                if (*pizzaSumPtr + 1.0 > 1.0)
                {
                    printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");
                    break;
                }
                else
                {
                    *pizzaTopPtr = 1;
                    *pizzaSumPtr += 1;
                    flag = 1;
                    break;
                }
            }
            case 2:
            {
                if (*pizzaSumPtr + 0.5 > 1.0)
                {
                    printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");
                    break;
                }
                else
                {
                    *pizzaTopPtr = 0.5;
                    *pizzaSumPtr += 0.5;
                    flag = 1;
                    break;
                }
            }
            case 3:
            {
                if (*pizzaSumPtr + 0.25 > 1.0)
                {
                    printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");
                    break;
                }
                else 
                {
                    *pizzaTopPtr = 0.25;
                    *pizzaSumPtr += 0.25;
                    flag = 1;
                    break;
                }
            }
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    // If all went well, Finally calculates the price and adds to the price pointer of the given pizza.
    if (topping == 1)
        *pizzaPricePtr += ((width * length * (*pizzaTopPtr)) / (BASE_LEN * BASE_WID)) * OLIVE_PRICE;
    else if (topping == 2)
        *pizzaPricePtr += ((width * length * (*pizzaTopPtr)) / (BASE_LEN * BASE_WID)) * MUSH_PRICE;
    else if (topping == 3) 
        *pizzaPricePtr += ((width * length * (*pizzaTopPtr)) / (BASE_LEN * BASE_WID)) * TOMATO_PRICE;
    else if (topping == 4)
        *pizzaPricePtr += ((width * length * (*pizzaTopPtr)) / (BASE_LEN * BASE_WID)) * PINAP_PRICE;
    return;
}

// Customer chooses optional toppings and the area they cover the pizza. Price is added accordingly to the selected area. 
PIZZA getToppings(PIZZA pizza)
{
    printf("\nPlease choose the toppings:\n");
    // The topping select function is the drive function for the logic regard toppings, it is called 4 times in this order with different arguments.
    toppingSelect(&pizza.olives, &pizza.toppings_sum, &pizza.price, pizza.length, pizza.width, 1);
    if (pizza.toppings_sum == 1)
        return pizza;
    toppingSelect(&pizza.mushrooms, &pizza.toppings_sum, &pizza.price, pizza.length, pizza.width, 2);
    if (pizza.toppings_sum == 1)
        return pizza;
    toppingSelect(&pizza.tomatoes, &pizza.toppings_sum, &pizza.price, pizza.length, pizza.width, 3);
    if (pizza.toppings_sum == 1)
        return pizza;
    toppingSelect(&pizza.pineapple, &pizza.toppings_sum, &pizza.price, pizza.length, pizza.width, 4);
    if (pizza.toppings_sum == 1)
        return pizza;
    return pizza;
}

// Part of the printPizzaDetails function. Responsible for naming each quarter with the correct charecter of the pizza topping. All char selection follows a number hierarchy based on vacancy (quarter 1 goes first, then 2 and so on). 
void quarterSelect(double *pizzaToppingPtr, char *pizzaQ1Ptr, char *pizzaQ2Ptr, char *pizzaQ3Ptr, char *pizzaQ4Ptr, char topping)
{
    if (*pizzaQ1Ptr == ' ') // If quarter 1 is empty, we have 3 options to fill the pizza with the given topping (based on topping fraction value given).
    {
        if (*pizzaToppingPtr == 0.25)
        {
            *pizzaQ1Ptr = topping;
            return;
        }
        else if (*pizzaToppingPtr == 0.5)
        {
            *pizzaQ1Ptr = topping, *pizzaQ2Ptr = topping;
            return;
        }
        else if (*pizzaToppingPtr == 1)
        {
            *pizzaQ1Ptr = topping, *pizzaQ2Ptr = topping, *pizzaQ3Ptr = topping, *pizzaQ4Ptr = topping;
            return;
        }
    }
    else if (*pizzaQ2Ptr == ' ') // If quarter 2 is empty, we have 2 options to fill the pizza with the given topping (based on topping fraction value given).
    {
        if (*pizzaToppingPtr == 0.25)
        {
            *pizzaQ2Ptr = topping;
            return;
        }
        else if (*pizzaToppingPtr == 0.5) 
        {
            *pizzaQ2Ptr = topping, *pizzaQ3Ptr = topping;
            return;
        }
    }
    else if (*pizzaQ3Ptr == ' ') // If quarter 3 is empty, we have 2 options to fill the pizza with the given topping (based on topping fraction value given).
    {
        if (*pizzaToppingPtr == 0.25)
        {
            *pizzaQ3Ptr = topping;
            return;
        }
        else if (*pizzaToppingPtr == 0.5)
        {
            *pizzaQ3Ptr = topping, *pizzaQ4Ptr = topping;
            return;
        }
    }
    else if (*pizzaQ4Ptr == ' ') // If quarter 4 is empty, we have 1 option to fill the pizza with the given topping (based on topping fraction value given).
    {
        if (*pizzaToppingPtr == 0.25)
        {
            *pizzaQ4Ptr = topping;
            return;
        }
    }
}

// Part of the printPizzaDetails function. Prints the pizza according to the size, dough type and toppings. All stored in the current pizza struct.
void printPizza(PIZZA pizza)
{
    int i, j; // i - rows , j - columns.
    for (j = 0; j < pizza.width; j++)
        printf("%c", pizza.doughType); // Top crust.
    printf("\n");
    for (i = 0; i < (pizza.length - 2) / 2; i++) // First half of the pizza by rows.
    {
        printf("%c", pizza.doughType);
        for (j = 0; j < (pizza.width - 2) / 2 ; j++)
            printf("%c", pizza.q4);
        for (j = 0; j < (pizza.width - 2) / 2 ; j++)
            printf("%c", pizza.q1);
        printf("%c", pizza.doughType);
        printf("\n");
    }
    for (i = 0; i < (pizza.length - 2) / 2; i++) // Second half of the pizza by rows.
    {
        printf("%c", pizza.doughType);
        for (j = 0; j < (pizza.width - 2) / 2 ; j++)
            printf("%c", pizza.q3);
        for (j = 0; j < (pizza.width - 2) / 2 ; j++)
            printf("%c", pizza.q2);
        printf("%c", pizza.doughType);
        printf("\n");
    }
    for (j = 0; j < pizza.width; j++)
        printf("%c", pizza.doughType); // Lower crust.
    printf("\n");
}

void printPizzaDetails(PIZZA pizza, int i)
{
    quarterSelect(&pizza.olives, &pizza.q1, &pizza.q2, &pizza.q3, &pizza.q4, 'O');
    quarterSelect(&pizza.mushrooms, &pizza.q1, &pizza.q2, &pizza.q3, &pizza.q4, 'M');
    quarterSelect(&pizza.tomatoes, &pizza.q1, &pizza.q2, &pizza.q3, &pizza.q4, 'T');
    quarterSelect(&pizza.pineapple, &pizza.q1, &pizza.q2, &pizza.q3, &pizza.q4, 'P');
    // Pizza summery print and adding to total sum
    printf("\nPizza #%d details:\n*******************\n", i);
    printf("Pizza size: %dx%d\n", (int)pizza.length, (int)pizza.width);
    printf("Pizza price (without tax): %.2lf\n", pizza.price);
    printPizza(pizza);
}
 // Optional delivery.
int getDelivery()
{
    int delivery_opt, flag = 0;
    printf("Do you want delivery for the price of %d NIS? Enter 1 for delivery or 0 for pick-up: ", (int)DELIVERY_PRICE);
    scanf("%d", &delivery_opt);
    while (flag == 0)
    {
        if (!(delivery_opt == 1 || delivery_opt == 0))
        {
            printf("Invalid choice! Try again.\n");
            printf("Do you want delivery for the price of %d NIS? Enter 1 for delivery or 0 for pick-up: ", (int)DELIVERY_PRICE);
            scanf("%d", &delivery_opt);
        }
        else
            flag = 1;
    }
    return delivery_opt * DELIVERY_PRICE;
}

// Payment system.
void getPayment(int totalPrice)
{
    int change, payment;
    while (totalPrice > 0)
        {
            printf("Please enter your payment: ");
            scanf("%d", &payment);
            totalPrice -= payment;
            if (totalPrice < 0) 
            {
                change = (-1) * (totalPrice);
                printf("Your change is %d NIS using: \n", change);
                if ((change / 10) > 0)
                {
                    printf("%d coin(s) of ten\n", (change / 10));
                    change %= 10;
                }
                if ((change / 5) > 0) 
                {
                    printf("%d coin(s) of five\n", (change / 5));
                    change %= 5;
                }
                if ((change / 2) > 0) 
                {
                    printf("%d coin(s) of two\n", (change / 2));
                    change %= 2;
                }
                if (change > 0) 
                {
                    printf("%d coin(s) of one\n", change);
                    printf("Thank you for your order!");
                    break;
                }
                if (change == 0) 
                {
                    printf("Thank you for your order!");
                    break;
                }
            }
            else if (totalPrice == 0)
            {
                printf("Thank you for your order!");
                break;
            }
            printf("Your remaining balance is: %d\n", totalPrice);
        }
}

/* This program is a pizza ordering service
   that recives customer selections, calculates
   the total sum and prints out the data. */
void main()
{
    int id, num_of_pizzas, i, delivery_price, vat_total;
    double totalPrice = 0.0;
    PIZZA pizza;

    // Welcome page with logo. 
    printf(" Welcome to MTA-Pizza!\n\n");
    printf("*****\n ***\n  *\n\n");
    
    // Id request.
    id = getIdNumber();

    //Menu print.
    printMenu();

    // Iterations as the number of pizzas, For each one data is calculated.
    num_of_pizzas = getNumOfPizzas();
    for (i = 1; i <= num_of_pizzas; i++)
    {
        printf("\n*************************************************\nPizza #%d:\n\n", i);
        pizza = getPizzaDimensions();
        pizza = getDoughType(pizza);
        pizza = getToppings(pizza);
        printPizzaDetails(pizza, i);
        totalPrice += pizza.price;
    }

    printf("\n*************************************************\n");

    delivery_price = getDelivery();

    // Total order info is printed for the customer.
    printf("\nYour order details:\n");
    printf("*******************\n");

    // The ID value is formated to show only 9 digits and 0 fillings if necessary.
    printf("ID number: %09d\n", id);
    printf("Number of pizzas: %d\n", i-1);

    if (delivery_price != 0)
    {
        totalPrice += delivery_price;
        printf("Delivery\n");
    }
    else
        printf("Pick-up\n");

    // Total price is formated to show 2 digits after decimal point precision.
    printf("Total price: %.2f\n", totalPrice);

    // The VAT is added to the float and then the expression is casted into an integer to round down the price.
    vat_total = (int)(totalPrice * VAT);
    printf("Total price with tax (rounded down): %d\n\n", vat_total);

    getPayment(vat_total);
}