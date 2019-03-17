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
SRVDAN001::VolImage::VolImage(){
    width=0;
    height=0;
}
void SRVDAN001::VolImage::extractWithG(int rowID, std::string output_prefix){
    std::ofstream fileOut(output_prefix + ".data");
    std::ofstream * _fileOut = &fileOut; //pointer to point to ofstream object to pass to function
    SRVDAN001::writeOut(_fileOut, output_prefix, ".data", width, height, 1);
    fileOut.close();
    size=0;
    int _width=0,_number=0,iterator=0;;//iterators for width and height of each individual image
    fileOut.open(output_prefix +".raw",std::ios::binary);
    if(fileOut.is_open()){
        _number=0;
        while (_number<SRVDAN001::numImages) {
            _width=0;
            while (_width<width) {
                fileOut << slices[_number][rowID][_width];
                size+=sizeof(slices[_number][rowID][_width]);
                _width++;
            }
            _number++;
        }
        fileOut.close();
    }
    else{
        SRVDAN001::printError(output_prefix, ".raw");
    }
       SRVDAN001::numImages=1;
}

void SRVDAN001::VolImage::extract(int sliceId, std::string output_prefix){
    std::ofstream fileOut(output_prefix + ".data");
    std::ofstream * _fileOut = &fileOut; //pointer to point to ofstream object to pass to function
    SRVDAN001::writeOut(_fileOut, output_prefix, ".data", width, height, 1);
    fileOut.close();
    size=0;
    int _width,_height,iterator=0;;//iterators for width and height of each individual image
    fileOut.open(output_prefix +".raw",std::ios::binary);
    if(fileOut.is_open()){
        _height=0;
        while (_height<height) {
            _width=0;
            while (_width<width) {
                fileOut << slices[sliceId][_height][_width];
                size+=sizeof(slices[sliceId][_height][_width]);
                _width++;
            }
            _height++;
        }
        fileOut.close();
    }
    else{
        SRVDAN001::printError(output_prefix, ".raw");
    }
    SRVDAN001::numImages=1;
}

void SRVDAN001::VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
    std::ofstream fileOut("/Users/danielservant/Documents/Xcode Projects/CSC3020H Assignment 2/brain_mri_raws/" +output_prefix + ".data");
    std::ofstream * _fileOut = &fileOut; //pointer to point to ofstream object to pass to function
    SRVDAN001::writeOut(_fileOut, output_prefix, ".data", width, height, 1);
    fileOut.close();
    size=0;
    int _width,_height,iterator=0;;//iterators for width and height of each individual image
    fileOut.open(output_prefix +".raw",std::ios::binary);
    if(fileOut.is_open()){
        _height=0;
        while (_height<height) {
            _width=0;
            while (_width<width) {
                byteArray bNew = (byteArray) abs((int)((float) slices[sliceI][_height][_width]-(float) slices[sliceJ][_height][_width]))/2;
                size+=sizeof(bNew);
                fileOut << bNew;
                _width++;
            }
            _height++;
        }
        fileOut.close();
    }
    else{
        SRVDAN001::printError(output_prefix, ".raw");
    }
    SRVDAN001::numImages=1;
    

}

SRVDAN001::VolImage::~VolImage(){
    int index=0,second=0;
    while (index<slices.size()) {
        second=0;
        while (second<height) {
            delete [] slices[index][second];
            second++;
        }
        delete [] slices[index];
        index++;
    }
}

bool SRVDAN001::VolImage::readImages(std::string baseName){
    int _width,_height;//iterators for width and height of each individual image
    int iterator=0;
    std::ifstream* _ifs;
    std::ifstream ifs(("/Users/danielservant/Documents/Xcode Projects/CSC3020H Assignment 2/brain_mri_raws/" +baseName +".data"));
    _ifs = &ifs;
    SRVDAN001::printError(_ifs, baseName, ".data");
    //pipe information from ifstream to program variables, consuming whitespace
    ifs>>width>>std::ws;
    ifs>>height>>std::ws;
    ifs>>SRVDAN001::numImages>>std::ws;
    ifs.close();
    //std::cout << "\nwidth: " << width << "\nHeight: " << height << "\n " << numImages;
    //loop through all images in stack
    while(iterator<SRVDAN001::numImages){
        std::ostringstream stream; stream<<iterator;
        std::ifstream ifs(("/Users/danielservant/Documents/Xcode Projects/CSC3020H Assignment 2/brain_mri_raws/" +baseName + stream.str() +".raw"),std::ios::binary);
        _ifs = &ifs;
        SRVDAN001::printError(_ifs, baseName, ".raw");
        byteArray** bytes = new byteArray*[height];
        size+=sizeof(bytes);
        //loop through height of .raw file (column of byte array)
        _height =0;
        while(_height<height){
            bytes[_height]= new byteArray[width];
            //std::cout << "Memory contents at address " << &bytes[_height] << ": " <<bytes[_height] << std::endl;
            size += sizeof(bytes[_height]);
            //loop through width of .raw file (row of byte array)
            _width=0;
            while(_width<width){
                if(ifs.eof()==false){
                    size +=1;
                    char * ptr = (char *) &bytes[_height][_width];
                    //std::cout << "Memory contents at address " << &bytes[_height][_width] << ": " <<bytes[_height] << std::endl;
                    ifs.read(ptr,1);
                    
                }
                _width++;
            }
            _height++;
        }
        iterator++;
        ifs.close();
        slices.push_back(bytes);
        //SRVDAN001::numImages=SRVDAN001::numImages;
        
    }
    
    return true;
}

int SRVDAN001::VolImage::volImageSize(void){
    return SRVDAN001::size;
}
int SRVDAN001::returnNoImages(void){
    return numImages;
}
void SRVDAN001::printError(std::ifstream * _ifs,std::string prefix, std::string extension){
    if(!(*_ifs)){
        std::cout << "There is an error opening " << "file with extension " << extension << " called " << prefix << "." << std::endl;
    }
}
void SRVDAN001::printError(std::string prefix, std::string extension){
    std::cout << "There is an error opening " << "file with extension " << extension << " called " << prefix << "." << std::endl;
}
void SRVDAN001::writeOut(std::ofstream * _ofs,std::string prefix, std::string extension,int width, int height,int number){
    if(((*_ofs).is_open())){
        (*_ofs) << width;
        (*_ofs) << " ";
        (*_ofs) << height;
        (*_ofs) << " ";
        (*_ofs) << number;
    }
    else{
        std::cout << "There is an error opening " << "file with extension " << extension << " called " << prefix << "." << std::endl;
    }
    
}
