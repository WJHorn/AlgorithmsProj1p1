// Standard libraries
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h> 


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

// Fermat test to be used with bigUnsigned integers
bool Fermat(BigUnsigned big) {
   //if the bigUnsigned value is 1, return false
   if (big == 1)
      return false;
   //test three random values to see if the number is mostly prime
   for (int i = 0; i < 3; i++) {
      BigInteger a = (rand()% 4000);
      if (modexp(a, (big - 1), big) != 1)
         return false;
   }
   return true;
}

int main(){
   try {
      //generation block
   ///////////////////////////////////////////////////

      //generate p
      BigUnsigned p = BigUnsigned(1);
      for (int i = 0; i < 400; i++) {
         p = p * 10 + rand();
      }
      //use Fermat test if p is prime
      //if it is not then re-generate p until it is
      while(!(Fermat(p))) {
         std::cout << "Working...\n";
         p = 0;
         for (int i = 0; i < 400; i++) {
            p = p * 10 + rand();
         }
      }
      std::cout << "Generated prime p... \n";

      //generate initial q
      BigUnsigned q = BigUnsigned(1);
      for (int i = 0; i < 400; i++) {
         q = q * 10 + rand();
      }
      //use Fermat test if q is prime
      //if it is not, then re-generate q until it is
      while (!(Fermat(q))){
         std::cout << "Working...\n";
         q = 0;
         for (int i = 0; i < 400; i++) {
            q = q * 10 + rand();
         }
      }
      std::cout << "Generated prime q... \n";

      //generate n
      BigUnsigned n = BigUnsigned(p * q);
      std::cout << "Generated n...\n";

      //generate nPhi
      BigUnsigned nPhi = BigUnsigned((p - 1) * (q - 1));
      std::cout << "Generated nPhi...\n";

      //generate initial e
      BigUnsigned e = BigUnsigned(3);
      //test if e is relatively prime to nPhi
      //if it is not, try the next odd number
      while (gcd(nPhi, e) != 1) {
         e = e + 2;
      }
      std::cout << "Generated e...\n";

      //generate d as the multiplicative inverse of e, modulo nPhi
      BigUnsigned d = modinv(e, nPhi);
      std::cout << "Generated d...\n\n";

      //output block
   /////////////////////////////////////////////////////

      //turn p and q into strings
      std::string pval = bigUnsignedToString(p);
      std::string qval = bigUnsignedToString(q);
      //output p and q into a text file
      std::ofstream pqfile("p_q.txt");
      pqfile << pval << std::endl << qval;
      pqfile.close();

      //turn n into a string
      std::string nval = bigUnsignedToString(n);
      //turn e and d into strings
      std::string eval = bigUnsignedToString(e);
      std::string dval = bigUnsignedToString(d);
      //output e and n into a text file
      std::ofstream enfile("e_n.txt");
      enfile << eval << std::endl << nval;
      enfile.close();
      //output d and n into a text file
      std::ofstream dnfile("d_n.txt");
      dnfile << dval << std::endl << nval;
      dnfile.close();

      std::cout << "Complete!\n";

	} catch(char const* err) {
		std::cout << "\n\nThe system threw an exception: \n\n"
			<< err << std::endl << std::endl;
	}

	return 0;
}
