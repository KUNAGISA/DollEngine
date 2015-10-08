//
//  ConsoleController.h
//  DollEngine
//
//  Created by DollStudio on 15/4/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>

@interface ConsoleController : NSWindowController<NSTextFieldDelegate,NSTableViewDataSource,NSTableViewDelegate>
{
//    IBOutlet WebView* output;
    IBOutlet NSTextView* output;
//    IBOutlet NSTextView* output;
    IBOutlet NSTextField* input;
}

+(ConsoleController*)GetInstance;

-(void)pushString:(NSString*)text;

-(void)setVisible:(BOOL)v;

@end
