/* Kevin Ramos
  COP4453
  Canny1
  */

/* How to run: Compile and then execute with any picture (.pgm format). Outputs 3 images (.pgm format) given a threshold */
/* Note: For garb34.pgm, the percent "answer" is 0.046 */

#include <stdio.h>                  /*  Marr-Hildreth.c  (or marrh.c) */
#include <math.h>
#include <stdlib.h>
#define  PICSIZE 256
#define  MAXMASK 100

int    pic[PICSIZE][PICSIZE];
double outpicx[PICSIZE][PICSIZE];
double outpicy[PICSIZE][PICSIZE];
double maskx[MAXMASK][MAXMASK];
double masky[MAXMASK][MAXMASK];
double convx[PICSIZE][PICSIZE];
double convy[PICSIZE][PICSIZE];
double ival[256][256]; // magnitude
double cand[256][256]; // first peak test
double final[256][256]; // final peak image
double histo[256];

main(argc,argv)
int argc;
char **argv;
{
  int     i,j,p,q,s,t,mr,centx,centy;
  int rows = 256, cols = 256;
  double  maskvalx,maskvaly,sum1,sum2,sig,maxival,minival,maxval,ZEROTOL;
  FILE    *fo1, *fo2, *fo3, *fp1, *fopen();
  char    *foobar;
  double high = 0.0, low = 0.0, percent = 0.0;

  /* Professor's method of reading and writing in bit mode */
  argc--; argv++;
  foobar = *argv;
  fp1=fopen(foobar,"rb");

  argc--; argv++;
  foobar = *argv;
  fo1=fopen(foobar,"wb");

  argc--; argv++;
  foobar = *argv;
  fo2=fopen(foobar,"wb");

  argc--; argv++;
  foobar = *argv;
  fo3 = fopen(foobar, "wb");

  argc--; argv++;
  percent = atof(*argv);

  // Initialize the headers for the three output pictures
  fprintf(fo1, "P5\n");
  fprintf(fo1, "%d %d\n", rows, cols);
  fprintf(fo1, "255\n");

  fprintf(fo2, "P5\n");
  fprintf(fo2, "%d %d\n", rows, cols);
  fprintf(fo2, "255\n");

  fprintf(fo3, "P5\n");
  fprintf(fo3, "%d %d\n", rows, cols);
  fprintf(fo3, "255\n");

  sig = 1;
  mr = (int)(sig * 3);
  centx = (MAXMASK / 2);
  centy = (MAXMASK / 2);

  /* Read in the picture into our 2D matrix*/
  for (i=0;i<256;i++)
  { for (j=0;j<256;j++)
    {
      pic[i][j]  =  getc (fp1);
    }
  }

  /* Determine x-mask and y-mask by doubling up on the first derivative of the Gaussian equation */
  for (p=-mr;p<=mr;p++)
  {  for (q=-mr;q<=mr;q++)
    {
      maskvalx = q*exp(-1*(((p*p)+(q*q))/(2*sig*sig)));
      maskvaly = p*exp(-1*(((p*p)+(q*q))/(2*sig*sig)));

      (maskx[p+centy][q+centx]) = maskvalx;
      (masky[p+centy][q+centx]) = maskvaly;
    }
  }

  /* The convolution of our picture */
  for (i=mr;i<=255-mr;i++)
  { for (j=mr;j<=255-mr;j++)
    {
      sum1 = 0;
      sum2 = 0;
      for (p=-mr;p<=mr;p++)
      {
        for (q=-mr;q<=mr;q++)
        {
          sum1 += pic[i+p][j+q] * maskx[p+centy][q+centx];
          sum2 += pic[i+p][j+q] * masky[p+centy][q+centx]; // doubling up
        }
      }
      outpicx[i][j] = sum1;
      convx[i][j] = sum1;

      /* probably */
      outpicy[i][j] = sum2;
      convy[i][j] = sum2;
    }
  }

  // Determine the magnitude using the square root of squares
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


  /* output the first image */
  for (i=0;i<256;i++)
  { for (j=0;j<256;j++)
    {
      ival[i][j] = (ival[i][j] / maxival) * 255;
      fprintf(fo1,"%c",(char)((int)(ival[i][j])));

    }
  }

  /* part 2 using peaks */
  // instead of arctangent, get the tangent of the direction, which is the slope
  double slope = 0.0;
  for(i=mr;i<256-mr;i++){
    for(j=mr;j<256-mr;j++){

      if(convx[i][j] == 0.0){
        convx[i][j] = .00001;
      }

      slope = convy[i][j]/convx[i][j];

      // determine which test to use to find peaks based on direction
      if((slope <= .4142) && (slope > -.4142)){
        if((ival[i][j] > ival[i][j-1]) && (ival[i][j] > ival[i][j+1])){
          cand[i][j] = 255;
        }
      }
      else if((slope <= 2.4142) && (slope > .4142)){
        if((ival[i][j] > ival[i-1][j-1])&&(ival[i][j]>ival[i+1][j+1])){
          cand[i][j] = 255;
        }
      }
      else if((slope <= -.4142)&&(slope > -2.4142)){
        if((ival[i][j]>ival[i+1][j-1])&&(ival[i][j]>ival[i-1][j+1])){
          cand[i][j] = 255;
        }
      }
      else{
        if((ival[i][j]>ival[i-1][j])&&(ival[i][j]>ival[i+1][j])){
          cand[i][j] = 255;
        }
      }
    }
  }

  /* output part 2 */
  for (i=0;i<256;i++)
  { for (j=0;j<256;j++)
    {
      fprintf(fo2,"%c",(char)((int)(cand[i][j])));
    }
  }


  /* part 4 squeezed in prior to part 3 */
  // Compute a histogram of scaled magnitudes
  for(i=0;i<256;i++){
    for(j=0;j<256;j++){
      histo[(int)ival[i][j]]++;
    }
  }

  double CutOff = percent*rows*cols;
  double AreaOfTops = 0;
  int ret = 0; // to calculate high and low

  for(i=255;i>=0;i--){
    AreaOfTops += histo[i];
    if(AreaOfTops>CutOff){
      ret = i;
      i = -1;
    }
  }

  high = ret;
  low = .35*high;

  /* part 3 final output -- iterative solution*/

  for(i=0;i<256;i++){
    for(j=0;j<256;j++){
      if(cand[i][j] == 255){
        if(ival[i][j] > high){
          cand[i][j] = 0;
          final[i][j] = 255;
        }
        else if(ival[i][j] < low){
          cand[i][j] = final[i][j] = 0;
        }
      }
    }
  }

  int moretodo = 1;
  int pp = 0, qq = 0;

  while(moretodo == 1){
    moretodo = 0;

    for(i=0;i<256;i++){
      for(j=0;j<256;j++){
        // look at the neighbors to determine if this is a peak
        if(cand[i][j] == 255){
          for(pp=-1; pp<=1;pp++){
            for(qq=-1;qq<=1;qq++){

              if(final[i+pp][j+qq] == 255){
                cand[i][j] = 0;
                final[i][j] = 255;
                moretodo = 1;
              }
            }
          }
        }
      }
    }
  }

  /* output the final image */
  for (i=0;i<256;i++)
  { for (j=0;j<256;j++)
    {
      fprintf(fo3,"%c",(char)((int)(final[i][j])));
    }
  }
}
