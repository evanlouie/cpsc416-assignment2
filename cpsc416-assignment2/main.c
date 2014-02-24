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


int main(int argc, const char * argv[])
{

    // insert code here...
    printf("%s\n", argv[1]);
    for (int i=0; i<=argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }
    
    FILE * pFile;
    pFile = fopen ("result.txt","w+");
    if (pFile!=NULL)
    {
        fputs ("fopen example asdf\n",pFile);
        fclose (pFile);
    }

    return 0;
}

