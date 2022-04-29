#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct operation_type {
    char optname[100];
    float commission; //indicates how much the bank charges for the operation
    int optnum; // for the id of the operation type
    struct operation_type *nextopt;

};

struct transaction {
    int optype; //to specify the type of transaction performed
    int tno; //indicates the id of transaction made by the customer
    float amount; //to hold the amount of money in the transaction
    struct transaction *nexttr; //to point to the next transaction information of the customer

};

struct customer {
    char fname[100];
    char lname[100];
    int cno; //for the customer's id information
    float paid_commission; // to keep the total commission paid by the customer for the transactions
    struct transaction *trans; // to keep the transactions made by the customer
    struct customer *nextc; //  to point to the next customer in the same branch of the bank

};


struct branch {
    char bname[100];
    int bno; // branch id
    struct customer *custs; // to hold the customer information of this branch
    struct branch *nextb; //to point to the next branch of the bank
};

struct bank {
    struct branch *branches; //to hold the branches of the bank
    struct operation_type *optypes;// to hold the transaction types offered by the bank
};

void readOperationTypes(struct operation_type *operationType, char *inputFile) {

    FILE *fPtr;
    char fileNamex[100];
    strcpy(fileNamex, "C:\\Users\\asxdc\\CLionProjects\\DataProject-1\\");

    strcat(fileNamex, inputFile);
    fPtr = fopen(fileNamex, "r");
    if (fPtr == NULL) {
        printf("There is a error opening the file.");

    }

    char entity[20];
    int iterator = 0;

    while (fscanf(fPtr, "%s", &entity) != EOF) {
        // Add this to linked list
        if (iterator % 2 == 0) {
            memcpy(operationType->optname, entity, sizeof(entity));
            iterator++;

        } else {
            operationType->commission = atof(entity);
            iterator++;
            // Go to next operation_type nextopt;
            operationType->nextopt = malloc(sizeof(struct operation_type));
            operationType = operationType->nextopt;

        }


    }


}

void readBranches(struct bank *bank, char *inputFile) {
    FILE *fPtr;
    char fileNamex[100];
    strcpy(fileNamex, "C:\\Users\\asxdc\\CLionProjects\\DataProject-1\\");

    strcat(fileNamex, inputFile);
    fPtr = fopen(fileNamex, "r");
    if (fPtr == NULL) {
        printf("There is a error opening the file.");

    }

    int index = 1;
    int bno=1;
    //Create branch
    struct branch *new_branch = malloc(sizeof(struct branch));

    char entity[20];
    while (fscanf(fPtr, "%s", &entity) != EOF) {
        // Add this to linked list
        //First create space for new branch on memory

        if (index == 1) {
            memcpy(new_branch->bname, entity, sizeof(entity));
            new_branch->bno=bno;
            bno++;
            bank->branches = new_branch;
            new_branch->nextb = malloc(sizeof(struct branch));
            //Go next branch

            new_branch = new_branch->nextb;
            index++;

        } else {
            memcpy(new_branch->bname, entity, sizeof(entity));
            new_branch->bno=bno;
            bno++;
            // Go next branch
            new_branch->nextb = malloc(sizeof(struct branch));

            new_branch = new_branch->nextb;

        }


    }
}
void readCustomers(char *inputFile){
    FILE *fPtr;
    char fileNamex[100];
    strcpy(fileNamex, "C:\\Users\\asxdc\\CLionProjects\\DataProject-1\\");

    strcat(fileNamex, inputFile);
    fPtr = fopen(fileNamex, "r");
    if (fPtr == NULL) {
        printf("There is a error opening the file.");

    }
    char entity[20];
    char entity2[20];
    char entity3[20];

    int iterator=0;
    while (fscanf(fPtr, "%s %s %s", &entity,&entity2,&entity3) != EOF) {

        // entity ile 2 ikinci branche gidicem

        printf("%d",1);
    }

}

/* Print all the elements in the linked list */
void printOpType(struct operation_type *head) {
    struct operation_type *current_node = head;
    while (current_node->nextopt->nextopt != NULL) {
        printf("%s ", current_node->optname);
        printf("%f\n ", current_node->commission);

        current_node = current_node->nextopt;
    }
}

void printBranches(struct bank *head) {
    struct branch *current_node = head->branches;
    while (current_node->nextb->nextb != NULL) {
        printf("%s ", current_node->bname);

        current_node = current_node->nextb;
    }
}



int main() {

    struct operation_type *headOp = malloc(sizeof(struct operation_type));
    struct bank *headB = malloc(sizeof(struct bank));

    while(1){
        printf("%s", "1)Read operations types from the file\n");
        printf("%s", "2)Read branches from the file\n");
        printf("%s", "3)Read customers from the file\n");
        printf("%s", "4)Read customer transactions from the file\n");
        printf("%s", "5)Calculate paid commission amount of each customers in each branches\n");

        int option;
        scanf("%d", &option);

        if(option==1){
            setbuf(stdout, 0);

            printf("%s", "Please enter the name of the file :");
            char filenameOpTypes[20];
            scanf("%s", filenameOpTypes);

            readOperationTypes(headOp, filenameOpTypes);
            // Print all operation types which is in headOp
            printOpType(headOp);
        }

        else if(option==2){
            printf("%s", "Please enter the name of the file :");
            char filenameBank[20];
            scanf("%s", filenameBank);
            readBranches(headB, filenameBank);
            printBranches(headB);

        }
        else if(option==3){
            printf("%s", "Please enter the name of the file :");
            char filenameBank2[20];
            scanf("%s", filenameBank2);
            readCustomers(filenameBank2);
        }
        else{

        }

    }















}
