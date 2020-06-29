#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h> 
#include<time.h> 


class RSA
{
  private:
   long double p;
   long double q;
  
   long double n;
   long double phiN;
   long double e;
   long double d;

  

  public:
  long double M;
  long double C;
  RSA()
  {
  	//GenerateRandomPrimeNos();
    	
  }
  void GeneratePrimeNo()
  {
    
  }

  void GenerateRandomPrimeNos()
  { 
  	//double a1[]={2,5,11,17,23,31,41,47,59,67,73,83,97,103,109,127,137,149,157,167};
  	//double a2[]={3,7,13,19,29,37,43,53,61,71,79,89,101,107,113,131,139,151,163,173};
  
  	double a1[]={17,23};   //now md5 can be used!
  	double a2[]={19,29};
    double temp;

  	srand (time(NULL));
    p = (int)a1[rand() % 2];

    srand (time(NULL));
    q = (int)a2[rand() % 2];
  
    //set p<q
    if((int)p>(int)q){temp=p;p=q;q=temp;}

  }
  void displayPrimeNos()
  {
  	printf("\n1st Prime Number (p)=%d",(int)p);
    printf("\n2nd Prime Number (q)=%d",(int)q);
  		
  }
  void set_N()
  {
   n=(int)p*q;
  }

  void display_N()
  {
   printf("\nN=p*q=%d",(int)n);

  }
  
  void set_phiN()
  {
   phiN= (int)((p-1)*(q-1));
  }
  
  void display_phiN()
  {
   printf("\nPhi(n)=(p-1)*(q-1)=%d",(int)phiN);
  }
  
  double gcd(double dividend, double divisor)
  {
    double remainder;
    while(1)
    {
       

       remainder= (int)dividend % (int)divisor;                          //         ============
      														  //		7 | 24  | 3
       														  //		  | 21  | 
       														  //		 =============
       														  //		    3  | 7  | 2
		       												  //		       | 6  |
       														  //		 ==============
      														  //		         1 | 3 | 3
 
       if(remainder==0) break;    														  //                   | 3 | 
       dividend=divisor;
       divisor=remainder;

      
    }
    return divisor;
   }
  
  void set_ed()
  { 
  	long double k;
    long double temp;
    long double tempD;

    for(e=q; e<(int)phiN; e++)     // choose e such that gcd(phi(n),e)=1 and 1<e<phi(n)
    {									  // another way of choosing e is selecting a prime number from a1 or a2 array
        //printf("\ne=%d phi(n)=%d",e,phiN);
        if( (int) gcd(phiN,e)==1 ) {//printf(" yes, gcd is 1"); 
        break;}
    }
     
    d=0;

    for(k=1; k<q ; k++)     // choose e such that gcd(phi(n),e)=1 and 1<e<phi(n)
    {  
    	temp = (int) (k*phiN +1) % (int) e;
        
    	//printf("\nTemp=%d\n",(int)temp );
    	if((int)temp==0) {d=(int)(k*phiN +1) / (int) e; if((int)e==(int)d) continue; else break;}
//     	if((int)(e*d) % (int)n == 1) break;

    }
   
    printf("\n++++++ PUBLIC KEY (e) ++++++++");
    printf("\n++++++      %d        ++++++++",(int)e);
    
    printf("\n\n++++++ PRIVATE KEY (d) +++++++");
    printf("\n++++++      %d        ++++++++",(int)d);
    

  } 
  void getdata()
  {
  	int x;

  	printf("\nEnter PlainText (M) to encrypt:");    //M must be leass than n;
    
    scanf("%d",&x);

    M=x;
   // / M= (double)M;

   // printf("\n========Entered Pladoubleext (M) is :%d",M);

    //if(M>=n){printf("\nEntered data (M) must be less than n=(%d)",n);goto L1;}
  } 

  
  void getciphertext()
  {
  	int x;

  	printf("\n\nEnter Ciphertext (C) to decrypt:");
    scanf("%d",&x);
    C=x;
   
  	//C=double(C);
  //	printf("\n========Entered Ciphertext (D) is:%d",C);

  } 
 long double findmod( long double a,  long double nn)
 {
     long double k=0;
   //  printf("We ha ve to ginf mod between: %d and %d",(int)a, (int)p);
     
     while(a>0)
     {  
     	k=a;
     	a = a - nn;    
     }
     return k;
 }
  
  long double power_mod( long double a,  long double exponent)
 {

         long double k;
         long double answer=1;

        //printf("\nGiven base=%d, exponent=%d",(int)a, (int)exponent);

        for(k=0;k<(int)exponent;k++)
        {
           answer= findmod(answer*a,n) ;
        }
       
       //printf("Power=%d",(int)answer );      
       return findmod(answer, n);
 }



 void encryptRSA()
 {
  	getdata();

  	//printf("\nEntered PlainText (M) is :%d",(int)M);
  	//printf("\nvalue of e is :%d",(int)e);
    // M = ( long double) M;
    
    C = power_mod(M,e);
    

    // find power easily; using eulers theorem
    // eulersformula(C,d);

    //printf("\npow(M,e)=%d", ( long double)pow(M,e));

    printf("CipherText:%d",(int)C);
 }
  
  void decryptRSA(){
  	getciphertext();
  	
  	//M  = ( long double) M;
    M = power_mod(C,d);
    
    //printf("\npow(C,d)=%d", ( long double)pow(C,d));
    printf("PlainText:%d",(int)M);
  }
 

};


void rsa_algorithm(RSA *obj)
{
	printf("\n*************************************************************");
	printf("\n************************   RSA      *************************");
    printf("\n*************************************************************");
   
    //GENERATE PRIME NUMBERS;
    obj->GenerateRandomPrimeNos();
    
    //DISPLAY THE JUST GENERATED PRIME NUMBERS;
    obj->displayPrimeNos();
    
    //SET N=p*q
    obj->set_N();
    
    //SET Phi(N)=(p-1)*(q-1)
    obj->set_phiN();
    
    //SET N=p*q
    obj->display_N();
    
    //SET Phi(N)=(p-1)*(q-1)
    obj->display_phiN();
    
    //SET e and d= ed=1 mod phin(n)
    obj->set_ed();
    
    
    //ENCRYPT OR DECYPT;
    obj->encryptRSA();

    //ENCRYPT OR DECYPT;
    obj->decryptRSA();


    

}

void main()
{
    double choice=1;
    RSA obj;
    //clrscr();
    
     //while(choice!=3)
    rsa_algorithm(&obj);
    
	//getch();
}