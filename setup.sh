#!/usr/bin/env bash

if [ -d _build ]
then
rm build -rf
fi

mkdir _build
cd _build
cmake ..
cd ..