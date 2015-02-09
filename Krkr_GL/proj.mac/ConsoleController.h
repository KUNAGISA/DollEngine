//
//  ConsoleController.h
//  Krkr_GL
//
//  Created by DollStudio on 14/12/21.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ConsoleController : NSWindowController<NSTextFieldDelegate>
{
    __weak IBOutlet NSTextField *input;
}
@property (assign) IBOutlet NSTextView *logView;

-(void)pushLog:(const char*)text;

- (IBAction)onEnterClick:(id)sender;

@end
