//
//  UKSoundFileRecorder.h
//  UKSoundFileRecorder
//
//  Created by Uli Kusterer on 14.07.07.
//  Copyright 2007 M. Uli Kusterer. All rights reserved.
//
//	This software is provided 'as-is', without any express or implied
//	warranty. In no event will the authors be held liable for any damages
//	arising from the use of this software.
//
//	Permission is granted to anyone to use this software for any purpose,
//	including commercial applications, and to alter it and redistribute it
//	freely, subject to the following restrictions:
//
//	   1. The origin of this software must not be misrepresented; you must not
//	   claim that you wrote the original software. If you use this software
//	   in a product, an acknowledgment in the product documentation would be
//	   appreciated but is not required.
//
//	   2. Altered source versions must be plainly marked as such, and must not be
//	   misrepresented as being the original software.
//
//	   3. This notice may not be removed or altered from any source
//	   distribution.
//

/*
	A class that records audio from standard sound input into a file.
	
	To use, simply create a new UKSoundFileRecorder object and point it at
	a file on disk using -setOutputFilePath:. You can also specify an output
	format if you wish, default is 44000kHz AAC Stereo.
	
	The class /should/ be KVC/KVO compliant, but this hasn't been extensively
	tested yet. Please let me know of any problems you have using this with
	bindings.
*/

// -----------------------------------------------------------------------------
//	Headers:
// -----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <AudioUnit/AudioUnit.h>
#import <AudioToolbox/AudioToolbox.h>
#import "UKAudioStreamBasicDescription.h"


@protocol UKSoundFileRecorderDelegate;


// -----------------------------------------------------------------------------
//	UKSoundFileRecorder:
// -----------------------------------------------------------------------------

@interface UKSoundFileRecorder : NSObject
{
	AudioBufferList		*		audioBuffer;
	AudioUnit					audioUnit;
	ExtAudioFileRef				outputAudioFile;
	NSString			*		outputFilePath;
	
	NSString			*		inputDeviceUID;
	AudioDeviceID				inputDeviceID;
	UInt32						audioChannels;
	UInt32						audioSamples;
	AudioStreamBasicDescription	actualOutputFormat;
	AudioStreamBasicDescription	deviceFormat;
	NSDictionary*				outputFormat;
	NSDictionary*				actualOutputFormatDict;
	double						currSeconds;
	UInt64						startHostTime;
	
	BOOL						isRecording;
	
	BOOL						delegateWantsTimeChanges;
	BOOL						delegateWantsLevels;
	BOOL						canDoMetering;
	BOOL						delegateWantsRawFrames;
}

+(nonnull NSDictionary*)	defaultOutputFormat;

/// NSArray of NSDictionaries. See below for the keys.
+(nonnull NSArray*)			availableInputDevices;

/// Designated initializer. You can use -init and then do setOutputFilePath: or use -initWithOutputFilePath:.
-(nonnull instancetype)				init NS_DESIGNATED_INITIALIZER;
-(nonnull instancetype)				initWithOutputFilePath: (nonnull NSString*)ofp;

// Setup:
/// If you set no path, the delegate <i>must</i> implement \c -soundFileRecorder:receivedFrames:count:seconds:
@property (nonatomic, copy, nonnull) NSString *outputFilePath;
/// Calls <code>[self setOutputFilePath: [sender stringValue]]</code>.
-(IBAction)			takeOutputFilePathFrom: (nonnull id)sender;

/// Keys for this dictionary can be found in UKAudioStreamBasicDescription.h and below.
@property (nonatomic, copy, nonnull) NSDictionary *outputFormat;
@property (nonatomic, copy, readonly, nonnull) NSDictionary*	actualOutputFormat;

@property (nonatomic, weak, nullable) id<UKSoundFileRecorderDelegate> delegate;

// Recording:
///Start recording sound, like, right now.
-(IBAction)				start: (nullable id)sender;

/// Is YES if we are currently recording, NO otherwise.
@property (nonatomic, getter=isRecording, readonly) BOOL recording;

/// Stop recording sound and flush the file to disk.
-(IBAction)				stop: (nullable id)sender;

/// Pass \c nil for the system default input device as set in System Preferences.app
@property (nonatomic, strong, null_resettable) NSString *inputDeviceUID;

// You probably don't need this:
/// Called as needed by <code>start:</code>, if nobody called it before that.
-(void)				prepare;

@end

// -----------------------------------------------------------------------------
//	Additional OutputFormat keys:
// -----------------------------------------------------------------------------

#define UKAudioOutputFileType						@"UKAudioOutputFileFormat"	// This is not an HFS OSType, nor a file suffix!!! These are equivalent to AudioFileTypeID, just that they've been stringified using UKStringFromAudioStreamFormatID().
	#define UKAudioOutputFileTypeAIFF				@"AIFF"
	#define UKAudioOutputFileTypeAIFC				@"AIFC"
	#define UKAudioOutputFileTypeWAVE				@"WAVE"
	#define UKAudioOutputFileTypeSoundDesigner2		@"Sd2f"
	#define UKAudioOutputFileTypeNext				@"NeXT"
	#define UKAudioOutputFileTypeMP3				@"MPG3"
	#define UKAudioOutputFileTypeAC3				@"ac-3"
	#define UKAudioOutputFileTypeAAC_ADTS			@"adts"
	#define UKAudioOutputFileTypeMPEG4				@"mp4f"
	#define UKAudioOutputFileTypeM4A				@"m4af"
	#define UKAudioOutputFileTypeCAF				@"caff"


// -----------------------------------------------------------------------------
//	Dictionary keys in -availableInputDevices dictionaries:
// -----------------------------------------------------------------------------

extern NSString	*__nonnull	UKSoundFileRecorderDeviceUID;
extern NSString	*__nonnull	UKSoundFileRecorderDeviceName;
extern NSString	*__nonnull	UKSoundFileRecorderDeviceManufacturer;


// -----------------------------------------------------------------------------
//	Notifications:
// -----------------------------------------------------------------------------

extern NSString*__nonnull	UKSoundFileRecorderAvailableInputDevicesChangedNotification;


// -----------------------------------------------------------------------------
//	Delegate protocol:
// -----------------------------------------------------------------------------

@protocol UKSoundFileRecorderDelegate <NSObject>

@optional

/// Sent on a successful start:
-(void)	soundFileRecorderWasStarted: (nonnull UKSoundFileRecorder*)sender;

/// Sent while we're recording:
-(void)	soundFileRecorder: (nonnull UKSoundFileRecorder*)sender reachedDuration: (NSTimeInterval)timeInSeconds;

/// This is for level meters:
-(void)	soundFileRecorder: (nonnull UKSoundFileRecorder*)sender hasAmplitude: (float)theLevel;

/// Sent after a successful stop:
-(void)	soundFileRecorderWasStopped: (nonnull UKSoundFileRecorder*)sender;

/// The following is required if you do not provide an outputFilePath:
-(void)	soundFileRecorder: (nonnull UKSoundFileRecorder*)sender receivedFrames: (nonnull AudioBufferList*)inData count: (UInt32)inNumberFrames seconds: (double)inSeconds;

@end


