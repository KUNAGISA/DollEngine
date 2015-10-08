//
//  main.m
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>

int main(int argc, const char * argv[]) {
    int ret=0;
    @try {
        ret = NSApplicationMain(argc, argv);
    }
    @catch (NSException *exception) {
        NSLog(@"%@",exception);
    }
    @finally {
        NSLog(@"catch some");
    }
    return ret;
}
