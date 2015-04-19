//
//  ConsoleController.m
//  DollEngine
//
//  Created by DollStudio on 15/4/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "ConsoleController.h"

@interface ConsoleController ()

@end

@implementation ConsoleController

static ConsoleController* s_instance=nil;

+(ConsoleController*)GetInstance
{
    if (s_instance==nil) {
        s_instance = [[ConsoleController alloc] initWithWindowNibName:@"ConsoleController"];
        [s_instance.window close];
    }
    return s_instance;
}

- (void)windowDidLoad {
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

@end
