//
//  ConsoleController.m
//  DollEngine
//
//  Created by DollStudio on 15/4/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "ConsoleController.h"
#include "ScriptEngine.h"
#include "tjs.h"

@interface ConsoleController ()
{
    NSMutableString* outPutString;
    BOOL errorInfo;
}

@end

@implementation ConsoleController

static ConsoleController* s_instance=nil;

+(ConsoleController*)GetInstance
{
    if (s_instance==nil) {
        s_instance = [[ConsoleController alloc] initWithWindowNibName:@"ConsoleController"];
    }
    return s_instance;
}

- (void)windowDidLoad {
    [super windowDidLoad];
    output.editable = NO;
    output.textContainerInset = NSMakeSize(10, 10);
    output.backgroundColor = [NSColor colorWithRed:39/255.0f green:40/255.0f blue:34/255.0f alpha:1];
    errorInfo = NO;
}

-(void)setVisible:(BOOL)v
{
    if (v) {
        [self.window makeKeyAndOrderFront:nil];
    }
    else {
        [self.window orderOut:nil];
    }
}

-(void)pushString:(NSString*)text
{
    if (text == nil ||
        text.length == 0) {
        return;
    }
    NSRange range = NSMakeRange(0, text.length);//范围
    NSFont* font = [NSFont fontWithName:@"Helvetica" size:16];//字体
    NSColor* fcolor;
    
    NSString* substr;
    if (text.length > 8 ) {
        substr = [text substringToIndex:7];
        if ([substr compare:@"【ERROR】"]==NSOrderedSame)
        {
            fcolor = [NSColor colorWithRed:249/255.0f green:16/255.0f blue:59/255.0f alpha:1];
        }
        else {
            fcolor = [NSColor whiteColor];//颜色
        }
    }
    else {
        fcolor = [NSColor whiteColor];//颜色
    }
    NSMutableParagraphStyle* paragraph = [[NSMutableParagraphStyle alloc]init];
    paragraph.lineSpacing = 3;//行间距
    
    NSMutableAttributedString* attr = [[NSMutableAttributedString alloc] initWithString:[NSString stringWithFormat:@"%@\n",text]];
    [attr addAttribute:NSFontAttributeName value:font range:range];
    [attr addAttribute:NSForegroundColorAttributeName value:fcolor range:range];
    [attr addAttribute:NSParagraphStyleAttributeName value:paragraph range:range];
    
    if(text.length >= 6){
        NSString* str = [text substringToIndex:6];
        if ([str compare:@"【TJS】:"] == NSOrderedSame) {
            [attr addAttribute:NSForegroundColorAttributeName value:[NSColor colorWithRed:127/255.0f green:208/255.0f blue:97/255.0f alpha:1] range:NSMakeRange(0, 6)];
        }
    }
    [[output textStorage]appendAttributedString:attr];
    [output scrollToEndOfDocument:nil];
}


-(IBAction)onOKClick:(id)sender
{
    [self control:input textShouldBeginEditing:nil];
}

-(IBAction)onClearClick:(id)sender
{
    output.string = @"";//[NSMutableString stringWithString:@""];
}


- (BOOL)control:(NSControl *)control textShouldEndEditing:(NSText *)fieldEditor
{
    if (control.stringValue == nil ||
        control.stringValue.length == 0) {
        return YES;
    }
    else
    {
        tTJSVariant ret;
        wstring code;
        DE::Utf8ToUnicode(control.stringValue.UTF8String, code);

        if(!DE::ScriptEngine::GetInstance()->eval(code, &ret)){
            control.stringValue = @"";
            return YES;
        }
        ret.ToString();
        const wchar_t* res = ret.AsStringNoAddRef()->operator const wchar_t *();
        string r;
        DE::UnicodeToUtf8(res, r);
        string tr = control.stringValue.UTF8String;
        control.stringValue = @"";
        [self pushString:[NSString stringWithUTF8String:(tr+":\n"+r).c_str()]];
        return YES;
    }
}

@end
