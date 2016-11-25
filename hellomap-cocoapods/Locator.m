//
//  Locator.m
//  MapCrashTest
//
//  Created by Arunas Pangonis on 25/11/2016.
//  Copyright © 2016 Arunas Pangonis. All rights reserved.
//

#import "Locator.h"

@interface Locator ()
@property (nonatomic, strong) CLLocationManager *manager;
@property (nonatomic, assign) BOOL isUpdatingLocation;
@end

@implementation Locator

+ (Locator *)sharedLocator
{
    static Locator *sharedLocator = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedLocator = [[Locator alloc] init];
    });
    return sharedLocator;
}

- (id)init
{
    self = [super init];
    if (self)
    {
        self.isUpdatingLocation = NO;
        self.manager = [[CLLocationManager alloc] init];
        [self.manager setDesiredAccuracy:kCLLocationAccuracyBestForNavigation];
        [self.manager requestWhenInUseAuthorization];
        [self.manager setAllowsBackgroundLocationUpdates:YES];
        [self.manager setDelegate:self];
    }
    
    return self;
}

- (BOOL)isUpdatingLocation
{
    return _isUpdatingLocation;
}

- (void)startUpdatingLocation
{
    [self.manager startUpdatingLocation];
    self.isUpdatingLocation = YES;
    NSLog(@"startUpdatingLocation");
}

- (void)stopUpdatingLocation
{
    self.isUpdatingLocation = NO;
    [self.manager stopUpdatingLocation];
    NSLog(@"stopUpdatingLocation");
}

#pragma mark CLLocationManagerDelegate


- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations
{
    [self.delegate locator:self didUpdateLocationTo:[locations firstObject]];
}



- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error;
{
    NSLog(@"locationManagerm didFailWithError %@", error);
}

- (void)locationManagerDidPauseLocationUpdates:(CLLocationManager *)manager
{
    NSLog(@"locationManagerDidPauseLocationUpdates");
}

- (void)locationManagerDidResumeLocationUpdates:(CLLocationManager *)manager
{
    NSLog(@"locationManagerDidResumeLocationUpdates");
}

@end
