//
//  ConsoleController.m
//  DollEngine
//
//  Created by DollStudio on 14/12/21.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import "ConsoleController.h"
//#include "StringUtils.h"
//#include "Scripts.h"

@interface ConsoleController ()

@end

@implementation ConsoleController

-(void)windowDidLoad
{
    [super windowDidLoad];
    [self.logView setEditable:NO];
    self.logView.backgroundColor = [NSColor blackColor];
    input.delegate = self;
}

-(void)pushLog:(const char*)text
{
    if (!text) {
        return;
    }
    NSString* ustr = [NSString stringWithUTF8String:text];
    
    NSFont *font = [NSFont fontWithName:@"Monaco" size:14.0];
    
    NSDictionary *attrsDictionary =
    [NSDictionary dictionaryWithObject:font
                                forKey:NSFontAttributeName];
    BOOL hasColor = NO;
    if (*text == '(' && *(text+1) == '#')
    {
        char* ntext = (char*)text+2;
        while (*ntext != '\0')
        {
            if (*ntext == ')' && *(ntext+1) == '@')
            {
                hasColor = YES;
//                [attrsDictionary setValue:[NSColor redColor] forKey:(NSString *)kCTForegroundColorAttributeName];
//                [string addAttribute:(NSString *)kCTForegroundColorAttributeName
//                               value:(id)[NSColor redColor]
//                               range:NSMakeRange(0, string.length-1)];
                break;
            }
            ++ntext;
        }
    }
    NSMutableAttributedString* string = [[NSMutableAttributedString alloc] initWithString:ustr attributes:attrsDictionary];
    if (hasColor)
    {
        [string addAttribute:NSForegroundColorAttributeName value:[NSColor grayColor] range:NSMakeRange(0, ustr.length)];
        
    }
    else
    {
        [string addAttribute:NSForegroundColorAttributeName value:[NSColor whiteColor] range:NSMakeRange(0, ustr.length)];
    }
    
//    NSMutableAttributedString *string =
//    [[NSMutableAttributedString alloc]
//     initWithString:ustr
//     attributes:attrsDictionary];
////    NSMutableAttributedString* outString;
//    if (*text == '(' && *(text+1) == '#')
//    {
//        char* ntext = (char*)text+2;
//        while (*ntext != '\0')
//        {
//            if (*ntext == ')' && *(ntext+1) == '@')
//            {
//                [string addAttribute:(NSString *)kCTForegroundColorAttributeName
//                               value:(id)[NSColor redColor]
//                               range:NSMakeRange(0, string.length-1)];
//                break;
//            }
//            ++ntext;
//        }
//    }
    
    NSTextStorage *storage = [self.logView textStorage];
    [storage beginEditing];
    [storage appendAttributedString:string];
    [storage endEditing];
    
    [self.logView scrollRangeToVisible: NSMakeRange(self.logView.string.length, 0)];
}

- (IBAction)onEnterClick:(id)sender {
    wstring code;
    StringUtils::ConvertUtf8ToUnicode(input.stringValue.UTF8String, code);
    if (code == L"") {
        return;
    }
    Scripts::GetInstance()->eval(code.c_str());
    input.stringValue = @"";
}

-(BOOL)control:(NSControl *)control textShouldEndEditing:(NSText *)fieldEditor
{
    [self onEnterClick:nil];
    return YES;
}

@end
