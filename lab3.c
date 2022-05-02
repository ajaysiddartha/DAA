/*
The Following code is used to find the shotest superstring for a given set of strings.

Input

1. The input (stdin) will consist of the following:
    a. A line with n (number of strings). n <= 100.
    b. n lines, each including a single string with no more than 50 symbols.
2. Before doing other processing, your program should verify that none of the input strings is a substring of any other input
string. If this condition is violated, an error message and termination should result. There is no loss of generality in
making this assumption, but it avoids a few tedious situations.

Output

Your output should print the strings, one per line, to make the overlaps comprising the superstring obvious.

1001001
 0010010
        110010
         100102

 or

110010
 1001001
  0010010
    100102

References:
1. https://ranger.uta.edu/~weems/NOTES5311/LAB/LAB3SPR22/lab3spr22.pdf
2. https://github.com/vli02/leetcode/blob/master/943.%20Find%20the%20Shortest%20Superstring.c
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int LengthofTail(const char *a, int la, const char *b, int lb) {
    int i = 0;
    int max = la < lb ? la - 1 : lb - 1;    // max overlap characters
    while (max && strncmp(&a[la - max], b, max)) {
        max --;
    }
    return lb - max;
}


int main()
{
    int r,z,ALength;
    scanf("%d", &ALength);
    char A[ALength][50];
	for(r=0; r< ALength ; r++) {
		scanf("%s",A[r]);
		if(strlen(A[r])>50)
		{
		    printf("String length greater than 50");
		    return 0;
		}
	}

//Comparing strings to find out if there are any substrings to each other
	for(r=0;r<ALength;r++)
	{
	    char *posFound=NULL;
	    for(z=0;z<ALength;z++)
	    {
	        if(r!=z)
	        {
	            posFound=strstr(A[r],A[z]);
	        }
	        //printf("%s",posFound);
	        if(posFound!=NULL)
	        {
	            printf("%s is a substring of %s, so terminating the process",A[z],A[r]);
	            return 0;
	        }
	        
	    }
	}

//Finding the shortest common superstring

    int *len, *addStr, *dp, *prev, *Order;
    int sz, i, j, p, k, l, sp;
    int min = 0, last;
    
    char *s, *t;
    
    len = malloc(ALength * sizeof(int));
    //assert(len);
    
    for (i = 0; i < ALength; i ++) {
        len[i] = strlen(A[i]);
    }
    
    addStr = calloc(ALength * ALength, sizeof(int));
    
#define IDX(I, J) ((I) * ALength + (J))
    
    for (i = 0; i < ALength; i ++) {
        for (j = i + 1; j < ALength; j ++) {
            // additional length of A[i] if combine it with A[j]
            addStr[IDX(i, j)] = LengthofTail(A[i], len[i], A[j], len[j]);
            addStr[IDX(j, i)] = LengthofTail(A[j], len[j], A[i], len[i]);
        }
    }
    
    sz = (1 << ALength);  // each bit of (sz - 1) identifies one string in A
    
    dp = calloc(sz * ALength, sizeof(int));
    prev = calloc(sz * ALength, sizeof(int));
    //assert(dp && path);
#define IDX2(I, J) ((I) * (ALength) + (J))
    
    for (i = 0; i < ALength; i ++) {
        dp[IDX2(1 << i, i)] = len[i];   // when there is no parent, the length is itself.
    }
    
    for (i = 1; i < sz; i ++) {         // current combination of strings being selected
        for (j = 0; j < ALength; j ++) {  // the one in the ends in above combination
            if (!(i & (1 << j))) continue;  // if A[j] is not in the above combination
            p = i & ~(1 << j);          // new combination excluding current string A[j]
            for (k = 0; k < ALength; k ++) {
                if (dp[IDX2(p, k)]) {   // if the length of the new combination with A[k] in the end is known
                    l = dp[IDX2(p, k)] + addStr[IDX(k, j)];
                    if (dp[IDX2(i, j)] == 0 ||
                        dp[IDX2(i, j)] > l) {
                        dp[IDX2(i, j)] = l;
                        prev[IDX2(i, j)] = k;   // A[j] is after A[k]
                    }
                }
            }
            if (i == sz - 1 &&              // all strings are selected
                (l = dp[IDX2(i, j)]) &&
                (min == 0 || min > l)) {    // and a minimal length is found
                min = l;
                last = j;                   // record the ending string A[j]
            }
        }
    }
    
    Order = malloc(ALength * sizeof(int));
    //assert(Order);
    sp = 0;
    
    p = sz - 1;             // all are selected
    while (p > 0) {
        Order[sp ++] = last;
        l = p;
        p &= ~(1 << last);
        last = prev[IDX2(l, last)];
    }
    
    s = malloc((min + 1) * sizeof(char));
    //assert(s);
    
    i = Order[ -- sp];
    strcpy(s, A[i]);
    printf("%s",A[i]);
    int yy;
    int su=0;

//printing each string in the order of the overlapping

    while (sp) {
        //printf("%d",sp);
        j = Order[ -- sp];
        //printf("%d",j);
        t = A[j];
        printf("\n");
        su+=addStr[IDX(i, j)];
        //for(yy=0;yy<su;yy++)
        //printf(" ");
        
        strcat(s, &t[len[j] - addStr[IDX(i, j)]]);
        for(yy=0;yy<strlen(s)- strlen(t);yy++)
        {
            printf(" ");
        }
        printf("%s",A[j]);
        
        i = j;
    }
    
    free(len);
    free(addStr);
    free(dp);
    free(prev);
    free(Order);
    
    printf("\n Length of SCS %ld",strlen(s));

return 0;

}