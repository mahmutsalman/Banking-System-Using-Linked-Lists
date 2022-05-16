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
    //Take first branch
    struct branch *brancha;

    while (fscanf(fPtr, "%s", &entity) != EOF) {
        brancha=bank->branches;

        if(bank->branches==NULL){
            bank->branches=malloc(sizeof (struct branch));
            memcpy(bank->branches->bname, entity, sizeof(entity));
            bank->branches->nextb=NULL;
            bank->branches->custs=NULL;
            bank->branches->bno=bno;
            bno++;
        }
        else{
            struct branch *new_branch= malloc(sizeof (struct branch));
            memcpy(new_branch->bname, entity, sizeof(entity));
            new_branch->custs=NULL;// Do I need this?
            new_branch->nextb=NULL;
            new_branch->bno=bno;
            bno++;
            struct branch *lastNode=brancha;
            while(lastNode->nextb!=NULL){
                lastNode=lastNode->nextb;
            }
            lastNode->nextb =new_branch;
        }
    }
}

struct branch  *getProperBranch(struct bank *banka,int entity){
    struct branch *bp=banka->branches;
    for(; bp; bp = bp->nextb){
        if(bp->bno==entity){
            return bp;
        }

    }
    return NULL;

}
struct customer *getProperCustomer(struct branch *brancha,int customerId){
    struct customer *cs = brancha->custs;
    for(;cs;cs=cs->nextc){
        if(cs->cno==customerId){
            return cs;
        }
    }
    return NULL;
}

void fillCustomerId(struct branch *brancha){
    int customerID=1;
    struct customer *temp_customer=brancha->custs;

    while(temp_customer!=NULL){
        temp_customer->cno=customerID;
        customerID++;
        temp_customer=temp_customer->nextc;
    }
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
        struct bank* banka;
        banka=bank;
        // Find proper branch
        struct branch *properBranch;
        properBranch=getProperBranch(banka,entity);
        struct customer *customersHead = properBranch->custs;


        struct customer *new_customer= malloc(sizeof (struct customer));
        memcpy(new_customer->fname, entity2, sizeof(entity2));
        memcpy(new_customer->lname, entity3, sizeof(entity3));
        new_customer->nextc=NULL;
        new_customer->trans=NULL;

        //
        if(customersHead==NULL){ //NEREDE SET LENIYOR BU,BRANCH YAILIRKEN MI
            properBranch->custs= malloc(sizeof (struct customer));
            memcpy(properBranch->custs->fname, entity2, sizeof(entity2));
            memcpy(properBranch->custs->lname, entity3, sizeof(entity3));
            properBranch->custs->nextc=NULL;
            properBranch->custs->trans=NULL;
        }
        else{
            // For the first customer? how to add first customer
            //last node's next address will be NULL.
            while(customersHead->nextc!=NULL){
                customersHead = customersHead->nextc;
            }
            customersHead->nextc=new_customer;
        }
        properBranch= getProperBranch(banka,entity);
        fillCustomerId(properBranch);
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
    struct branch *properBranch;

    while (fscanf(fPtr, "%d %d %d %f", &entity, &entity2, &entity3,&entity4) != EOF) {

        //get proper branch
       properBranch = getProperBranch(banka,entity);
        fillCustomerId(properBranch);
        //get proper customer
        //entity2 holds customer id
        struct customer *properCustomer = getProperCustomer(properBranch,entity2);
        temp_customer=properCustomer;
        //Add new transaction to proper place in the customer
        //If it is first transaction
        if(temp_customer->trans==NULL){
            temp_customer->trans= malloc(sizeof (struct transaction));
            temp_customer->trans->nexttr=NULL;
            temp_customer->trans->amount=entity4;
            temp_customer->trans->optype=entity3;
            temp_customer->trans->tno=tno;
            tno++;
        }
        else{
            // Create a new transaction
            struct transaction *new_transaction= malloc(sizeof(struct transaction) );
            new_transaction->amount=entity4; // Amount
            new_transaction->optype=entity3; // Opetaion type
            new_transaction->tno=tno;
            new_transaction->nexttr=NULL;
            tno++;

            //Find last transaction
            struct transaction *temp_transaction=temp_customer->trans;
            while(temp_transaction->nexttr!=NULL){
                temp_transaction=temp_transaction->nexttr;
            }
            //Got last transaction,add new_transaction to the last transaction
            temp_transaction->nexttr=new_transaction;



        }

    }


}

/* Print all the elements in the linked list */
void printOpType(struct operation_type *head) {
    struct operation_type *current_node = head;
    while (current_node != NULL) {
        setbuf(stdout, 0);
        printf("%s ", current_node->optname);
        printf("%.1f \n ", current_node->commission);


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

void printCustomer(struct bank *banka){
    struct branch *temp_branch=banka->branches;
    struct customer *temp_customer;
    while(temp_branch!=NULL){
        printf("%s \n",temp_branch->bname);
        temp_customer=temp_branch->custs;
        while(temp_customer!=NULL){
            printf("%d %s %s\n ",temp_customer->cno,temp_customer->fname,temp_customer->lname);
            temp_customer=temp_customer->nextc;
        }
        // After printing all the customers, go to next branch
        temp_branch=temp_branch->nextb;
    }
}
void printTransactions(struct bank *banka){
    struct branch *temp_branch=banka->branches;
    struct customer *temp_customer;
    struct transaction *temp_transaction;

    while(temp_branch!=NULL){
        printf("Branch: %d %s \n",temp_branch->bno,temp_branch->bname);
        temp_customer=temp_branch->custs;
        // Go through custs of temp_branch
        while(temp_customer!=NULL){
            //Print all the customer's id and name
            printf("--  %d %s",temp_customer->cno,temp_customer->fname);
            printf("\n");
            temp_transaction=temp_customer->trans;
            while(temp_transaction!=NULL){
                printf("--  ++tno %d operation type  %d amount %.2f \n",temp_transaction->tno,temp_transaction->optype,temp_transaction->amount);
                temp_transaction=temp_transaction->nexttr;
            }

           temp_customer=temp_customer->nextc;
        }
        // If there is no customer go to the next branch
        temp_branch=temp_branch->nextb;
    }

}
//Loop through headOp and find proper op type's commissonRate using temp_transaction->optype
int getcommissionRate(struct operation_type *headOp,int opType){
    struct operation_type *operationType =headOp;
        while(operationType!=NULL){
            if(operationType->optnum==opType){
                return operationType->commission;
            }
            else{
                operationType=operationType->nextopt;
            }
        }
}
float getPaidCommisson(struct transaction *transaction,float commissionRate){
        return transaction->amount*commissionRate;
}
struct operation_type *getOperationType(struct operation_type *headOp,int opType){
    //Loop through headOp and find proper operation type with given opType value
    struct operation_type *temp_operation_type=headOp;
    while(temp_operation_type!=NULL){
        if(temp_operation_type->optnum==opType){
            return temp_operation_type;
        }
        else{
            temp_operation_type=temp_operation_type->nextopt;
        }
    }
}


int main() {

    struct operation_type *headOp= malloc(sizeof (struct operation_type));
    headOp->nextopt=NULL;
    struct bank *headB = malloc(sizeof(struct bank));
    headB->branches= NULL;


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
        // Create branches
        else if (option == 2) {
            printf("%s", "Please enter the name of the file :");
            char filenameBank[20];
            scanf("%s", filenameBank);
            readBranches(headB, filenameBank);
            printBranches(headB);


        }
        // Fill customers into branches
        else if (option == 3) {
            printf("%s", "Please enter the name of the file :");
            char filenameBank2[20];
            scanf("%s", filenameBank2);
            readCustomers(filenameBank2,headB);
            printCustomer(headB);

        } else if(option==4) {
            printf("%s", "Please enter the name of the file :");
            char filenameBank2[20];
            scanf("%s", filenameBank2);

            readTransactions(filenameBank2,headB);
            printTransactions(headB);
        }
        //option 5
        else{
        // Go through each branch
        // For each customer
        // For each transaction
        // Print its details
        struct branch *temp_branch=headB->branches;

        float totalCommission=0;
            while(temp_branch!=NULL){
                struct customer *temp_customer=temp_branch->custs;
                struct transaction *temp_transaction=temp_customer->trans;
                printf("Branch: %s\n",temp_branch->bname);
                while(temp_customer!=NULL){
                    printf("--> Customer id %d : %s \n",temp_customer->cno,temp_customer->fname);
                    while (temp_transaction!=NULL){
                        //WAHERE IS THE COMMISSION RATE? HEADOP
                        //Loop through headOp and find proper op type's commissonRate using temp_transaction->optype
                       struct operation_type *temp_opType=getOperationType(headOp,temp_transaction->optype);
                       //Get operation type's commission
                        float comissionRate= temp_opType->commission;
                        //Get
                        float paidCommission=getPaidCommisson(temp_transaction,comissionRate);
                        totalCommission+=paidCommission;
                        printf("-- tno %d optype %d commission rate %%0.2f amount %.2f paid commission %.2f total commission %.2f   \n",temp_transaction->tno,temp_transaction->optype,comissionRate,temp_transaction->amount,paidCommission,totalCommission);
                        temp_transaction=temp_transaction->nexttr;

                    }
                    // If there is no transaction, print that
                    if(temp_customer->trans==NULL){
                        printf("customer has no transaction \n");
                    }
                    else{
                        printf("paid commission  %.2f \n",totalCommission);
                    }
                    totalCommission=0;
                    temp_customer=temp_customer->nextc;
                }
                temp_branch=temp_branch->nextb;
            }
        }
    }
}
