#include <stdio.h>
#include <emmintrin.h>


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
   unsigned i, j, k;

   int r = n%4;
   n = n - r;

   for(i=0; i<n+r; i++ ){
      c[i]-=b[(n+r)-1-i]*(n+r);
   }
   

   for(i=0; i<n-4; i=i+4){
      
      c[i]+=a[i][i+1] + a[i][i+2] + a[i][i+3];
      c[i+1]+=a[i+1][i+2] + a[i+1][i+3] + a[i+1][i+4];
      c[i+2]+=a[i+2][i+3] + a[i+2][i+4] + a[i+2][i+5];
      c[i+3]+=a[i+3][i+4] + a[i+3][i+5] + a[i+3][i+6];

      for(j=i+4; j<n-4; j=j+4){
         c[i]+=a[i][j] + a[i][j+1] + a[i][j+2] + a[i][j+3];
         c[i+1]+=a[i+1][j+1] + a[i+1][j+2] + a[i+1][j+3] + a[i+1][j+4];
         c[i+2]+=a[i+2][j+2] + a[i+2][j+3] + a[i+2][j+4] + a[i+2][j+5];
         c[i+3]+=a[i+3][j+3] + a[i+3][j+4] + a[i+3][j+5] + a[i+3][j+6];
      }

      for (k=0; k < r + 4; k++)
      {
         c[i]  += a[i][j+k];
      }

      for (k=1; k < r + 4; k++)
      {
         c[i+1]  += a[i+1][j+k] ;
      }

      for (k=2; k < r + 4; k++)
      {
         c[i+2]  += a[i+2][j+k] ;
      }

      for (k=3; k < r + 4; k++)
      {
         c[i+3]  += a[i+3][j+k] ;
      }
      
      //c[i+1]+= (a[i+1][j+1] + a[i+1][j+2]+ a[i+1][j+3]);
      //c[i+2]+= (a[i+2][j+2] + a[i+2][j+3]);
      //c[i+3]+= a[i+3][j+3];
      
   }

   for(; i<n+r; i++){
      for(j=i+1; j<n+r; j++){
         c[i]+=a[i][j];
      }   
   }
}


#elif defined OPT4
/*Unrolling + OPT2*/
void kernel (unsigned n, const double a[n][n], const double b[n], double c[n]) {
   unsigned i, j, k;

   double k1, k2, k3, k4;
   k1 = 0;
   k2 = 0;
   k3 = 0;
   k4 = 0;

   int r = n%4;
   n = n - r;

   for(i=0; i<n+r; i++ ){
      c[i]-=b[(n+r)-1-i]*(n+r);
   }
   

   for(i=0; i<n-4; i=i+4){
      
      k1+=a[i][i+1] + a[i][i+2] + a[i][i+3];
      k2+=a[i+1][i+2] + a[i+1][i+3] + a[i+1][i+4];
      k3+=a[i+2][i+3] + a[i+2][i+4] + a[i+2][i+5];
      k4+=a[i+3][i+4] + a[i+3][i+5] + a[i+3][i+6];

      for(j=i+4; j<n-4; j=j+4){
         k1+=a[i][j] + a[i][j+1] + a[i][j+2] + a[i][j+3];
         k2+=a[i+1][j+1] + a[i+1][j+2] + a[i+1][j+3] + a[i+1][j+4];
         k3+=a[i+2][j+2] + a[i+2][j+3] + a[i+2][j+4] + a[i+2][j+5];
         k4+=a[i+3][j+3] + a[i+3][j+4] + a[i+3][j+5] + a[i+3][j+6];
      }

      for (k=0; k < r + 4; k++)
      {
         k1  += a[i][j+k];
      }

      for (k=1; k < r + 4; k++)
      {
         k2  += a[i+1][j+k] ;
      }

      for (k=2; k < r + 4; k++)
      {
         k3  += a[i+2][j+k] ;
      }

      for (k=3; k < r + 4; k++)
      {
         k4  += a[i+3][j+k] ;
      }
      
      c[i]+=k1;
      c[i+1]+=k2;
      c[i+2]+=k3;
      c[i+3]+=k4;
      k1=0;
      k2=0;
      k3=0;
      k4=0;
      
   }

   for(; i<n+r; i++){
      for(j=i+1; j<n+r; j++){
         c[i]+=a[i][j];
      }   
   }
}

#elif defined OPT5
/* OPT4 + vectorisation*/
void kernel (unsigned n, const double a[n][n], const double b[n], double c[n]) {
   unsigned i, j, k;

   int r = n%4;
   n = n - r;

   for(i=0; i<n+r; i++ ){
      c[i]-=b[(n+r)-1-i]*(n+r);
   }
   

   for(i=0; i<n-4; i=i+4){
      
      c[i]+=a[i][i+1] + a[i][i+2] + a[i][i+3];
      c[i+1]+=a[i+1][i+2] + a[i+1][i+3] + a[i+1][i+4];
      c[i+2]+=a[i+2][i+3] + a[i+2][i+4] + a[i+2][i+5];
      c[i+3]+=a[i+3][i+4] + a[i+3][i+5] + a[i+3][i+6];

      for(j = i + 4; j < n - 4; j += 4){
         __m128d temp1, temp2, somme;

         // Pour c[i]
         temp1 = _mm_loadu_pd(&a[i][j]);      // Charge a[i][j] et a[i][j+1]
         temp2 = _mm_loadu_pd(&a[i][j+2]);    // Charge a[i][j+2] et a[i][j+3]
         somme = _mm_add_pd(temp1, temp2);     // Additionne les deux premiers vecteurs
         c[i] += somme[0] + somme[1];           // Ajoute les éléments du vecteur résultant à c[i]

         // Pour c[i+1]
         temp1 = _mm_loadu_pd(&a[i+1][j+1]);  // Charge a[i+1][j+1] et a[i+1][j+2]
         temp2 = _mm_loadu_pd(&a[i+1][j+3]);  // Charge a[i+1][j+3] et a[i+1][j+4]
         somme = _mm_add_pd(temp1, temp2);     // Additionne les deux vecteurs
         c[i+1] += somme[0] + somme[1];         // Ajoute les éléments du vecteur résultant à c[i+1]

         // Pour c[i+2]
         temp1 = _mm_loadu_pd(&a[i+2][j+2]);  // Charge a[i+2][j+2] et a[i+2][j+3]
         temp2 = _mm_loadu_pd(&a[i+2][j+4]);  // Charge a[i+2][j+4] et a[i+2][j+5]
         somme = _mm_add_pd(temp1, temp2);     // Additionne les deux vecteurs
         c[i+2] += somme[0] + somme[1];         // Ajoute les éléments du vecteur résultant à c[i+2]

         // Pour c[i+3]
         temp1 = _mm_loadu_pd(&a[i+3][j+3]);  // Charge a[i+3][j+3] et a[i+3][j+4]
         temp2 = _mm_loadu_pd(&a[i+3][j+5]);  // Charge a[i+3][j+5] et a[i+3][j+6]
         somme = _mm_add_pd(temp1, temp2);     // Additionne les deux vecteurs
         c[i+3] += somme[0] + somme[1];         // Ajoute les éléments du vecteur résultant à c[i+3]
      }

      for (k=0; k < r + 4; k++)
      {
         c[i]  += a[i][j+k];
      }

      for (k=1; k < r + 4; k++)
      {
         c[i+1]  += a[i+1][j+k] ;
      }

      for (k=2; k < r + 4; k++)
      {
         c[i+2]  += a[i+2][j+k] ;
      }

      for (k=3; k < r + 4; k++)
      {
         c[i+3]  += a[i+3][j+k] ;
      }
      
      //c[i+1]+= (a[i+1][j+1] + a[i+1][j+2]+ a[i+1][j+3]);
      //c[i+2]+= (a[i+2][j+2] + a[i+2][j+3]);
      //c[i+3]+= a[i+3][j+3];
      
   }

   for(; i<n+r; i++){
      for(j=i+1; j<n+r; j++){
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

