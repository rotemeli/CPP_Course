#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTStack.h"

#define     MAX_LENGTH      16

typedef struct intl_passenger* intl_passenger;

struct intl_passenger {
    char given_name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    char passport_id[MAX_LENGTH];
    char country[MAX_LENGTH];
};

intl_passenger passengerCreate() {
    intl_passenger pass = malloc(sizeof(struct intl_passenger));
    if(!pass) {
        fprintf(stderr, "%s, %d: Failed to allocate memory\n", \
        __FILE__, __LINE__);
        exit(-1);
    }
    return pass;
}

void destroyPassenger(intl_passenger p) {
    free(p);
}

char* label_elm(intl_passenger p) {
    if (!p) {
        return NULL;
    }

    char *s = malloc((16 * 4) + 4);
    if(!s) {
        fprintf(stderr, "%s/%u: failed to allocated %lu bytes, aborting\n", __FILE__, __LINE__, sizeof(double));
        exit(-1);
    }

    strcat(s, p->given_name);
    strcat(s, " ");
    strcat(s, p->surname);
    strcat(s, " ");
    strcat(s, p->passport_id);
    strcat(s, " ");
    strcat(s, p->country);
    return s;
}

int main() {
    Stack s = init(100, (void *(*)(void *)) strcpy, free, (char *(*)(void *)) label_elm);

    char* buf = NULL;
    size_t bufSize = 0;

    FILE *fin = fopen("international_passengers.dat", "r");
    if (fin == NULL) {
        fprintf(stderr, "%s/%u: failed to open the file, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }

    char temp[MAX_LENGTH];
    int j = 0;
    int k = 0;

    while(getline(&buf, &bufSize, fin) != EOF) {
        intl_passenger newPass = passengerCreate();
        for(int i=0; i < strlen(buf); i++) {
            temp[j] = buf[i];
            j++;
            if(buf[i] == ' ' || buf[i] == '\n') {
                temp[j-1] = '\0';
                j=0;
                if(k==0) {
                    strcpy(newPass->given_name, temp);
                }
                else if(k==1) {
                    strcpy(newPass->surname, temp);
                }
                else if(k==2) {
                    strcpy(newPass->passport_id, temp);
                }
                else if(k==3) {
                    strcpy(newPass->country, temp);
                }
                k++;
            }
            if(k==4) {
                k=0;
                break;
            }
        }
        push(s, newPass);
    }
    temp[j] = '\0';
    intl_passenger p0 = pop(s);
    strcpy(p0->country, temp);
    push(s, p0);                    // fix last element country field

    free(buf);
    fclose(fin);

    intl_passenger pPrint;
    pPrint = pop(s);
    while(size(s) != 0) {
        printf("%s %s %s\n", pPrint->given_name, pPrint->surname, pPrint->passport_id);
        pPrint = pop(s);
    }
    printf("%s %s %s\n", pPrint->given_name, pPrint->surname, pPrint->passport_id);

    destroyPassenger(p0);
    destroyPassenger(pPrint);
    destroy(s);
    return 0;
}