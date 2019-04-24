# Volumetric Image Manipulation Tool

A volumetric image tool, which can load a “stack” of 2D images and manipulate them as a group. 
Volumetric images are produced by many instruments, including radio astronomy telescopes and MRI machines used in medical imaging.

The program loads a sequence of 2D unsigned byte (values from 0..255) buffers, one for each image slice. These Are provided, as a sequence of binary (“.raw”) files with a header file that provides the image dimensions.
So, for example, an image sequence called “scan” would have a file “scan.dat” (the header file) and a sequence of images numbered as follows: “scan0.raw”, “scan1.raw”, “scan2.raw” etc. You can determine the number of images to open and read by first opening the header file. 
The application is invoked as follows on the command line:

**volimage <imageBase> [-d i j output_file_name] [-x i output_file_name]**

Where <imageBase> is the the prefix for the file sequence ( “scan” in the example) 

1. -d i j output file name: compute a difference map between images i and j, and write this out to file.
2. -x i output file name: extract and write the slice with number i and write this out to file.
