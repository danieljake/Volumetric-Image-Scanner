#!/bin/bash
for file in *.raw ; do mv $file ${file//MRI/scan} ; done
for file in *.data ; do mv $file ${file//MRI/scan} ; done