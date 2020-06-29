/*Implementation of MUNEEBS DIGITAL SIGNATURE in CPP 
  
  Encryption/Decryption: RSA
  Hahing Algorithm: MD5

  Hardcoded by
  MUNEEB AHMED PANDITH
  M.TECH CSE
  Jamia Millia Islamia
  
  muneebpandith@gmail.com
  http://www.twitter.com/munneeb
  Compiled in G++
  
*/


#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include<stdlib.h> 
#include<time.h> 
#include<fstream.h>
#include<string.h>
#include<process.h>

class txt{
  public:
  unsigned char ch;
}txtobj;


class nmb{
  public:
  long double number;
}nmbobj;

class MD5 {
    public:
      char *text;
      unsigned char* digest;

     // int blocks,textlengthinbits,remainderbits;    //PARAMETRES for calculation and padding

     unsigned int textlength;   //in bytes
     unsigned int blocks,remainderbytes;    //PARAMETRES for calculation and padding
     unsigned int T[64];          //T TABLE
     unsigned long int a,b,c,d;
     unsigned long int vector[4];
      int spr;


    public:
    MD5()
       { int i;
      text=new char[1000];                        //say 100 bytes input
      for(i=0;i<999;i++) text[i]=NULL;
      strcpy(text,"");
      textlength=0;
      digest=new unsigned char[16];                        //say 100 bytes input
       
      a=vector[0] = 0x67452301;
      b=vector[1] = 0xefcdab89;
      c=vector[2] = 0x98badcfe;
      d=vector[3] = 0x10325476;

       }

    void getdata(char * filename)
       {
     
      int i=0;
      unsigned char ch;
      fstream fp;
      
      fp.open(filename,ios::in);
      fp>>text;
      //strcpy(text,fp.gets());
      fp.close();
 //     cout<<"Enter a text string to be hashed:";
        //strcpy(text,t);
        text[strlen(text)]='~';    //marks end of the text
         text[strlen(text)+1]=NULL;   

       }


    void print()
      { 
   
      //clrscr();
    cout<<"\nText in the filename: "<<text;
     


      }

      printfull()
      {
        int count=0;
        cout<<"\n\nCOPNPLETE TEXT: ";
        for(count=0;count<stringlength(text);count++)
        {
          cout<<text[count];

        }
        cout<<".";

      }

    void divideintoblocksof512()
    {
      
   //textlength contains no of BYTES taken by TEXT
   //divide into n-blocks of y-bits each; Here y=512 bits;
     textlength=stringlength(text);              //no of bytes taken byt he TEXT
      //textlengthinbits=textlength*8    ;    //no of bits taken by TEXT
      blocks=textlength / 64;        //will give us no of blocks each of size 512-bits (=64 bytes);
      remainderbytes=textlength % 64;   //will give us remainder block that are 512-bits in size and need to be padded;
      

   }
   void padding()
   {
       unsigned int bytestobepadded;
       unsigned int offset=0;                                 //this contains the offset from TEXTLENGTH that is to be padded
       int byteno=1;
       text[textlength]=0x00;

       if(remainderbytes<56)  //ifthe input text is >=56 bytes we have to pad upto nect block
          {
            bytestobepadded=56-remainderbytes; 
           
          }
      else{ bytestobepadded=120-remainderbytes;  }      //we have to pad BYTESTOBEPADDED number of bytes (=448-remainderbits OR 56-remainderbytes)
      
       //Because we are dealing with bytes, we can't pad a binary bit by bit
   
       //Step 1: So, we can append a byte and not a bit! Therfore we append Byte as Hex(0x80) OR Bin(10000000)
       //Step 2: then pad 0s taking one byte at a time and not just a bit, because we dealing with bytes! as Hex(0x00) OR Bin(00000000)

    
       while(bytestobepadded>0)     //loop until no bittobepadded is there
  {
      if(byteno==1){text[(64*blocks)+remainderbytes+offset]=0x80;}   //So Step1: Pad 0x80 //this is the first byte we are padding as defined by Step 1
        else{text[(64*blocks)+remainderbytes+offset]=0x00;  }     //And then Step2: Pad 0x00 for rest of the bytes  // next 8-bits are padded with 0x00
      bytestobepadded--;                   // since 8-bits have been padded. Now we have BITSTOBEPADDED minus 8 no of bits to be padded more
      offset++; 
      byteno++;                           // as padding takes place 8-bits at a time, offset is incremented to next byte
  }
  text[(64*blocks)+remainderbytes+offset]='~';    //marks end of padding. Appending og length will start from here
   spr= (64*blocks)+remainderbytes+offset;

    }

    void appendsize()
    {
   //int bytesleftforsize=8;          //the last 64-bits OR 8-bytes left after padding for appending size of original message
   //we can have 64-bits representing the size of the original message

   //sizecalculation of original message
   //TEXTLENGTH has changed theoretically after padding but the variable has not been changed manually. so it will have the original value
   //so we are actually converting TEXTLENGTH into hex/binary and then append it to the textmessage;
   int n=textlength*8;    // it will contain the no of bits of the original mesage for dec to bin calculation
     
     int totallengthafterpadding=stringlength(text);   //will need it to set length at that byte. string length checks for '~' sign
     
     int counterofbits=0;
   unsigned int remainder;
   int offset=0;
     

     text[totallengthafterpadding]=0x00;//because we we must have NULL (0X00) at that place, since we have put '~' there in padding stage
   
     
   while(offset<8)  //8bytes
       {
    remainder=n % 2;
    n=n/2;
        

    text[totallengthafterpadding+offset]= ((remainder << counterofbits ) | (remainder >> (8-counterofbits) )) | text[totallengthafterpadding+offset] ;
    counterofbits++;            //must run from 0 to 7 in each iteration

    if(counterofbits==8){ counterofbits=0;  offset++;}
       }

       //appending successful! :*
      text[totallengthafterpadding+offset]='~';   //marks end of string after everything is calculated
      spr= totallengthafterpadding+offset;





    }




/*
T[ 0.. 3] := { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee }
T[ 4.. 7] := { 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 }
T[ 8..11] := { 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be }
T[12..15] := { 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 }
T[16..19] := { 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa }
T[20..23] := { 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 }
T[24..27] := { 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed }
T[28..31] := { 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a }
T[32..35] := { 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c }
T[36..39] := { 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 }
T[40..43] := { 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 }
T[44..47] := { 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 }
T[48..51] := { 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 }
T[52..55] := { 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 }
T[56..59] := { 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 }
T[60..63] := { 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 }
This can be manually generated as below algorithm TMatrix()
*/

    void TMatrix()
    {
       // Let T[i] denote the i-th element of the table, which
       // is equal to the integer part of 4294967296 (= 2power32) times abs(sin(i)
       double s, pwr;
       int i;
      pwr = pow( 2, 32);
      for (i=1; i<=64; i++)
     {
       s = fabs(sin(i));
       T[i] = (unsigned)( s * pwr );
      }
      //TMatrix generated
    }



unsigned long int F(unsigned long int *x,unsigned long int *y, unsigned long int *z) 
               {
                return ((*x) & (*y)) | (~(*x) & (*z));
               }
unsigned long int G(unsigned long int *x,unsigned long int *y, unsigned long int *z) 
               {
              return ((*x) & (*z)) | ((*y) & ~(*z));
               }
unsigned long int H(unsigned long int *x,unsigned long int *y, unsigned long int *z) 
               {
                return ((*x) ^ (*y) ^ (*z));
               }
unsigned long int I(unsigned long int *x,unsigned long int *y, unsigned long int *z) 
               {
                return ((*y) ^ ((*x) | ~(*z)));
               }
unsigned long int rotateleft( unsigned long int r, short N )
  {   return ( (r<<N) | (r>>(32-N)) );
  }

 void ROTATE_4BYTES_TORIGHT()
 { unsigned long int temp;
    temp=d;
    d=c;
    c=b;
    b=a;
    a=temp;
 }



void  FF(unsigned long int x, int s, unsigned long int ac) 

  { 
  a  += F(&b, &c, &d) + (x) + (ac); 
  a  = rotateleft(a, s); 
  a  += b;
 ROTATE_4BYTES_TORIGHT();
  }

  void GG(unsigned long int x, int s, unsigned long int ac) { 
  a += G(&b, &c, &d) + (x) + (ac); 
  a = rotateleft(a, s); 
  a += b;
 ROTATE_4BYTES_TORIGHT();
 }

  void  HH(unsigned long int x, int s, unsigned long int ac) { 
  a += H(&b, &c, &d) + (x) + (ac); 
  a = rotateleft(a, s); 
  a += b;
 ROTATE_4BYTES_TORIGHT();
}
  void  II(unsigned long int x, int s, unsigned long int ac) { 
  a += I(&b, &c, &d) + (x) + (ac);          
  a = rotateleft(a, s); 
  a += b;
 ROTATE_4BYTES_TORIGHT();
}

    void Hash()
    {
      //INITIALIZATION
      
      unsigned long int w[16];      //used for breaking a 512-bit-block OR 64-BYTE-BLOCK) into 16-WORDS (each of 32-Bits OR 4-Bytes)
      int offset,new_len,i;

      new_len=stringlength(text);   //the new_length of the text after padding and appendingsize in bytes
      text[stringlength(text)]=0x00;
      
     
  //for each 512-bit chunk of message:
   for(offset=0; offset<(new_len/64); offset += 64)        //total blocks/chunk each of 512bits or 64bytes
    {
       // break each 512bit/64byte chunk into sixteen 32-bit words/4byte w[j], from 0 to 15
        for (i = 0; i < 16; ++i){ w[i] = *((unsigned long int*)(text + offset + (i<<2)));}


        //we have 4 rounds now

        //ROUNF 1
        //SHIFTS 7,12 ect may be stored in an array
        //shiftarray[]=7,12,17,22    


        /*
         for(step=0;step<15;step++)
         { if (step%4==0){steparraycount=0} 
          
         FF(w[step], sfiftarray[step+steparraycount], T[step])
        steparraycount++;
        
         
        */


        
        FF(w[0],  7, 0xD76AA478);       
        FF(w[1], 12, 0xE8C7B756);
        FF(w[2], 17, 0x242070DB);
        FF(w[ 3], 22, 0xC1BDCEEE);

        FF(w[ 4],  7, 0xF57C0FAF);
        FF(w[ 5], 12, 0x4787C62A);
        FF(w[ 6], 17, 0xA8304613);
        FF(w[ 7], 22, 0xFD469501);
        FF(w[ 8],  7, 0x698098D8);
        FF(w[ 9], 12, 0x8B44F7AF);
        FF(w[10], 17, 0xFFFF5BB1);
        FF(w[11], 22, 0x895CD7BE);
        FF(w[12],  7, 0x6B901122);
        FF(w[13], 12, 0xFD987193);
        FF(w[14], 17, 0xA679438E);
        FF(w[15], 22, 0x49B40821);

        //rOUND 2
        GG(w[ 1],  5, 0xF61E2562);
        GG(w[ 6],  9, 0xC040B340);
        GG(w[11], 14, 0x265E5A51);
        GG(w[ 0], 20, 0xE9B6C7AA);
        GG(w[ 5],  5, 0xD62F105D);
        GG(w[10],  9, 0x02441453);
        GG(w[15], 14, 0xD8A1E681);
        GG(w[ 4], 20, 0xE7D3FBC8);
        GG(w[ 9],  5, 0x21E1CDE6);
        GG(w[14],  9, 0xC33707D6);
        GG(w[ 3], 14, 0xF4D50D87);
        GG(w[ 8], 20, 0x455A14ED);
        GG(w[13],  5, 0xA9E3E905);
        GG(w[ 2],  9, 0xFCEFA3F8);
        GG(w[ 7], 14, 0x676F02D9);
        GG(w[12], 20, 0x8D2A4C8A);

        //rOUND 3

        HH(w[ 5],  4, 0xFFFA3942);
        HH( w[ 8], 11, 0x8771F681);
        HH(w[11], 16, 0x6D9D6122);
        HH(w[14], 23, 0xFDE5380C);
        HH(w[ 1],  4, 0xA4BEEA44);
        HH(w[ 4], 11, 0x4BDECFA9);
        HH(w[ 7], 16, 0xF6BB4B60);
        HH(w[10], 23, 0xBEBFBC70);
        HH(w[13],  4, 0x289B7EC6);
        HH(w[ 0], 11, 0xEAA127FA);
        HH(w[ 3], 16, 0xD4EF3085);
        HH(w[ 6], 23, 0x04881D05);
        HH(w[ 9],  4, 0xD9D4D039);
        HH(w[12], 11, 0xE6DB99E5);
        HH(w[15], 16, 0x1FA27CF8);
        HH(w[ 2], 23, 0xC4AC5665);

        //EOUND 4

        II(w[ 0],  6, 0xF4292244);
        II(w[ 7], 10, 0x432AFF97);
        II( w[14], 15, 0xAB9423A7);
        II(w[ 5], 21, 0xFC93A039);
        II(w[12],  6, 0x655B59C3);
        II(w[ 3], 10, 0x8F0CCC92);
        II(w[10], 15, 0xFFEFF47D);
        II(w[ 1], 21, 0x85845DD1);
        II(w[ 8],  6, 0x6FA87E4F);
        II(w[15], 10, 0xFE2CE6E0);
        II(w[ 6], 15, 0xA3014314);
        II(w[13], 21, 0x4E0811A1);
        II(w[ 4],  6, 0xF7537E82);
        II(w[11], 10, 0xBD3AF235);
        II(w[ 2], 15, 0x2AD7D2BB);
        II(w[ 9], 21, 0xEB86D391);
 
     a=a+vector[0];
     b=b+vector[1];
     c=c+vector[2];
     d=d+vector[3];

// because we may have n-number of 512 bit blocks. so vectors need to be updated after each iteration
      vector[0] = a;
      vector[1] = b;
      vector[2] = c;
      vector[3] = d;
  
    }

    *((unsigned long int*)digest) = a;
    *((unsigned long int*)(digest + 4)) = b;
    *((unsigned long int*)(digest + 8)) = c;
    *((unsigned long int*)(digest + 12)) = d;
    
   

    }

    void printHash()
    {
      int i=0;

      cout<<"\nTHE Hash is: 0x";
      for(i=0;i<16;i++){
      printf("%02x",digest[i]);
      }
    }

 

    int stringlength(char str[])
    {   int count=0;

  while(str[count]!='~')
  {
      count++;
  }
  return count;

    }
         
};


void md5_hash(MD5* obj,char *filename)
{    
      unsigned char * DIGEST;
      int i=0;

      //clrscr();

      obj->getdata(filename);                         //GETDATA FROM USER
      obj->print();  
      obj->divideintoblocksof512();           //DIVIDE THE DATA INTO blocks of 512bits
      
     


      obj->padding();
      

      obj->appendsize();
      
      obj->Hash();
     
     

      

}

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
  long double M[16];
  long double C[16];
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
  void SetPrimeNos()
  { 
    int temp;
  
    srand (time(NULL));
    printf("\n\nEnter 1st Prime Number:");
    scanf("%d",&temp);

    p = (int)temp;

    printf("\nEnter 2nd Prime Number:");
    scanf("%d",&temp);

    q = (int)temp;
  
    //set p<q
    if((int)p>(int)q){temp=(int)p;p=(int)q;q=(int)temp;}

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
                                    //    7 | 24  | 3
                                    //      | 21  | 
                                    //     =============
                                    //        3  | 7  | 2
                                    //           | 6  |
                                    //     ==============
                                    //             1 | 3 | 3
 
       if(remainder==0) break;                                  //                   | 3 | 
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
    {                   // another way of choosing e is selecting a prime number from a1 or a2 array
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
//      if((int)(e*d) % (int)n == 1) break;

    }
    
    temp=e;
    e=d;
    d=temp;

    printf("\n++++++ PUBLIC KEY (e) ++++++++");
    printf("\n++++++      %d        ++++++++",(int)e);
    
    printf("\n\n++++++ PRIVATE KEY (d) +++++++");
    printf("\n++++++      %d        ++++++++",(int)d);
    

  } 
  void get_ed()
  { 
    int temp;
    printf("\nEnter PUBLIC KEY (e) of the SENDER:");
    scanf("%d",&temp);

    e = (int)temp;

  }
 /* void getdata()
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
  //  printf("\n========Entered Ciphertext (D) is:%d",C);

  }
  */ 
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



 void encryptRSA(MD5 *objM)
 {
    //getdata(objM);
     int i;

    //unsigned int x;
    

    printf("\nHash: 0x");    //M must be leass than n;
    
    for(i=0;i<16;i++){
      printf("%02x", (int)objM->digest[i]);
    }
        

    printf("\nEncrypted Hash:");    //M must be leass than n;

    for(i=0;i<16;i++){

       M[i] = (int)objM->digest[i];
       C[i] = power_mod(M[i],d);    //encrypt using priate key is necessary in DS!

       printf(" %d", (int)C[i]);
    }
    //printf("\nEntered PlainText (M) is :%d",(int)M);
    //printf("\nvalue of e is :%d",(int)e);
    // M = ( long double) M;
    
    

    // find power easily; using eulers theorem
    // eulersformula(C,d);

    //printf("\npow(M,e)=%d", ( long double)pow(M,e));

    //printf("CipherText:%d",(int)C);
 }
  

  void decryptRSA(MD5 *objM){
     
    int i;
    printf("\nHash: 0x");    //M must be leass than n;
    
    for(i=0;i<16;i++){
      printf("%02x", (int)objM->digest[i]);
    }
        

    printf("\nDecrypted Hash:");    //M must be leass than n;

    for(i=0;i<16;i++){

       //C[i] = (int)objM->digest[i];
       M[i] = power_mod(C[i],e);

       printf("%02x", (int)M[i]);
    }
  }
 

};


void rsa_algorithm(RSA *obj, MD5 *objM, char x)
{
  
    //GENERATE PRIME NUMBERS;
    x=='s'?obj->GenerateRandomPrimeNos():obj->SetPrimeNos() ;
    
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
    
    x=='s'?obj->set_ed():obj->get_ed();
    
    //ENCRYPT OR DECYPT;
    //obj->encryptRSA();
    x=='s'?obj->encryptRSA(objM):obj->decryptRSA(objM);

    

    

}

void appendencryptedhashtofile(RSA *obj)
{
   fstream fp;
   fp.open("hash.txt",ios::out);

   //printf("\nEncrypted Hash before writing to file: ");
   for(int i=0;i<16;i++)
   {
     nmbobj.number=(int)obj->C[i];
   //  printf("%d ",(int)nmbobj.number );
     fp.write((long double*)&nmbobj,sizeof(nmb));

    }
   fp.close();
}

void readencryptedhashfromfile(RSA *obj)
{
   fstream fp;
   fp.open("hash.txt",ios::in);
   
   //printf("\nEncrypted Hash after writing to file: ");
   for(int i=0;i<16;i++)
   {
     fp.read((long double*)&nmbobj,sizeof(nmb));

     obj->C[i]=(int)nmbobj.number;
     
     //printf("%d ",(int)nmbobj.number);
  }
   
   /*for(int i=0;i<16;i++)
   {
    printf(",%02x",obj->digest[i]);
   } 
   */


   fp.close();
}

void checkvalidity(RSA *obj1, MD5 *obj2)
{
  int i=0;
  int flag=1;

  for(i=0;i<16;i++)
  {
    if((int)obj1->M[i]!=(int)obj2->digest[i])
    {
      flag=0;
    }
  }
  if(flag==0)
    {printf("\n\nDIGITAL SIGNATURE IS NOT VALID!");}
else
    {printf("\n\nDIGITAL SIGNATURE IS VALID!");}

}
int main()
{
  int i=0;
  int choice;

  FILE *fp;
   


  do{
   // system("cls");
    printf("\n         1. GENERATION \n         2. VERIFICATION \n         3. Exit\n\n         Enter Choice:");
    scanf("%d",&choice);

    if(choice==1)
      {
      //GENERATION OF DS.
        MD5 objSENDERmd5;RSA objSENDERrsa;
        //Step1: Calculate MD5 using written algorithm
        md5_hash(&objSENDERmd5, "inputfile.txt"); //hash will be stored in digest[[ array]] ob objSENDER object, which is public
  
        //Step2:Append the hash to the inputfile.txt file
        rsa_algorithm(&objSENDERrsa, &objSENDERmd5,'s');
 
        //Step3:Append the hash to the inputfile.txt file
        appendencryptedhashtofile(&objSENDERrsa);
      }
    else if(choice==2){
      MD5 objRECEIVERmd5;
      RSA objRECEIVERrsa;
 
      //VERIFICATION OF DS

      //Step 1---
      md5_hash(&objRECEIVERmd5, "inputfile.txt"); //hash will be stored in digest[[ array]] ob objRECEIVER object, which is public
  
      //STEP 2---
      readencryptedhashfromfile(&objRECEIVERrsa);   //encrypted hash is stored in C[i] of this object
   
      //STEP 3---REVERSE PROCESS OF RSA i.,e decryption
      rsa_algorithm(&objRECEIVERrsa, &objRECEIVERmd5,'r');    //decrtytpted hash is stored in M[i] of this object

      //Step4:
      checkvalidity(&objRECEIVERrsa,&objRECEIVERmd5);

      

    }
    else if(choice==3){printf("\nEXITTING....");break;}
    else{printf("\nWRONG Choice...");}
    
  }while(choice!=3);

  
  
 
 

  
    
     //while(choice!=3)
  //if("tt"=="tt") printf("Yes");
  return 0;
     
}
