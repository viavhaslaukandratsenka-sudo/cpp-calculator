#include <iostream>
#include "calculator.h"
#include <string>
#include <cmath>
#include <limits>
using namespace std;

bool ReadNumber(Number& result){
    if(!(cin >> result)){
        cerr<<"Error: Numeric operand expected"<<endl;
        return false; 
    }
    return true; 
}

bool RunCalculatorCycle(){
    string command;
    Number current_number = 0; 
    Number saved_number = 0; 
    bool number_is_saved = false;

    if(!(ReadNumber(current_number))){
        return false;
    }
    while (cin>>command){
        if(command == "s"){
            saved_number = current_number;
            number_is_saved = true;
        }
        else if(command == "l"){
            if(number_is_saved){
                current_number = saved_number;
            }
            else{
                cerr<<"Error: Memory is empty"<<endl;
                return false;
            }
        }
        else if(command == "+"){
            Number user_number = 0; // число введённое пользователем
            if(!(ReadNumber(user_number))){ 
                return false;
            }
            current_number += user_number;
        }
        else if(command == "-"){
            Number user_number = 0;
            if(!(ReadNumber(user_number))){
                return false;
            }
            current_number -= user_number;
        }
        else if(command == "*"){
            Number user_number = 0;
            if(!(ReadNumber(user_number))){
                return false;
            }
            current_number *= user_number;
        }
        else if(command == "/"){
            Number user_number = 0;
            if(!(ReadNumber(user_number))){
                return false;
            }
            if(user_number == 0){
                current_number = numeric_limits<Number>::infinity();
                continue;
                cout<<"inf"<<endl;
            }
            else{
                current_number /= user_number;
            } 
        }
        else if(command == ":"){
            Number user_number = 0;
            if(!(ReadNumber(user_number))){       
            return false;
            }
            current_number = user_number;
        }
        else if(command == "c"){
            current_number = 0;
        }
        else if(command == "**"){
            Number user_number = 0;
            if(!(ReadNumber(user_number))){
                return false;
            }
            current_number = pow(current_number, user_number);
        }
        else if(command == "="){
            cout<<current_number<<endl;
        }
        else if(command == "q"){
            break;
        }
        else{
            cerr<<"Error: Unknown token "<<command<<endl;
            return false;
        }
    }
    return true;
}
