#include<vector>
#include"Algorithms.h"

struct binary{
  LongModInt order;
  int bit;
};

LongModInt montgomeryPower(const LongModInt& number1, const LongModInt& number2){

    std::vector<int> mod=number1.getMod();
    LongModInt result("1",mod),temp=number1,number=number2;
    const int bits=8;
    int length=mod.size()*bits;
    std::vector<binary>number2bin; number2bin.resize(length);
    LongModInt order("2",mod),degree("1",mod);
    int breakpoint=0;

    for(int i(length-1);i>=0;i--){
        number2bin[i].order=degree;
        degree=degree*order;
        number2bin[i].bit=0;
    }

    for(int i(length-1);i>0;i--){
        if(number2bin[i].order>number2bin[i-1].order){
            breakpoint=i;
                break;}
        }

    for(int i(breakpoint);i<length;i++)
        if(number2bin[i].order<=number){
            number2bin[i].bit++;
            number=number-number2bin[i].order;
    }
    for(int i(length-1);i>=breakpoint;i--){
        if(number2bin[i].bit) result=result*temp;
            temp=temp*temp;
    }
    return result;
}
