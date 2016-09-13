/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#import "NTLicenseManagerListener.h"

@class GLKView;

@interface NTMapLicenseManagerListener : NTLicenseManagerListener

-(id)initWithLicenseKey:(NSString*)licenseKey defaultsKeyOld:(NSString*)oldKey defaultsKeyNew:(NSString*)newKey;

@end
