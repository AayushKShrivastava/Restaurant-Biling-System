#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// function to generate bills

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

void generateBillHeader(char name[50], char date[30]){
    printf("\n\n");
    printf("\t   My Restaurant");
    printf("\n\t   -----------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n\n");
    printf("-----------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n----------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price){
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty*price);
    printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total-dis;
    float cgst = 0.09*netTotal, grandTotal = netTotal + 2*cgst;
    printf("------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%", dis);
    printf("\n\t\t\t\t---------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%", cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n---------------------------------------\n");
}

int main(){
    float total;
    int opt, invoices;
    struct orders ord, order;
    char saveBill = 'y', name[50];
    char contOperation = 'y';
    
    FILE *fp;
    while(contOperation == 'y') {
        printf("\t==============My Restaurant===============");
        printf("\n\nPlease select your preferred operation:\t");
        printf("\n\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoice");
        printf("\n4.Exit");

        printf("\n\nYour choice:\t");

        scanf("%d", &opt);

        fgetc(stdin);
        switch(opt){
            case 1:
            total = 0;
            
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.customer,50,stdin);
            ord.customer[strlen(ord.customer)-1]= 0;
            strcpy(ord.date,__DATE__);
            printf("\nPlease enter the number of items:\t");
            scanf("%d", &ord.numOfItems);

            for(int i = 0; i < ord.numOfItems; i++){
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d:\t",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
                printf("Please enter the quantity:\t");
                scanf("%d",&ord.itm[i].qty);
                printf("Please enter the unit price: \t");
                scanf("%f",&ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }

            generateBillHeader(ord.customer, ord.date);

            for(int i = 0; i < ord.numOfItems; i++){
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }

            generateBillFooter(total);
            
            printf("\nDo you want to save the invoice [y/n]:\t");

            scanf("%s", &saveBill);
            if(saveBill == 'y'){
                fp = fopen("RestaurantBill.dat","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fwrite != 0)
                    printf("\nSaved Successfully");
                else
                    printf("\nError Saving");
                fclose(fp);
                
            }
            fgetc(stdin);
            break;

            case 2:
            
            fp = fopen("RestaurantBill.dat", "r");
            printf("\n *****Your Previous Invoices*****");
            while(fread(&order,sizeof(struct orders),1,fp)){
                total = 0;
                generateBillHeader(order.customer, order.date);

                for(int i = 0; i < order.numOfItems; i++){
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    total += order.itm[i].qty * order.itm[i].price;
                }

                generateBillFooter(total);

            }
            fclose(fp);
            break;

            case 3:
            invoices = 0;
            printf("Enter the name of the customer:\t");
            fgets(name,50,stdin);
            name[strlen(name)-1] = 0;
            
            fp = fopen("RestaurantBill.dat", "r");
            printf("\n *****Your Previous Invoices*****");
            while(fread(&order,sizeof(struct orders),1,fp)){
                if(strcmp(name,order.customer)) continue;
                total = 0;
                generateBillHeader(order.customer, order.date);

                for(int i = 0; i < order.numOfItems; i++){
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    total += order.itm[i].qty * order.itm[i].price;
                }
                
                generateBillFooter(total);
                invoices = 1;

            }
            if(!invoices) 
                printf("\n\nThere is no invoice for the customer named %s", name);
            fclose(fp);
            break;

            case 4:
            printf("\n\t\t Bye Bye :) \n\n");
            exit(0);
            break;

            default:
            printf("Invalid input");
            break;
            
        }
        
        printf("\nDo you want to continue billing?[y/n]:\t");
        scanf("%c", &contOperation);
    }
    
    printf("\n\n");

    return 0;
}