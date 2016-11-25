//
//  Locator.h
//  MapCrashTest
//
//  Created by Arunas Pangonis on 25/11/2016.
//  Copyright © 2016 Arunas Pangonis. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@class Locator;

@protocol LocatorDelegate <NSObject>
@required

- (void)locator:(Locator*) locator didUpdateLocationTo:(CLLocation *) location;

@end

@interface Locator : NSObject <CLLocationManagerDelegate>
@property (nonatomic, weak) id<LocatorDelegate> delegate;


+ (Locator *)sharedLocator;

- (void)startUpdatingLocation;
- (void)stopUpdatingLocation;

- (BOOL)isUpdatingLocation;

@end
