#include <stdio.h>

struct operation_type{
    char optname[100];
    float commission; //indicates how much the bank charges for the operation
    int optnum; // for the id of the operation type
    struct operation_type* nextopt;

};

struct transaction{
    int optype; //to specify the type of transaction performed
    int tno; //indicates the id of transaction made by the customer
    float amount; //to hold the amount of money in the transaction
    struct transaction* nexttr; //to point to the next transaction information of the customer

};

struct customer{
    char fname[100];
    char lname[100];
    int cno; //for the customer's id information
    float paid_commission; // to keep the total commission paid by the customer for the transactions
    struct transaction* trans; // to keep the transactions made by the customer
    struct customer* nextc; //  to point to the next customer in the same branch of the bank



};

struct branch{
    char bname[100];
    int bno; // branch id
    struct customer* custs; // to hold the customer information of this branch
    struct branch* nextb; //to point to the next branch of the bank
};

struct bank{
    struct branch* branches; //to hold the branches of the bank
    struct operation_type* optypes;// to hold the transaction types offered by the bank
};

int main() {
    printf("1)Read operations types from the file\n");
    printf("2)Read branches from the file\n");
    printf("3)Read customers from the file\n");
    printf("4)Read customer transactions from the file\n");
    printf("5)Calculate paid commission amount of each customers in each branches\n");

    return 0;

}
