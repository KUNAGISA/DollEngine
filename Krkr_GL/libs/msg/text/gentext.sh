#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd "$DIR"
echo "============================"
echo "Begin"
echo "Parse CSV..."
perl gentext.pl
echo "Copy File..."
cp tjsErrorInc.h ../../../scripts/tjs2/tjsErrorInc.h
cp MsgLoad.cpp ../mac/MsgLoad.cpp
cp string_table_en.h ../mac/string_table_en.h
cp string_table_jp.h ../mac/string_table_jp.h
cp string_table_resource.h ../mac/string_table_resource.h
echo "End"
echo "============================"
