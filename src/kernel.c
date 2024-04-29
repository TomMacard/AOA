
#ifdef OPT1


/* opt , faire partir i de j au lieu de 0, et faire sauter le conditionnel */
void kernel (unsigned n, const double a[n][n], const double b[n], double c[n]) {
   unsigned i, j;
   for (j=0; j<n; j++) {
      c[j]-=b[n-1-j]*n;
      for (i=j+1; i<n; i++) {
         c[j]+=a[j][i] ;
      }
   }
}



#elif defined OPT2
/* Reduction d'accés mémoire à c[] en utilisant une variable temporaire*/
void kernel (unsigned n, const double a[n][n], const double b[n], double c[n]) {
   unsigned i, j;
   for (j=0; j<n; j++) {
      c[j]-=b[n-1-j]*n;
      double k = 0;
      for (i=j+1; i<n; i++) {
         k+=a[j][i] ;
      }
      c[j]+=k;
   }
}

#elif defined OPT3
/*Unrolling*/
void kernel (unsigned n, const double a[n][n], const double b[n], double c[n]) {
   unsigned i, j;

   for(i=0; i<n; i++ ){
      c[i]-=b[n-1-i]*n;
   }

   for(i=0; i<n-4; i=i+4){
      
      c[i]+=  a[i][i+1]   + a[i][i+2] +   a[i][i+3];
      c[i+1]+=a[i+1][i+2] + a[i+1][i+3] + a[i+1][i+4];
      c[i+2]+=a[i+2][i+3] + a[i+2][i+4] + a[i+2][i+5];
      c[i+3]+=a[i+3][i+4] + a[i+3][i+5] + a[i+3][i+6];

      for(j=i+4; j<n-4; j=j+4){
         c[i]+=  a[i][j]     + a[i][j+1]   + a[i][j+2] +   a[i][j+3];
         c[i+1]+=a[i+1][j+1] + a[i+1][j+2] + a[i+1][j+3] + a[i+1][j+4];
         c[i+2]+=a[i+2][j+2] + a[i+2][j+3] + a[i+2][j+4] + a[i+2][j+5];
         c[i+3]+=a[i+3][j+3] + a[i+3][j+4] + a[i+3][j+5] + a[i+3][j+6];
      }

      c[i]  += a[i][j]     + a[i][j+1]   + a[i][j+2]   + a[i][j+3];
      c[i+1]+= a[i+1][j+1] + a[i+1][j+2] + a[i+1][j+3];
      c[i+2]+= a[i+2][j+2] + a[i+2][j+3];
      c[i+3]+= a[i+3][j+3];
      
   }

   for(; i<n; i++){
      for(j=i+1; j<n; j++){
         c[i]+=a[i][j];
      }   
   }
}

#else

/* Baseline */
void kernel (unsigned n, const double a[n][n], const double b[n], double c[n]) {
   unsigned i, j;
   for (j=0; j<n; j++)
      for (i=0; i<n; i++) {
         c[i]-=b[n-1-i];
         if (i<j)
            c[i]+=a[i][j] ;
   }
}
#endif

