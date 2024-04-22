#ifdef OPT1

void kernel (unsigned n, const double a[n][n], const double b[n], double c[n]) {
   unsigned i, j;
   for (j=0; j<n; j++)
      c[j]-=b[n-1-j]*n;
   for (i=0; i<n; i++) {
      for (j=i+1; j<n; j++)
         c[i]+=a[i][j] ;
   }
}


#elif defined OPT2

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


