/*
The following code is used to edge color a bipartite graph using alternating(a,b) path technique.

Input

a. nl,nr and m, the numbers of left column vertices, right column vertices, and edges. nl <= nr <=50 and m <=1000.
b. m lines, each giving an edge: left column vertex, right column vertex. Left column vertices are numbered 0 . . . nl-1.
   Right column vertices are numbered 0 . . . nr- 1. Duplicate edges will not occur.

Output

a. A trace of the processing. Each edge will be processed by either 
    1) using a color that is “free” at both incident vertices, 
       or 
    2) using an alternating (a, b) path. For (1), simply indicate the free color that is used for the edge. For
       (2), indicate the colors (e.g. numbers) for a and b along with the vertices on the path.
b. A list of the edges (input order) and the final color for each edge.

References:
1. https://ranger.uta.edu/~weems/NOTES5311/LAB/LAB2SPR22/lab2spr22.pdf

*/

#include <stdio.h>

struct graph
{
    int vertexLeft, vertexRight;
    int edgecolor;
};

int main()
{
    int nl,nr,m;
    int maxLeft=0,maxRight=0;
    int i,j,k,l;
   
    scanf("%d",&nl);
    scanf("%d",&nr);
    scanf("%d",&m);
    struct graph edge[m];
    
    if(nl>50 || nr>50 || m>1000)
    {
        printf("edges not in the limits");
        return 0;
    }
    
    int colors=m/nl;
    
    for(i=0;i<m;i++)
    {
        scanf("%d",&edge[i].vertexLeft);
        scanf("%d",&edge[i].vertexRight);
        edge[i].colorsUsedLeft=2500;
        edge[i].colorsUsedRight=2500;
        edge[i].edgecolor=2500;
        if(maxLeft<edge[i].vertexLeft)
        {
            maxLeft=edge[i].vertexLeft;
        }
        if(maxRight<edge[i].vertexRight)
        {
            maxRight=edge[i].vertexRight;
        }
        
    }
     
   

//**************************************************************  Case1  ****************************************************************


    for(i=0;i<m;i++) //For edges
    {
        char colorAvailable='N';
        for(j=0;j<colors;j++) // For colors
        {
            //printf("%d %d %d\n",edge[i].colorsUsedLeft,edge[i].colorsUsedRight,edge[i].edgecolor);
            
            int color;
            for(k=0;k<m;k++)
            {
                if((edge[k].vertexLeft==edge[i].vertexLeft && edge[k].vertexRight<maxRight) || (edge[k].vertexLeft<maxLeft && edge[k].vertexRight==edge[i].vertexRight))
                {
                    if(edge[k].edgecolor==j)
                    {
                        colorAvailable='N';
                        break;
                    }
                    else
                    {
                        colorAvailable='Y';
                        //edge[i].edgecolor=j;
                        //edge[i].colorsUsedLeft=j;
                        //edge[i].colorsUsedRight=j;
                        //printf("Case 1: edge %d (%d %d) gets color %d\n",i,edge[i].vertexLeft,edge[i].vertexRight,j);
                    }
                }
            }
            
            if(colorAvailable=='Y')
            {
                edge[i].edgecolor=j;
                //edge[i].colorsUsedLeft=j;
                //edge[i].colorsUsedRight=j;
                printf("Case 1: edge %d (%d %d) gets color %d\n",i,edge[i].vertexLeft,edge[i].vertexRight,j);
                break;
            }
        }
//***************************************************************   Case2 ( alternating(a,b) )  *********************************************************

        if(colorAvailable=='N')
        {
            int a,b;
            
//***************************************************************   Find "a" ***************************************************************************
            for(k=0;k<nl;k++)
            {
                if(a==k-1)
                {
                    break;
                }
                 for(l=i;l>=0;l--)
                {
                     if(edge[l].vertexLeft==edge[i].vertexLeft)
                     {
                        if(edge[l].edgecolor==k)
                        {
                            a=k+1;
                            break;
                        }
                        else
                        {
                            a=k;
                        }
                     }
                }  
            }
            
//**************************************************************  Find "b" ******************************************************************************************

           for(k=0;k<nl;k++)
            {
                if(b==k-1)
                {
                    break;
                }
                 for(l=i;l>=0;l--)
                {
                     if(edge[l].vertexRight==edge[i].vertexRight)
                     {
                        if(edge[l].edgecolor==k)
                        {
                            b=k+1;
                            break;
                        }
                        else
                        {
                            b=k;
                        }
                     }
                }  
            }

            
//*************************************************************  Find Path and Swap "a" and "b" ****************************************************************


            char nextpath='T';
            int curredge=i;
            int nextvertex;
            printf("Case 2: edge %d (%d %d) gets color a=%d, swaps with b=%d",i,edge[i].vertexLeft,edge[i].vertexRight,a,b);
            for(k=i;k>=0;k--)
               {
                   //printf("%d %d %d\n",edge[k].vertexRight,edge[currvertex].vertexRight,edge[k].edgecolor);
                   if(edge[k].vertexRight==edge[i].vertexRight && edge[k].edgecolor==a)
                   {
                       //printf("%d %d %d\n",edge[k].vertexRight,edge[currvertex].vertexRight,edge[k].edgecolor);
                       curredge=k;
                       edge[k].edgecolor=b;
                       //printf("%c",nextpath);
                       break;
                   }
                   
               }
               printf(" r:%d l:%d",edge[curredge].vertexRight,edge[curredge].vertexLeft);
               while(nextpath=='T')
               {
                   //left to right
                   for(k=0;k<m;k++)
                   {
                      //printf(" %d %d %d  %d %d %d ",edge[k].vertexLeft,edge[k].edgecolor,edge[k].vertexRight,edge[curredge].vertexLeft,b,edge[curredge].vertexRight);
                       if(edge[k].vertexLeft==edge[curredge].vertexLeft && edge[k].edgecolor==b && edge[k].vertexRight!=edge[curredge].vertexRight)
                       {
                           edge[k].edgecolor=a;
                           curredge=k;
                           printf(" r:%d",edge[k].vertexRight);
                           break;
                       }
                   }
                   //right to left
                   for(k=0;k<m;k++)
                   {
                       if(edge[k].vertexRight==edge[curredge].vertexRight && edge[k].edgecolor==a && edge[k].vertexLeft!=edge[curredge].vertexLeft)
                       {
                           edge[k].edgecolor=b;
                           nextpath='T';
                           curredge=k;
                           printf(" l:%d",edge[k].vertexLeft);
                           break;
                       }
                       else
                       {
                           nextpath='F';
                       }
                   }
                   if(nextpath=='F')
                   {
                       edge[i].edgecolor=a;
                       printf("\n");
                   }
               }
            
        }
    }
    
    for(i=0;i<m;i++)
    {
        printf("%d %d %d\n",edge[i].vertexLeft,edge[i].vertexRight,edge[i].edgecolor);
    }
    
    return 0;
}
