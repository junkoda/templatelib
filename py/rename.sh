#!/bin/sh

# Replace library name to
name=newnamelib



for file in Makefile setup.py py_package.cpp .gitignore `ls templatelib/*.py`
do
  sed -i .bak "s/templatelib/$name/g" $file
done

mv templatelib $name

# Original files are renamed with .bak
# To erase bak files
# rm *.bak $name/*.bak
