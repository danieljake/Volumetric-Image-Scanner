//
//  main.cpp
//
//  Created by Daniel Servant on 2019/03/13.
//  Copyright © 2019 Daniel Servant. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "volimage.hpp"

int main(int argc, const char * argv[]) {
    SRVDAN001::VolImage firstClass;
    switch (argc) {
        case 2:
        {
            firstClass.readImages(std::string(argv[1]));
            if(SRVDAN001::returnNoImages()>0){
            std::cout << "Number of images: " << SRVDAN001::returnNoImages()<< "\n" << "Number of bytes required: " << firstClass.volImageSize() << std::endl;
            }else{
                std::cout << "Error – Erronous input entered." << std::endl;
            }
        }
            break;
        case 5:
        {
            firstClass.readImages(std::string(argv[1]));
            //check for -x extract
            if(std::string(argv[2])=="-x"){
                int inputInt;
                std::istringstream intStrean(argv[3]);
                intStrean >> inputInt;
                firstClass.extract(inputInt, std::string(argv[4]));
                std::cout << "Number of images: " << SRVDAN001::returnNoImages()<< "\n" << "Number of bytes required: " << firstClass.volImageSize() << std::endl;
            }
            //check for -g extract
            else if(std::string(argv[2])=="-g"){
                int inputInt;
                std::istringstream intStrean(argv[3]);
                intStrean >> inputInt;
                firstClass.extractWithG(inputInt, std::string(argv[4]));
                std::cout << "Number of images: " << SRVDAN001::returnNoImages()<< "\n" << "Number of bytes required: " << firstClass.volImageSize() << std::endl;
                
            }
            else{
                std::cout << "Error – Erronous input entered." << std::endl;
            }
            
            
        }
            break;
        case 6:
        {
            firstClass.readImages(std::string(argv[1]));
            if((std::string(argv[2])=="-d"))
        {
            int input1,input2;
            std::istringstream intStrean(argv[3]);
            intStrean >> input1;
            std::istringstream intStrean2(argv[4]);
            intStrean2 >> input2;
            firstClass.diffmap(input1, input2, std::string(argv[5]));
            std::cout << "Number of images: " << SRVDAN001::returnNoImages()<< "\n" << "Number of bytes required: " << firstClass.volImageSize() << std::endl;
            
        }else{
            std::cout << "Error – Erronous input entered." << std::endl;
        }
        }
            break;
            
        default:
            break;
    }
    
    return 0;
}
