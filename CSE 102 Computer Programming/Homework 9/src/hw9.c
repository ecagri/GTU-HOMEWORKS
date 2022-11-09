#include <stdio.h>

typedef struct customer{
	char name[10];	
	int age;
	int label;
}customer;

#define rows 4

#define coloumns 15

void rowofcustomer(customer customers[rows][coloumns],customer add); /* Finds customer's row in sequence. */

void coloumnofcustomer(customer customers[rows][coloumns], customer add, int vertical); /* Finds customer's coloumn in sequence. */

void move(customer customers[coloumns], customer new, int horizontal); /* Moves new customer to the where it belongs. */

void process(customer customers[rows][coloumns]); /* Makes process step. */

void printcurrent(customer customers[rows][coloumns]); /* Prints current customers. */

/*---------------------------------------------------------------------*/

int main(){
	customer customers[rows][coloumns]; /* Customers in bank. */

	customer add; /* New customer to add. */

	int option;

	int counter = 0; /* Customer counter. */

	int i, j;

	for(i=0;i<rows;i++){ /* This blocks sets labels of all customers to -1. */

		for(j=0;j<coloumns;j++){

			customers[i][j].label = -1; 
		}
	}

	printf("***********BANKING SYSTEM***********\n");

	while(1){ /* This blocks continues until the user wants to quit. */

		printf("1-ADD COSTUMER\n");

		printf("2-PROCESS CUSTOMER\n");

		printf("0-QUİT\n");

		while(1){ /* This blocks continues until the user enters valid option. */
			scanf("%d",&option);

			if(0<=option && option<=2) break;
	
			else printf("Enter valid operation: ");
		}

		if(option == 1 && counter<50){ /* If user wants to add new costumer continues. */
			printf("Please enter the name of the customer: ");

			scanf("%s",add.name);

			printf("Please enter the age of the customer: ");

			scanf("%d",&add.age);

			printf("Please enter the label of the customer: ");

			while(1){ /* This blocks continues until the users enters valid label. */
				scanf("%d",&add.label);

				if(0<=add.label && add.label<=4) break;

				else printf("Enter valid label: ");
			}

			rowofcustomer(customers, add); /* Calls wheremustbe function. */

			counter++; /* Increases counter by one. */
		} 
		else if(option == 1 && counter>=50){ /* If user wants to add new costumer but bank is full, prints an error message. */
			printf("You cannot add new customers. Bank is full.\n");
		}
		
		else if(option == 2){ /* If user wants to process, continues. */
			process(customers); /* Calls process function. */

			counter--; /* Decreases counter by one. */
		}

		if(option == 0) break; /* If user wants to quit, ends the program. */

		printcurrent(customers); /* Calls printcurrent function. */

		printf("\n");
	}

	return 0;
}

/*---------------------------------------------------------------------*/

void rowofcustomer(customer customers[rows][coloumns], customer new){  
	int vertical, horizontal;

	int limit;

	int times;

	switch(new.label){
		case 0:
			limit = 5; /* If new customer's albel is 0, the limit is 5. */
			break;
		case 1: 
			limit = 3; /* If new customer's albel is 1, the limit is 3. */
			break;
		case 2: 
			limit = 3; /* If new customer's albel is 2, the limit is 3. */
			break;
		case 3: 
			limit = 2; /* If new customer's albel is 3, the limit is 2. */
			break;
		case 4: 
			limit = 2; /* If new customer's albel is 4, the limit is 2. */
			break;
	}

	for(vertical=0;vertical<rows;vertical++){

		times = 0;

		for(horizontal=0;horizontal<coloumns;horizontal++){ /* Calculates number of new customer's label in each row. */
			if(customers[vertical][horizontal].label == new.label) times++;
		}

		if(times<limit) break; /* If number of new customer's label in i. row is less than limit, break the loop. */
	}

	if(vertical>3){
		printf("The limit is full for this label.\n");
	}
	else{
		coloumnofcustomer(customers, new, vertical); /* Calls slide function. */
	}

}

/*---------------------------------------------------------------------*/

void coloumnofcustomer(customer customers[rows][coloumns], customer new, int vertical){
	int i;

	int horizontal = -1;

	for(i=0;i<coloumns;i++){ /* Search the row, if it finds a label which is greater than new customer's label, breaks the loop. */
		if(customers[vertical][i].label > new.label){ 

			horizontal = i;

			break;
		}
	}

	if(horizontal == -1){ /* If the first cannot find any horizontal coordinate, continues. */
		for(i=0;i<coloumns;i++){ /* Search the row, if it finds a empty place, breaks the loop. */
			if(customers[vertical][i].label == -1){

				horizontal = i;

				break;
			}
		}
	}
	
	move(customers[vertical], new, horizontal); /* Calls move function. */

}

/*---------------------------------------------------------------------*/

void move(customer customers[coloumns], customer new, int horizontal){ /* Puts new customer in sequence and slides the rest of the sequence. */
 
	customer temp; /* Creates a temp variable. */

	for(;horizontal<coloumns;horizontal++){ /* It works from new customer's coloumn to the end of the coloumn. */
		
		temp = customers[horizontal];
		
		customers[horizontal] = new;
		
		new = temp;

	}
}

/*---------------------------------------------------------------------*/

void printcurrent(customer customers[rows][coloumns]){ /* Prints current sequence. */
	int i, j;

	int isfirst = 0;

	for(i=0;i<rows;i++){

		for(j=0;j<coloumns;j++){

			if(customers[i][j].label != -1){ /* If label of customers[i][j] is -1 (empty), do not print. */
				isfirst++;
				if(isfirst != 1) printf("-"); /* If the label is not first element of the sequence print '-' .*/

				printf("%d",customers[i][j].label);
			}

		}
	}
}

void process(customer customers[rows][coloumns]){

	int i, j;

	int flag = 0;

	for(j=0;j<coloumns;j++){ /* Controls the first line is over or not. */
		if(customers[0][j].label != -1) flag = 1;
	}

	if(flag==0){ /* If the first line is over, slide other lines up. */
		for(i=0;i<3;i++){
			for(j=0;j<coloumns;j++){
				customers[i][j] = customers[i+1][j];
			}
		}

		for(j=0;j<coloumns;j++){ /* Makes the last line empty. */
				customers[3][j].label = -1;
		}
	}

	if(customers[0][0].label == -1){ /* If it cannot find a customer, prints an error. */
		printf("There is not any customer in bank system sequence. \n");
	}
	else{ /* Otherwise prints the customer, and delete the customer from the sequence. */
		printf("Proceed customer is: %s\n",customers[0][0].name); 

		for(j=0;j<coloumns-1;j++){ /* After the process the customer, slide other coloumns left. */
			customers[0][j] =  customers[0][j+1];
		}

		customers[0][coloumns-1].label = -1; /* Makes the last coloumns of the line empty. */
	}

}
