#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DEC="$DIR"
cd "$DEC"

rm -rf build-DollEngine-Desktop_Qt_5_4_1_clang_64bit-Debug/DollEngine.app/Contents/MacOS/data
cp -r Resource/data build-DollEngine-Desktop_Qt_5_4_1_clang_64bit-Debug/DollEngine.app/Contents/MacOS