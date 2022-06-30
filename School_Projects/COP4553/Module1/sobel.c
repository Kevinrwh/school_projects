#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int pic[256][256];
int outpicx[256][256];
int outpicy[256][256];
int maskx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
int masky[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
double ival[256][256],maxival;

main(argc,argv)
int argc;
char **argv;
{
  int i,j,p,q,mr,sum1,sum2;
  double HI, LO;
  FILE *fo1, *fo2, *fo3, *fp1, *fopen();
  char *foobar;
  char *foobar2;
  char *foobar3;

  argc--; argv++; // read first argument (input)
  foobar = *argv;
  fp1=fopen(foobar,"rb");

  argc--; argv++; // write to second argument (output: image 1)
  foobar = *argv;
  fo1=fopen(foobar,"wb");

  argc--; argv++;
  foobar2 = *argv;
  fo2 = fopen(foobar2, "wb");

  argc--; argv++;
  foobar3 = *argv;
  fo3 = fopen(foobar3, "wb");

  int rows = 256, cols = 256;

  // first image
  fprintf(fo1, "P5\n");
  fprintf(fo1, "%d %d\n", rows, cols);
  fprintf(fo1, "255\n");

  // second image
  fprintf(fo2, "P5\n");
  fprintf(fo2, "%d %d\n", rows, cols);
  fprintf(fo2, "255\n");

  // third image
  fprintf(fo3, "P5\n");
  fprintf(fo3, "%d %d\n", rows, cols);
  fprintf(fo3, "255\n");

  argc--; argv++; // go to third argument
  foobar = *argv;

  // we need two HIs, one high and one low
  HI = atof(foobar);
  printf("high: %f\n", HI);

  argc--; argv++;
  foobar = *argv;

  LO = atof(foobar); // second threshold
  printf("low: %f\n", LO);

  for (i=0;i<256;i++)
  { for (j=0;j<256;j++)
    {
      pic[i][j]  =  getc (fp1);
      pic[i][j]  &= 0377;
    }
  }

  mr = 1;
  for (i=mr;i<256-mr;i++)
  { for (j=mr;j<256-mr;j++)
    {
      sum1 = 0;
      sum2 = 0;
      for (p=-mr;p<=mr;p++)
      {
        for (q=-mr;q<=mr;q++)
        {
          sum1 += pic[i+p][j+q] * maskx[p+mr][q+mr];
          sum2 += pic[i+p][j+q] * masky[p+mr][q+mr];
        }
      }
      outpicx[i][j] = sum1;
      outpicy[i][j] = sum2;
    }
  }

  maxival = 0;
  for (i=mr;i<256-mr;i++)
  { for (j=mr;j<256-mr;j++)
    {
      ival[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) +
      (outpicy[i][j]*outpicy[i][j])));
      if (ival[i][j] > maxival)
      maxival = ival[i][j];

    }
  }

  int temp = 0, temp2 = 0, temp3 = 0;

  // To form pmg images
  for (i=0;i<256;i++)
  { for (j=0;j<256;j++)
    {
      // high threshold
      temp = ival[i][j];
      temp = (temp / maxival) * 255;
      /* edit: first threshold. I think because of overwriting, it's causing
      a duplicate picture to be formed. */
      if(temp > HI){
        temp = 255;
      } else{
        temp = 0;
      }
      fprintf(fo1,"%c",(char)((int)(temp)));

      /* Low threshold*/
      temp2 = ival[i][j];
      temp2 = (temp2/maxival)*255;
      if(temp2 > LO){
        temp2 = 255;
      } else{
        temp2 = 0;
      }
      fprintf(fo2, "%c", (char)((int)(temp2)));

      /* Magnitude image */
      temp3 = ival[i][j];
      temp3 = (temp3/maxival)*255;
      fprintf(fo3, "%c", (char)((int)(temp3)));
    }
  }
}
