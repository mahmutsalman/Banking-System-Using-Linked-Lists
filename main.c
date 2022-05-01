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

void readOperationTypes(struct operation_type *headOpType, char *inputFile) {
    FILE *fPtr;
    char fileNamex[100];
    strcpy(fileNamex, "C:\\Users\\asxdc\\CLionProjects\\DataProject-1\\");

    strcat(fileNamex, inputFile);
    fPtr = fopen(fileNamex, "r");
    if (fPtr == NULL) {
        printf("There is a error opening the file.");

    }
    char entity[20];
    float entity2;

    int iterator = 0;// For adding to head
    int optnum=1;

    while (fscanf(fPtr, "%s%f", &entity, &entity2) != EOF) {
        struct operation_type *new_branch = malloc(sizeof(struct operation_type));
        new_branch->nextopt = NULL;
        memcpy(new_branch->optname, entity, sizeof(entity));
        new_branch->commission = entity2;

        if (iterator == 0) {
            headOpType->nextopt = NULL;
            memcpy(headOpType->optname, entity, sizeof(entity));
            headOpType->commission = entity2;
            headOpType->optnum=optnum;
            iterator++;
        } else {
            struct operation_type *lastNode = headOpType;
            while (lastNode->nextopt != NULL) {
                lastNode = lastNode->nextopt;
            }
            lastNode->nextopt = new_branch;
            lastNode->optnum=optnum;
            optnum++;
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

    int bno = 1;
    //Create branch
    char entity[20];

    int iterator=0;

    while (fscanf(fPtr, "%s", &entity) != EOF) {
        //If head is empty, add new branch into it
        if(iterator==0){
            bank->branches= malloc(sizeof (struct branch));//Buna gerek olmayabilir,main içersinde zaten bu yapılıyor
            bank->branches->nextb=NULL;
            memcpy(bank->branches->bname, entity, sizeof(entity));
            bank->branches->bno = bno;
            bank->branches->custs = NULL;
            bno++;
            iterator++;

        }
        else{
            struct branch *new_branch = malloc(sizeof(struct branch));
            new_branch->nextb = NULL;
            memcpy(new_branch->bname, entity, sizeof(entity));
            new_branch->bno = bno;
            new_branch->custs= malloc(sizeof (struct customer));
            new_branch->custs->nextc=NULL;
            bno++;

            struct branch *lastNode = bank->branches;

            while(lastNode->nextb!=NULL){
                lastNode=lastNode->nextb;
            }
            lastNode->nextb=new_branch;

        }


    }
}
struct branch  *getProperBranch(struct bank *banka,int entity){
    for(struct branch *bp = banka->branches; bp; bp = bp->nextb){
        if(bp->bno==entity){
            return bp;
        }

    }
    return NULL;

}
struct customer *getProperCustomer(struct branch *brancha,int customerId){
    for(struct customer *cs = brancha->custs; cs;cs=cs->nextc){
        if(cs->cno==customerId){
            return cs;
        }
    }
    return NULL;
}

void readCustomers(char *inputFile,struct bank* bank) {
    FILE *fPtr;
    char fileNamex[100];
    strcpy(fileNamex, "C:\\Users\\asxdc\\CLionProjects\\DataProject-1\\");

    strcat(fileNamex, inputFile);
    fPtr = fopen(fileNamex, "r");
    if (fPtr == NULL) {
        printf("There is a error opening the file.");

    }
    int entity;
    char entity2[20];
    char entity3[20];
    int customerNo=1;

    while (fscanf(fPtr, "%d %s %s", &entity, &entity2, &entity3) != EOF) {

        // entity ile  ikinci branche gidicem,o branch bank head'in içinde
        struct bank* banka = malloc(sizeof(struct bank)); // malloc olmasa ne olur burada
        banka=bank;
        // Find proper branch
        struct branch *properBranch;
        properBranch=getProperBranch(banka,entity);


        struct customer *new_customer= malloc(sizeof (struct customer));
        memcpy(new_customer->fname, entity2, sizeof(entity2));
        memcpy(new_customer->lname, entity3, sizeof(entity3));
        new_customer->cno=customerNo;
        customerNo++;
        new_customer->nextc=NULL;

        if(properBranch->custs==NULL){ //NEREDE SET LENIYOR BU,BRANCH YARATILIRKEN MI
            properBranch->custs=new_customer;
        }
        else{
            // For the first customer? how to add first customer
            //last node's next address will be NULL.
            while(properBranch->custs->nextc!=NULL){
                properBranch->custs = properBranch->custs->nextc;
            }
            properBranch->custs->nextc=new_customer;
        }

    }

}

void readTransactions(char *inputFile,struct bank *banka){
    FILE *fPtr;
    char fileNamex[100];
    strcpy(fileNamex, "C:\\Users\\asxdc\\CLionProjects\\DataProject-1\\");

    strcat(fileNamex, inputFile);
    fPtr = fopen(fileNamex, "r");
    if (fPtr == NULL) {
        printf("There is a error opening the file.");

    }
    int entity; //Branch number
    int entity2; // Customer id(cid)
    int entity3; //Operation type
    float entity4; //transaciton-> amount
    int tno=1;

    struct customer *temp_customer;

    while (fscanf(fPtr, "%d %d %d %f", &entity, &entity2, &entity3,&entity4) != EOF) {

        //get proper branch
        struct branch *properBranch = getProperBranch(banka,entity);

        //get proper customer
        struct customer *properCustomer = getProperCustomer(properBranch,entity2);
        temp_customer=properCustomer;
        //Add new transaction to proper place in the customer
        //If it is first transaction
        if(properCustomer->trans==NULL){
            properCustomer->trans= malloc(sizeof (struct transaction));
            properCustomer->trans->nexttr=NULL;
            properCustomer->trans->amount=entity4;
            properCustomer->trans->optype=entity3;
            tno++;
        }
        else{
            // Create a new transaction
            struct transaction *new_transaction= malloc(sizeof(struct transaction) );
            new_transaction->amount=entity4; // Amount
            new_transaction->optype=entity3; // Opetaion type
            new_transaction->tno=tno;
            tno++;

            //Find last transaction
            while(temp_customer->trans->nexttr!=NULL){
                temp_customer->trans=temp_customer->trans->nexttr;
            }
            //Got last transaction
            temp_customer->trans=new_transaction;


        }




    }


}

/* Print all the elements in the linked list */
void printOpType(struct operation_type *head) {
    struct operation_type *current_node = head;
    while (current_node != NULL) {
        setbuf(stdout, 0);
        printf("%s ", current_node->optname);
        printf("%f\n ", current_node->commission);


        current_node = current_node->nextopt;
    }
}

void printBranches(struct bank *head) {
    struct branch *current_node = head->branches;
    while (current_node != NULL) {
        printf("%s ", current_node->bname);

        current_node = current_node->nextb;
    }
}




int main() {

    struct operation_type *headOp= malloc(sizeof (struct operation_type));
    headOp->nextopt=NULL;
    struct bank *headB = malloc(sizeof(struct bank));

    headB->branches = malloc(sizeof(struct branch));
    headB->branches->nextb=NULL;

    int indexX = 0;
    while (indexX < 10) {
        printf("%s", "\n");
        printf("%s", "1)Read operations types from the file\n");
        printf("%s", "2)Read branches from the file\n");
        printf("%s", "3)Read customers from the file\n");
        printf("%s", "4)Read customer transactions from the file\n");
        printf("%s", "5)Calculate paid commission amount of each customers in each branches\n");

        int option;
        scanf("%d", &option);

        // For operation types
        if (option == 1) {


            printf("%s", "Please enter the name of the file :");
            char filenameOpTypes[20];
            scanf("%s", filenameOpTypes);

            readOperationTypes(headOp, filenameOpTypes);
            // Print all operation types which is in headOp
            printOpType(headOp);
            headB->optypes=headOp;

        }
        // For bank, creating branches
        else if (option == 2) {
            printf("%s", "Please enter the name of the file :");
            char filenameBank[20];
            scanf("%s", filenameBank);
            readBranches(headB, filenameBank);
            printBranches(headB);


        } else if (option == 3) {
            printf("%s", "Please enter the name of the file :");
            char filenameBank2[20];
            scanf("%s", filenameBank2);
            readCustomers(filenameBank2,headB);

        } else if(option==4) {
            printf("%s", "Please enter the name of the file :");
            char filenameBank2[20];
            scanf("%s", filenameBank2);
            readTransactions(filenameBank2,headB);


        }
        //option 5
        else{

        }


    }


}
