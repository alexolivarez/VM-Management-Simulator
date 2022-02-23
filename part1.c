#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  unsigned int PT[32] = {2,4,1,7,3,5,6,0};
  unsigned int p=5, f=3, d=7;
  unsigned long LA, PA;
  unsigned int pnum, fnum, dnum; /*offset*/
  FILE *fp = NULL;
  fp = fopen(argv[1],"r");
  int n = 0;
  while(1){
    //if(fread(&LA, sizeof(unsigned long), 1, fp) != 1)
      fread(&LA, sizeof(unsigned long), 1, fp);
      dnum = LA&0x7F;
      pnum = LA >> d; //shift 'd' bits to right
      fnum = PT[pnum];
      PA = (fnum << d) + dnum; //or fnum << d | dnum?
      if( feof(fp) ) { 
        break ;
      }
      printf("The LA is %lx and Translated PA is %lx\n", LA, PA);
      //printf("%016lx\n", LA);
      //printf("%016lx\n", PA);    
    n++;
  }
  printf("total number of pages = %d", n);
  printf("\n-------------------------------\n");
  //test print
  //printf("\n%016lx\n", LA);
  //printf("\n%016lx\n", PA);
  fclose(fp);
  return 0;
}
