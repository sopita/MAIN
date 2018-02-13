//
//  Unitval.cpp
//  Project_Main
//
//  Created by andres quiroz on 13/02/2018.
//  Copyright © 2018 andres quiroz. All rights reserved.
//

#include <stdio.h>
#include "Unitval.hpp"

/*class Unitval {
 public:
 float & get_valLine();
 void set_valLine(float x);
 private:
 float valLine;
 };*/

float Unitval::get_valLine(){
    return this->valLine;
}

void Unitval::set_valLine(float x){
    this->valLine=x;
}