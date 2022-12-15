#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        unsigned long long w[5]; //array of values after conversion
        w[0] = 0;
        w[1] = 0;
        w[2] = 0;
        w[3] = 0;
        w[4] = 0;
        int S = k.length();
      
        if(S <= 6 ){ // only block 0
        
        for(int i = S - 1; i >= 0; --i){
           w[4] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-1 - i) );
        }
        
        }
        else if( S <= 12 &&  S >= 7){ // blocks 0,1

        for(int i = S - 1; i >= S - 6; --i){
           w[4] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-1 - i) );
        }

        for(int i = S - 7; i >= 0; --i){
           w[3] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-7 - i) );
        }
      
        //std::cout << w[4] << std::endl;
        //std::cout << w[3] << std::endl;

        }
        else if( S <= 18 &&  S >= 13){ // blocks 0,1,2

        for(int i = S - 1; i >= S - 6; --i){
           w[4] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-1 - i) );
        }

        for(int i = S - 7; i >= S - 12; --i){
           w[3] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-7 - i) );
        }

        for(int i = S - 13; i >= 0; --i){
           w[2] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-13 - i) );
        }
 

        }
        else if( S <= 24 &&  S >= 19){ // blocks 0,1,2,3

        for(int i = S - 1; i >= S - 6; --i){
           w[4] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-1 - i) );
        }

        for(int i = S - 7; i >= S - 12; --i){
           w[3] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-7 - i) );
        }

        for(int i = S - 13; i >= S-18; --i){
           w[2] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-13 - i) );
        }

        for(int i = S - 19; i >= 0; --i){
           w[1] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-19 - i) );
        }
 


        }
        else if(S > 24){ // All blocks
        
        for(int i = S - 1; i >= S - 6; --i){
           w[4] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-1 - i) );
        }

        for(int i = S - 7; i >= S - 12; --i){
           w[3] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-7 - i) );
        }

        for(int i = S - 13; i >= S-18; --i){
           w[2] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-13 - i) );
        }

        for(int i = S - 19; i >= S-24; --i){
           w[1] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-19 - i) );
        }
        
        for(int i = S - 25; i >= 0; --i){
           w[0] += letterDigitToNumber(k[i]) * (unsigned long long)pow(36, (S-25 - i) );
        }
        //std::cout << w[0] << std::endl;
        //std::cout << w[1] << std::endl;
        //std::cout << w[2] << std::endl;
        //std::cout << w[3] << std::endl;
        //std::cout << w[4] << std::endl;

 
        }

        unsigned long long sol = 0;
        for(int i = 0; i < 5; i++){
            sol += rValues[i] * w[i];
        }
        return sol;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if((int)letter >= 48 && (int)letter <= 57 ){ // if number 
            return ((int)letter - 22);
        }
        else if((int)letter >= 65 && (int)letter <= 90 ){ // if uppercase letter
            return ((int)letter - 65);
        }
        else  // if lowercase letter
            return ((int)letter - 97);
        

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
