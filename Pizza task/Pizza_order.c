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
    if (counter > 9)
        return 0;
    return 1;
}

// Checks if the check digit is correct by the protocol.
int checkDigit(int id)
{
    int mult = 1, sum = 0, dig, checkDig;
    checkDig = id % 10;
    id /= 10;
    while (id)
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
    if ((sum + checkDig) % 10 == 0)
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
            printf("Invalid ID number! try again.\n");
            printf("Please enter your ID number:\n");
            scanf("%d", &id);
        }
        else if (checkDigit(id) == 0)
        {
            printf("Invalid check digit! try again.\n");
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
    printf("Pinapple: %d NIS\n\n", (int)PINAP_PRICE);
    printf("Dough type for basic size pizza:\n");
    printf("Regular: %d NIS\n", (int)REGULAR_DOUGH);
    printf("Vegan: %d NIS\n", (int)VEGAN_DOUGH);
    printf("Whole wheat: %d NIS\n", (int)WW_DOUGH);
    printf("Gluten free: %d NIS\n\n", (int)GF_DOUGH);
}

// Customer enters the number of pizzas for order. If a non positive number is entered the user is prompted to try again.
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

// The customer chooses pizza size and stored accordingly. The total basic price (toppings not included) is calculated and adds up.  
PIZZA getPizzaDimensions()
{   
    PIZZA pizza;
    pizza.price = 0;
    pizza.toppings_sum = 0.0;
    int flag1 = 0, flag2 = 0;

    while(flag1 == 0)
    {
        printf("Please enter your pizza's length (cm): ");
        scanf("%f", &pizza.length);
        if ((pizza.length - (int)pizza.length) != 0 || (pizza.length < 10) || (pizza.length > 40) || ((int)pizza.length % 2 != 0))
        {
            printf("Invalid length! Try again.\n");
        }
        else
            flag1 = 1;
    }
    
    while(flag2 == 0)
    {
        printf("Please enter your pizza's width (cm): ");
        scanf("%f", &pizza.width);
        if ((pizza.width - (int)pizza.width) != 0 || (pizza.width < 10) || (pizza.width > 80) || ((int)pizza.width % 2 != 0))
        {
            printf("Invalid width! Try again.\n");
        }
        else
            flag2 = 1;    
    }
    pizza.price += ((pizza.width * pizza.length) / (BASE_LEN * BASE_WID)) * BASE_PRICE;
    return pizza;
}

// The customer choosese dough type.
PIZZA getDoughType(PIZZA pizza)
{
    int flag = 0;
    while(flag == 0)
    {
        printf("\nPlease enter the pizza's dough type:\nr - for regular\nv - for vegan\nw - for whole wheat\nf - for gluten-free\n");
        scanf(" %c", &pizza.doughType);
        switch (pizza.doughType)
        {
        case 'r':
        {
            pizza.doughType = REGULAR_DOUGH;
            flag = 1;
            break;
        }
        case 'v':
        {
            pizza.doughType = VEGAN_DOUGH;
            flag = 1;
            break;
        }
        case 'w':
        {
            pizza.doughType = WW_DOUGH;
            flag = 1;
            break;
        }
        case 'f':
        {
            pizza.doughType = GF_DOUGH;
            flag = 1;
            break;
        }
        default:
        {
            printf("Invalid choice! Try again.\n");
        }
        }
    }
    pizza.price += ((pizza.width * pizza.length) / (BASE_LEN * BASE_WID)) * pizza.doughType;
    return pizza;
}


void toppingSelect(double *pizzaTopPtr, double *pizzaSumPtr, double *pizzaPricePtr, double length, double width, int topping)
{
    int flag = 0, choise;
    while(flag == 0)
    {
        switch (topping)
        {
            case 1:
            {
                printf("\nOlives (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
                break;
            }
            case 2:
            {
                printf("\nMushrooms (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
                break;
            }
            case 3:
            {
                printf("\nTomatos (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
                break;
            }
            case 4:
            {
                printf("\nPineapple (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
                break;
            }
        }
        scanf("%d", &choise);
        switch (choise) 
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
    
}

/* This program is a pizza ordering service
   that recives customer selections, calculates
   the total sum and prints out the data. */
void main()
{
    int id, delivery_opt, num_of_pizzas, vat_total, payment, change, i;
    double total = 0.0;
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
        

        // Pizza summery print and adding to total sum
        printf("\nPizza #%d details:\n*******************\n", i);
        printf("Pizza size: %dx%d\n", (int)pizza.length, (int)pizza.width);
        printf("Pizza price (without tax): %.2lf\n", pizza.price);
        total += pizza.price;
    }

    printf("\n*************************************************\n");
    // Optional delivery.
    printf("Do you want delivery for the price of %d NIS? Enter 1 for delivery or 0 for pick-up: ", (int)DELIVERY_PRICE);
    scanf("%d", &delivery_opt);
    if (!(delivery_opt == 1 || delivery_opt == 0)) {
        printf("Invalid choice! Pick-up was chosen as a default.\n");
        delivery_opt = 0;
    }
    total += delivery_opt * DELIVERY_PRICE;

    // Total order info is printed for the customer.
    printf("\nYour order details:\n");
    printf("*******************\n");

    // The ID value is formated to show only 9 digits and 0 fillings if necessary.
    printf("ID number: %09d\n", id);
    printf("Number of pizzas: %d\n", i-1);

    // Total price is formated to show 2 digits after decimal point precision.
    printf("Total price: %.2f\n", total);

    // The VAT is added to the float and then the expression is casted into an integer to round down the price.
    vat_total = (int)(total * VAT);
    printf("Total price with tax (rounded down): %d\n\n", vat_total);
    
    // Payment system.
    while (vat_total > 0) {
        printf("Please enter your payment: ");
        scanf("%d", &payment);
        vat_total -= payment;
        if (vat_total < 0) {
            change = (-1) * (vat_total);
            printf("Your change is %d NIS using: \n", change);
            if ((change / 10) > 0) {
                printf("%d coin(s) of ten\n", (change / 10));
                change %= 10;
            }
            if ((change / 5) > 0) {
                printf("%d coin(s) of five\n", (change / 5));
                change %= 5;
            }
            if ((change / 2) > 0) {
                printf("%d coin(s) of two\n", (change / 2));
                change %= 2;
            }
            if (change > 0) {
                printf("%d coin(s) of one\n", change);
                printf("Thank you for your order!");
                break;
            }
            if (change == 0) {
                printf("Thank you for your order!");
                break;
            }
            
        }
        else if (vat_total == 0) {
            printf("Thank you for your order!");
            break;
        }

        printf("Your remaining balance is: %d\n", vat_total);
            
    }

}