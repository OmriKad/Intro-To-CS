// Omri Kadmon
// 209017383

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define VAT 1.17
#define BASE_PRICE 60.0
#define OLIVE_PRICE 10.0
#define MUSH_PRICE 12.0
#define REGULAR_DOUGH 0.0
#define VEGAN_DOUGH 5.0
#define WW_DOUGH 3.0
#define GF_DOUGH 4.0

struct Pizza {
    float length; // pizza length (cm)
    float width; // pizza width (cm)
    char doughType; // dough type ('r'/'v'/'w'/'f')
    double olives; // olives amount (0/1/0.5/0.25)
    double mushrooms; // mushrooms amount (0/1/0.5/0.25)
    double toppings_sum; // Represents the pizza toppings as a fraction (can't exceed 1)
    double price; // pizza price (without tax)
};

/* This program is a pizza ordering service
   that recives customer selections, calculates
   the total sum and prints out the data. */
void main()
{
    int id, delivery, num_of_pizzas, vat_total, payment, change, i;
    double total = 0.0;

    // Welcome page with customer ID request. 
    printf(" Welcome to MTA-Pizza!\n\n");
    printf("*****\n ***\n  *\n\n");
    printf("Please enter your ID number:\n");
    scanf("%d", &id);

    // Menu info print.
    printf("\nOur menu:\n");
    printf("*********\n");
    printf("Basic pizza: %.2f NIS for 40x40 size pizza\n\n", BASE_PRICE);
    printf("Toppings for basic size pizza:\n");
    printf("Olives: %d NIS\n", (int)OLIVE_PRICE);
    printf("Mushrooms: %d NIS\n\n", (int)MUSH_PRICE);
    printf("Dough type for basic size pizza:\n");
    printf("Regular: %d NIS\n", (int)REGULAR_DOUGH);
    printf("Vegan: %d NIS\n", (int)VEGAN_DOUGH);
    printf("Whole wheat: %d NIS\n", (int)WW_DOUGH);
    printf("Gluten free: %d NIS\n\n", (int)GF_DOUGH);

    // Customer enters the number of pizzas for order. If a negative number is entered the procedure terminates.
    printf("How many pizzas would you like to order? ");
    scanf("%d", &num_of_pizzas);
    if (num_of_pizzas <= 0)
        printf("Thank you and goodbye.");

    else
    {
        // Iterations as the number of pizzas, For each one data is calculated.
        for (i = 1; i <= num_of_pizzas; i++)
        {
            printf("\n*************************************************\nPizza #%d:\n\n", i);
            struct Pizza pizza;
            pizza.price = 0;
            pizza.toppings_sum = 0.0;

            // The customer chooses pizza size and stored accordingly. The total basic price (toppings not included) is calculated and adds up.  
            printf("Please enter your pizza's length (cm): ");
            scanf("%f", &pizza.length);
            if ((pizza.length - (int)pizza.length) != 0 || (pizza.length < 10) || (pizza.length > 40) || ((int)pizza.length % 2 != 0))
            {
                printf("Invalid length! Basic length was chosen as a default.\n");
                pizza.length = 40.0;
            }

            printf("Please enter your pizza's width (cm): ");
            scanf("%f", &pizza.width);
            if ((pizza.width - (int)pizza.width) != 0 || (pizza.width < 10) || (pizza.width > 80) || ((int)pizza.width % 2 != 0))
            {
                printf("Invalid width! Basic width was chosen as a default.\n");
                pizza.width = 40.0;
            }
            pizza.price += ((pizza.width * pizza.length) / 1600.0) * BASE_PRICE;

            // The customer choosese dough type.
            printf("\nPlease enter the pizza's dough type:\nr - for regular\nv - for vegan\nw - for whole wheat\nf - for gluten-free\n");
            scanf(" %c", &pizza.doughType);
            switch (pizza.doughType)
            {
            case 'r':
            {
                pizza.doughType = REGULAR_DOUGH;
                break;
            }
            case 'v':
            {
                pizza.doughType = VEGAN_DOUGH;
                break;
            }
            case 'w':
            {
                pizza.doughType = WW_DOUGH;
                break;
            }
            case 'f':
            {
                pizza.doughType = GF_DOUGH;
                break;
            }
            default:
            {
                printf("Invalid choice! Regular dough was chosen as a default.\n");
                pizza.doughType = REGULAR_DOUGH;
            }
            }
            pizza.price += ((pizza.width * pizza.length) / 1600.0) * pizza.doughType;

            // Customer chooses optional toppings and the area they cover the pizza. Price is added accordingly to the selected area. 
            printf("\nPlease choose the toppings:\n");
            printf("\nOlives (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
            scanf(" %lf", &pizza.olives);
            switch ((int)pizza.olives) 
            {
            case 0:
            {
                pizza.olives = 0;
                break;
            }
            case 1:
            {
                pizza.olives = 1;
                pizza.toppings_sum += 1.0;
                break;
            }
            case 2:
            {
                pizza.olives = 0.5;
                pizza.toppings_sum += 0.5;
                break;
            }
            case 3:
            {
                pizza.olives = 0.25;
                pizza.toppings_sum += 0.25;
                break;
            }
            default:
            {
                printf("Invalid choice! Current topping not added.\n");
                pizza.olives = 0;
            }
            }
            pizza.price += ((pizza.width * pizza.length * pizza.olives) / 1600.0) * OLIVE_PRICE;

            printf("\nMushrooms (choose 0-3):\n0. None\n1. Whole pizza\n2. Half pizza\n3. Quarter pizza\n");
            scanf(" %lf", &pizza.mushrooms);
            switch ((int)pizza.mushrooms) 
            {
            case 0:
            {
                pizza.mushrooms = 0;
                break;
            }
            case 1:
            {
                if (pizza.toppings_sum + 1.0 > 1.0) {
                    printf("You have exceeded the maximum amount of toppings allowed on one pizza! Current topping not added.\n");
                    pizza.mushrooms = 0;
                    break;
                }
                else {
                    pizza.mushrooms = 1;
                    pizza.toppings_sum += 1;
                    break;
                }
            }
            case 2:
            {
                if (pizza.toppings_sum + 0.5 > 1.0) {
                    printf("You have exceeded the maximum amount of toppings allowed on one pizza! Current topping not added.\n");
                    pizza.mushrooms = 0;
                    break;
                }
                else {
                    pizza.mushrooms = 0.5;
                    pizza.toppings_sum += 0.5;
                    break;
                }
            }
            case 3:
            {
                if (pizza.toppings_sum + 0.25 > 1.0) {
                    printf("You have exceeded the maximum amount of toppings allowed on one pizza! Current topping not added.\n");
                    pizza.mushrooms = 0;
                    break;
                }
                else {
                    pizza.mushrooms = 0.25;
                    pizza.toppings_sum += 0.25;
                    break;
                }
            }
            default:
            {
                printf("Invalid choice! Current topping not added.\n");
                pizza.mushrooms = 0;
            }
            }
            pizza.price += ((pizza.width * pizza.length * pizza.mushrooms) / 1600.0) * MUSH_PRICE;

            // Pizza summery print and adding to total sum
            printf("\nPizza #%d details:\n*******************\n", i);
            printf("Pizza size: %dx%d\n", (int)pizza.length, (int)pizza.width);
            printf("Pizza price (without tax): %.2lf\n", pizza.price);
            total += pizza.price;
        }

        printf("\n*************************************************\n");
        // Optional delivery.
        printf("Do you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
        scanf("%d", &delivery);
        if (!(delivery == 1 || delivery == 0)) {
            printf("Invalid choice! Pick-up was chosen as a default.\n");
            delivery = 0;
        }
        total += delivery * 15.0;

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
}