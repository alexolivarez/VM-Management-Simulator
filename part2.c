#include <stdio.h>
#include <stdlib.h>

struct page_table{
  int f_num;
  int vi;
};

int frame_search(int frames[]){

  int f=1;
  int index;
  while(frames[f] == 1) //&& f <=7)
  {
    index = f;
    frames[f] = 0;
  }

  f++;

  return index;

}

int select_victimLRU(int lru[]) {

  int i = 0;
  int minV = lru[0];

  for(i = 1; i <= 7; i++)
  {
    if(lru[i] < minV){
      minV = lru[i];
    }
  }

  return i;
}

int main(int argc, char *argv[])
{
  unsigned long PA, LA;
  struct page_table PT[32];
  unsigned int d=7;
  unsigned int pnum, fnum, dnum; /*offset*/
  int CLK = 0;
  int freeframes[8] = {0,1,1,1,1,1,1,1};
  int LRUcount[32] = {0};
  int revmap[8] = {-1};
  //initially set all valid/invalid values in page table to 0-invalid
  int k;
  for(k=0; k<32; k++){
    PT[k].vi = 0;
  }

  //open file for reading
  FILE *fp = NULL;
  fp = fopen(argv[1],"r");

  while (1) {

  /* Read each LA-logical address in binary format to unsigned integer */
    if(fread(&LA, sizeof(unsigned long), 1, fp) != 1) break;
    CLK++;
    pnum = LA >> d;
    dnum = LA&0x07F;
    
    if(feof(fp)){
      break ;
    }
    
    if(PT[pnum].vi == 1){
      fnum = PT[pnum].f_num;
      PA = (fnum << d) + dnum;
      //fwritePA
      printf("The PA is %lx\n", PA);
      LRUcount[fnum] = CLK;
    }
    
    else //if invalid then find empty frame
    {
      int x; 
      x = frame_search(freeframes[8]); //empty when freeframes[] = 1

      if(x > 0) {
        PT[pnum].f_num = x;
        PT[pnum].vi = 1;

        fnum = PT[pnum].f_num;
        PA = (fnum<< d) + dnum;
        printf("The PA is %lx\n", PA);
        //update LRU count table and Reverse map table
        revmap[x] = pnum;
        LRUcount[fnum] = CLK; //know what time accessed
        
      }
      
      else {
      //LRU algo
      int y;
        y = select_victimLRU(LRUcount[8]); //pick the least recently used, then get that frame into PT[f_num]

        PT[revmap[y]].vi = 0; //invalid
        PT[pnum].f_num = y;
        PT[pnum].vi = 1;
        fnum = PT[pnum].f_num;
        PA = (fnum << d) + dnum;

        printf("The PA is %lx\n", PA);
        LRUcount[fnum] = CLK;
        revmap[fnum] = pnum;
      }
    }
  }
  return 0;
}
