//
//  main.c
//  cpsc416-assignment2
//
//  Created by Evan Louie on 2/23/2014.
//  Copyright (c) 2014 Evan Louie. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

FILE * pFile;

typedef struct queue_operation {
    int operation;
    int value;
} operation_t;

typedef struct generator_state {
    int state[4];
} generator_state_t;

int load_generator(operation_t *op, generator_state_t **s) {
    if (*s == NULL) {
        *s = (generator_state_t *) malloc(sizeof(generator_state_t));
        // initialize state
    }
    
    return 1;
}

int main(int argc, const char * argv[])
{

    // insert code here...
    printf("%s\n", argv[1]);
    for (int i=0; i<=argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }
    
    
    pFile = fopen ("result.txt","w+");
    if (pFile!=NULL)
    {
        fputs ("fopen example EVAN LUIe\nasdfasdfasdf\n",pFile);
        fclose (pFile);
    }

    return 0;
}

