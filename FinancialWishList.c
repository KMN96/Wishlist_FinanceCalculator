#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#define maxItem 10
#define minItem 1


int main(void) {
	printf("+--------------------------+\n");
	printf("+   Wish List Forecaster   |\n");
	printf("+--------------------------+\n");

	double netIncome, totalCost = 0; // User's monthly income and total cost
	const double minIncome = 500.00, maxIncome = 400000.00, minCost = 100.00; // Constants
	int items, menuSelection, financeCount, years, months, priorityFilter;
	int keepgoing, i; // loops

	double costValue[10]; //arrays
	int priorityValue[10];
	char financeOption[10];

	do // Getting User's input for Monthly Income
	{
		keepgoing = 1;
		printf("\nEnter your monthly NET income: $");
		scanf("%lf", &netIncome);


		if (netIncome < minIncome) // error range
		{
			printf("ERROR: You must have a consistent monthly income of at least $500.00\n");
			keepgoing = 0;
		}

		if (netIncome > maxIncome)
		{
			printf("ERROR: Liar! I'll believe you if you enter a value no more than $400000.00\n");
			keepgoing = 0;
		}


	} while (keepgoing != 1);

	do // Validating User's input for number of wish list items with appropriate error message that will repreat until valid input is given
	{
		keepgoing = 1;
		printf("\nHow many wish list items do you want to forecast?: ");
		scanf("%d", &items);

		if (items < minItem || items > maxItem) // error range for number of wish list items
		{
			printf("ERROR: List is restricted to between 1 and 10 items.\n");
			keepgoing = 0;
		}

	} while (keepgoing != 1);

	for (i = 0; i < items; i++) // loop for 3 related pieces that was stored in parallel arrays
	{
		printf("\nItem-%d Details:\n", i + 1);

		do // Validating User's input for item cost with appropriate error message that will repeat until valid input is given
		{
			keepgoing = 1;
			printf("   Item cost: $");
			scanf("%lf", &costValue[i]);
			if (costValue[i] < minCost)
			{
				printf("      ERROR: Cost must be at least $100.00\n");
				keepgoing = 0;
			}


		} while (keepgoing != 1);

		do // Validating User's input for item priority with appropriate error message that will repeat until valid input is given
		{
			keepgoing = 1;
			printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
			scanf("%d", &priorityValue[i]);
			if (priorityValue[i] < 1 || priorityValue[i] > 3)
			{
				printf("      ERROR: Value must be between 1 and 3\n");
				keepgoing = 0;
			}

		} while (keepgoing != 1);

		do // Validating User's input for fiancing options with appropriate error message that will repeat until valid input is given
		{
			keepgoing = 1;
			printf("   Does this item have financing options? [y/n]: ");
			scanf(" %c", &financeOption[i]);
			if (financeOption[i] != 'y' && financeOption[i] != 'n')
			{
				printf("      ERROR: Must be a lowercase 'y' or 'n'\n");
				keepgoing = 0;
			}

		} while (keepgoing != 1);



	}
	printf("\nItem Priority Financed        Cost\n"); // Display for formatted table
	printf("---- -------- -------- -----------\n");
	for (i = 0; i < items; i++)
	{
		printf("%3d  %5d    %5c    %11.2lf\n", i + 1, priorityValue[i], financeOption[i], costValue[i]);
		totalCost += costValue[i];
	}

	printf("---- -------- -------- -----------\n");
	printf("                      $%11.2lf\n\n", totalCost);
	do // Item Details
	{	
		do
		{
			keepgoing = 1;
			printf("How do you want to forecast your wish list?\n 1. All items (no filter)\n 2. By priority\n 0. Quit/Exit\n"); // Menu Selection
			printf("Selection: ");
			scanf("%d", &menuSelection);

			if (menuSelection < 0 || menuSelection > 2) // Error to occur
			{
				printf("\nERROR: Invalid menu selection.\n\n");
				keepgoing = 0;
			}

		} while (keepgoing != 1);

		switch (menuSelection) // Options that was selected
		{
			case 1: // If User selected option  1
				financeCount = 0;
				totalCost = 0;
				for ( i = 0; i < items; i++)
				{
					totalCost += costValue[i];
					if (financeOption[i] == 'y');
					financeCount++;
				}
				printf("\n====================================================");
				printf("\nFilter:   All items\n");
				printf("Amount:   $%1.2lf\n", totalCost);

				years = (int)totalCost / (((int)netIncome)* 12);
				months = ((int)(totalCost / netIncome + 0.5)) % 12;

				printf("Forecast: %d years, %d months", years, months);
				if (financeCount > 0)
				{
					printf("\nNOTE: Financing options are available on some items.\n      You can likely reduce the estimated months.");
				}
				printf("\n====================================================\n\n");
				break;

			case 2: // If User selected option 2
				financeCount = 0;
				totalCost = 0;

				do // Appropriate Error Message for incorrect input
				{
					keepgoing = 1;
					printf("\nWhat priority do you want to filter by? [1-3]: ");
					scanf("%d", &priorityFilter);
					if (priorityFilter < 1 || priorityFilter > 3)
					{
						printf(" ERROR: Value must be between 1 and 3");
						keepgoing = 0;
					}
				} while (keepgoing != 1);

				for (i = 0; i < items; i++) // Calculation for total cost of the items and finance options
				{
					if (priorityValue[i] == priorityFilter)
					{
						if (financeOption[i] == 'y')						
						financeCount++;
						totalCost += costValue[i];
						
					}

				}
				printf("\n====================================================\n"); 
				printf("Filter:   by priority (%d)\n", priorityFilter); // Display for Filter
				printf("Amount:   $%1.2lf\n", totalCost);
				years = (int)totalCost / (((int)netIncome) * 12); //Calculation for Year
				months = ((int)(totalCost / netIncome + 1)) % 12;
				printf("Forecast: %d years, %d months\n", years, months);

				if (financeCount > 0)
				{
					printf("NOTE: Financing options are available on some items.\n      You can likely reduce the estimated months.\n");
				}
				printf("====================================================\n\n");
			break;
		}
	} while (menuSelection != 0);

	printf("\nBest of luck in all your future endeavours!"); 
	
	return 0;
}

