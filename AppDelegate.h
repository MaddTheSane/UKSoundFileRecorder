//
//  AppDelegate.h
//  UKSoundRecorder
//
//  Created by Uli Kusterer on 14.07.07.
//  Copyright 2007 M. Uli Kusterer. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "UKSoundFileRecorder.h"


@interface AppDelegate : NSObject
{
	IBOutlet UKSoundFileRecorder*		recorder;
	IBOutlet NSTextField*				pathField;
	IBOutlet NSTextField*				statusField;
}

@end
