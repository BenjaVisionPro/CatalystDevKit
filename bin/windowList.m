////////////////////////////////////////////////////////////////////////////////
// Compile with:
// clang windowlist.m -o windowlist -framework coregraphics -framework cocoa
//
// Run with:
// ./windowlist
//
// You can then run "screencapture" to capture that window:
//
// screencapture -l<windowid> -x someFile.[png|jpg|tif]
////////////////////////////////////////////////////////////////////////////////
#include <Cocoa/Cocoa.h>
#include <CoreGraphics/CGWindow.h>

int main(int argc, char **argv)
{
   NSArray *windows = (NSArray *)CGWindowListCopyWindowInfo(kCGWindowListExcludeDesktopElements|kCGWindowListOptionOnScreenOnly,kCGNullWindowID);
   for(NSDictionary *window in windows){
      int WindowNum = [[window objectForKey:(NSString *)kCGWindowNumber] intValue];
      NSString* OwnerName = [window objectForKey:(NSString *)kCGWindowOwnerName];
      NSString* WindowName= [window objectForKey:(NSString *)kCGWindowName];
      printf("%s:%s:%d\n",[OwnerName UTF8String],[WindowName UTF8String],WindowNum);
   }
}


void test() {
	NSArray* windowList = (__bridge NSArray*)CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
	uint32_t maxDisplayCount = 10;
	CGDirectDisplayID onlineDisplayIDs[maxDisplayCount];
	uint32_t displayCount;
	CGGetOnlineDisplayList(maxDisplayCount, (CGDirectDisplayID*)&onlineDisplayIDs, &displayCount);
	for(uint32_t i = 0; i < displayCount; ++i)
	{
		CGRect dspyRect = CGDisplayBounds(onlineDisplayIDs[i]);
		for(NSDictionary* windowDict in windowList)
		{
			CGRect windowRect;
			CGRectMakeWithDictionaryRepresentation((__bridge CFDictionaryRef)(windowDict[(id)kCGWindowBounds]), &windowRect);
			if(CGRectContainsRect(dspyRect, windowRect))
			{
				NSLog(@"window %@ is on screen with ID:%d", windowDict[(id)kCGWindowName], onlineDisplayIDs[i]);
			}
		}
	}
}