#include<stdio.h>   
#include<conio.h>               
#include<stdlib.h>              

typedef struct Chrom             
   {
    short int bit[6];
      int fit;
   }chr;                           

void *evalp(chr pop[4]);        
int x(chr pop);
int y(int x);
void *pickchrs(chr pop[4]);
void *crossover(chr popnxt[4]);
void *mutation(chr popnxt[4]);

void main()       {                     
   int num;                            
   int i,j;

  


   enter: printf("\nPlease enter the no. of iterations:  ");
   scanf("%d",&num);                // enter the no. of iterations in num

   chr pop[4];                          
   chr popnxt[4];                            

   if(num<1)                              
   goto enter;

   evalp(pop);                          //initialise pop current
   
   for(i=0;i<num;i++)                      
{

     printf("\ni = %d\n",i);           

     for(j=0;j<4;j++)                            
        popnxt[j]=pop[j];             

     pickchrs(popnxt);                     //pick best chres
     crossover(popnxt);                     
     mutation(popnxt);                  

     for(j=0;j<4;j++)                    
        pop[j]=popnxt[j];              //copy the chres of popnxt to pop 

    }                                          

   printf("\nPress any key to end ! ");
   
   flushall();                                  
   getche();                           

}                                               //end of main



void *evalp(chr pop[4])                 //takes a pointer to a chr of 4 elements
{
 int i,j,value;
   int random;
   for(j=0;j<4;j++)                          // loop of j to choose chres from [0] to [3]
    {
        for(i=0;i<6;i++)                        // loop of i to choose the gen of the chr from  [0] to [5]
     
        {
            random=rand();                     
            random=(random%2);                  // make the random value 0 or 1 only
            pop[j].bit[i]=random;   
        }  
      
        value=x(pop[j]);                // get the value of the chr as integer
        pop[j].fit=y(x(pop[j]));    
        printf("\n pop[%d]=%d%d%d%d%d%d    value=%d    fitness = %d",j,
        pop[j].bit[5],pop[j].bit[4],pop[j].bit[3],pop[j].bit[2],
        pop[j].bit[1],pop[j].bit[0],value,pop[j].fit);    
                                                                                            
       }                                                            


  return(0);                
}                              

int x(chr pop)          
{
 int z;
   z=(pop.bit[0]*1)+(pop.bit[1]*2)+(pop.bit[2]*4)+(pop.bit[3]*8)+(pop.bit[4]*16);
   if(pop.bit[5]==1)
   z=z*(-1);                    
    return(z);                  
 }                      

int y(int x)               
{
 int y;
   y=-(x*x)+5;              
   return(y);             
}                               // end of y function

void *pickchrs(chr pop[4])      
{

 int i,j;
   chr temp;                                //temp chre to use in sorting

    for(i=0;i<3;i++)                    
       for(j=0;j<3;j++)
         {
             if(pop[j+1].fit>pop[j].fit)
               {
                 temp=pop[j+1];
                 pop[j+1]=pop[j];
                 pop[j]=temp;

               }   // end of if
         }                // end of for loop

      for(i=0;i<4;i++)
  printf("\nSorting:popnxt[%d] fitness=%d",i,pop[i].fit);      
  printf("\n");                 //print new line
      flushall();                                                       //flush the input buffer
  return(0);
}                       

void *crossover(chr popnxt[4]) // crossover function takes a pointer to array of chres
{
 int random;
   int i;
   random=rand();                                   
   random=((random%5)+1);                         
   for(i=0;i<random;i++)                        
     {
       popnxt[2].bit[i]=popnxt[0].bit[i];         //child 1 cross over
         popnxt[3].bit[i]=popnxt[1].bit[i];       // child 2 cross over
      } // end of for

 for(i=random;i<6;i++)                          // crossing the bits beyond the cross point index
     {
       popnxt[2].bit[i]=popnxt[1].bit[i];         // child 1 cross over
       popnxt[3].bit[i]=popnxt[0].bit[i];         // chlid 2 cross over
      }    // end of for

      for(i=0;i<4;i++)
       popnxt[i].fit=y(x(popnxt[i]));         

      for(i=0;i<4;i++)                           
      printf("\nCrossOver popnxt[%d]=%d%d%d%d%d%d    value=%d    fitness = %d",i,
      popnxt[i].bit[5],popnxt[i].bit[4],popnxt[i].bit[3],popnxt[i].bit[2],
      popnxt[i].bit[1],popnxt[i].bit[0],x(popnxt[i]),popnxt[i].fit); 
                      
  return(0);
   }                

void *mutation(chr popnxt[4])  
{
  
   int random;
   int row,col,value;                                     
   random=rand()%50;                  //random value is between ( 0 - 49 )

   if (random==25)    // assume probability of mutation is 2% 
   {
    col=rand()%6;                               // random column (gene) choosing 
      row=rand()%4;                             // random row ( chre ) choosing
     
     if (popnxt[row].bit[col]==0)              // invert the bit to 1 if it was 0
      popnxt[row].bit[col]=1 ;
     
      else if (popnxt[row].bit[col]==1)        // invert the bit to 0 if it was 1
           popnxt[row].bit[col]=0;
         
       popnxt[row].fit=y(x(popnxt[row]));     
       value=x(popnxt[row]);
       printf("\nMutation occured in popnxt[%d] bit[%d]:=%d%d%d%d%d%d    value=%d   
       fitness=%d",row,col,popnxt[row].bit[5],popnxt[row].bit[4],popnxt[row].bit[3],
       popnxt[row].bit[2],popnxt[row].bit[1],popnxt[row].bit[0],value,popnxt[row].fit);


   }            
 
   return(0);
}