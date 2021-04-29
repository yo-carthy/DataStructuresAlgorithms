#include <iostream>
#include <vector>
#include <string>

using namespace std;

void addZeros(string &num1, string&num2){
    int l1 = num1.size();
    int l2 = num2.size();
    if(l1 > l2){
        for(int i = 0; i < l1 - l2; i++){
            num2 = ('0' + num2);
        }
    }else{
        for(int i = 0; i < l2 - l1; i++){
            num1 = ('0' + num1);
        }
    }
}

string stringPlus(string num1, string num2){
    int carrier = 0;
    int bitresult = 0;
    string fullResult;
    string finalResult;
    addZeros(num1,num2);
    for(int i =0; i < num1.size(); i++){
        bitresult = num1[num1.size()-i-1] - '0' + num2[num2.size()-i-1] - '0' + carrier;
        carrier = 0;
        if(bitresult > 9){
            carrier = 1;
            bitresult = bitresult - 10;
        }
        fullResult.push_back(bitresult+'0');
    }
    if(carrier == 1)fullResult.push_back('1');
    for(int i = 0; i < fullResult.size(); i++){
        finalResult.push_back(fullResult[fullResult.size()-i-1]);
    }
    //finalResult.push_back('\0');
    int pos = finalResult.find_first_not_of('0');
    if(pos!=string::npos)finalResult = finalResult.substr(pos, finalResult.size()-pos);
    else finalResult = "0";
    return finalResult;
}

string stringMinus(string num1, string num2){
    int carrier = 0;
    int bitresult = 0;
    string fullResult;
    string finalResult;
    addZeros(num1,num2);
    for(int i =0; i < num1.size(); i++){
        bitresult = num1[num1.size()-i-1] -  num2[num2.size()-i-1] - carrier;
        carrier = 0;
        if(bitresult < 0){
            carrier = 1;
            bitresult = bitresult + 10;
        }
        fullResult.push_back(bitresult+'0');
    }
    for(int i = 0; i < fullResult.size(); i++){
        finalResult.push_back(fullResult[fullResult.size()-i-1]);
    }
    //finalResult.push_back('\0');
    int pos = finalResult.find_first_not_of('0');
    if(pos!=string::npos)finalResult = finalResult.substr(pos, finalResult.size()-pos);
    else finalResult = "0";
    return finalResult;
}

string karatsuba(string num1, string num2){
    if(num1.length() == 1 || num2.length() ==1){
        return to_string(atoi(num1.c_str()) * atoi(num2.c_str()));
    }else{
        addZeros(num1,num2);
        string a, b, c, d;
        a = num1.substr(0,num1.size()/2 + num1.size()%2);
        b = num1.substr(num1.size()/2 + num1.size()%2, num1.size()/2);
        c = num2.substr(0,num2.size()/2 + num2.size()%2);
        d = num2.substr(num2.size()/2 + num2.size()%2, num2.size()/2);
        string ac = karatsuba(a,c);
        string bd = karatsuba(b,d);
        string acPlusbd= stringPlus(ac,bd);
        string adPlusbc = karatsuba(stringPlus(a,b),stringPlus(c,d));
        adPlusbc = stringMinus(adPlusbc, acPlusbd);
        cout<<" ac: "<<ac<<" adPlusbc: "<<adPlusbc<<":"<<" bd: "<<bd<<" final: "<<stringPlus(stringPlus(ac,adPlusbc),bd)<<endl;
        int bigOrder = num1.size()/2 * 2;
        int smallOrder = num1.size()/2 ;
        for(int i = 0; i < bigOrder; i++){
            ac = ac + '0';
        }
        for(int i = 0; i < smallOrder; i++){
            adPlusbc = adPlusbc + '0';
        }
        cout<<" A: "<<a<<" B: "<<b<<":"<<" C: "<<c<<" D: "<<d<<endl;
        cout<<" ac: "<<ac<<" adPlusbc: "<<adPlusbc<<":"<<" bd: "<<bd<<" final: "<<stringPlus(stringPlus(ac,adPlusbc),bd)<<endl;
        return stringPlus(stringPlus(ac,adPlusbc),bd);
    }
}

int main()
{
    string a = "3141592653589793238462643383279502884197169399375105820974944592";
    string b = "2718281828459045235360287471352662497757247093699959574966967627";
    addZeros(a,b);
    cout<< "a+b =";
    cout <<karatsuba(a,b);
}
