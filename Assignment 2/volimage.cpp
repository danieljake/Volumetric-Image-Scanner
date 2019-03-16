//
//  volimage.cpp
//  Assignment 2
//
//  Created by Daniel Servant on 2019/03/13.
//  Copyright © 2019 Daniel Servant. All rights reserved.
//

#include "volimage.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

bool SRVDAN001::VolImage::readImages(std::string baseName){
    int _width,_height;//iterators for width and height of each individual image
    int iterator=0;
    std::ifstream* _ifs;
    std::ifstream ifs((baseName +".data"));
    _ifs = &ifs;
    SRVDAN001::printError(_ifs, baseName, ".data");
    //pipe information from ifstream to program variables, consuming whitespace
    ifs>>width>>std::ws;
    ifs>>height>>std::ws;
    ifs>>numImages>>std::ws;
    ifs.close();
    //loop through all images in stack
    while(iterator<numImages){
        std::ostringstream ss; ss<<iterator;
        std::ifstream infile(baseName +".raw",std::ios::binary);
        _ifs = &infile;
        SRVDAN001::printError(_ifs, baseName, ".raw");
        byteArray** bytes = new byteArray*[height];
        size+=sizeof(bytes);
        //loop through height of .raw file (column of byte array)
        _height =0;
        while(_height<height){
            bytes[_height]= new byteArray[width];
            size += sizeof(bytes[height]);
            //loop through width of .raw file (row of byte array)
            _width=0;
            while(_width<width){
                if(ifs.eof()==false){
                    size +=1;
                    //convert to char from unsigned char for the read method that follows
                    char* ptr = (char*) &bytes[_height][_width];
                    ifs.read(ptr,1);
                }
                _width++;
            }
            _height++;
        }
        iterator++;
        ifs.close();
        slices.push_back(bytes);
    }
    return true;
}
void SRVDAN001::printError(std::ifstream * _ifs,std::string prefix, std::string extension){
    if(!(*_ifs)){
        std::cout << "Unable to open " << extension << " file " << prefix << "." << std::endl;
    }
    
}
