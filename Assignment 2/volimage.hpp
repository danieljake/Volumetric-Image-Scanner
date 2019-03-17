//
//  volimage.hpp
//  Assignment 2
//
//  Created by Daniel Servant on 2019/03/13.
//  Copyright © 2019 Daniel Servant. All rights reserved.
//

#ifndef volimage_hpp
#define volimage_hpp
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

typedef unsigned char byteArray;// unsigned char f(or 2D array)


namespace SRVDAN001 {
    static int numImages=0;//number of images in stack
    static int size=0;
    //return number of images in stack.
    int returnNoImages(void);
    //method for printing error messages relating to files that are unable to be opened for ifstream
    void printError(std::ifstream * ifs,std::string prefix,std::string extension);
    //Overloaded method for printing error messages relating to files that are unable to be opened for ofstream
    void printError(std::string prefix,std::string extension);
    //method for writing to output
    void writeOut(std::ofstream * _ofs,std::string prefix, std::string extension,int width, int height, int number);
    
    class VolImage
    {
    private: // private members
        int width, height; // width and height of image stack std::vector<unsigned char**> slices; // data for each slice, in order
        std::vector<unsigned char**> slices;
    public: // public members
        void extractWithG(int rowID, std::string output_prefix);
        VolImage(); // default constructor - define in .cpp
        ~VolImage(); // destructor - define in .cpp file
        // populate the object with images in stack and //set member variables define in .cpp
        bool readImages(std::string baseName);
        // compute difference map and write out;  define in .cpp
        void diffmap(int sliceI, int sliceJ, std::string output_prefix); // extract slice sliceId and write to output - define in .cpp
        void extract(int sliceId, std::string output_prefix);
        // number of bytes uses to store image data bytes //and pointers (ignore vector<> container, dims etc) int volImageSize(void); // define in .cpp
        int volImageSize(void); // define in .cpp
    };
}


#endif /* volimage_hpp */
