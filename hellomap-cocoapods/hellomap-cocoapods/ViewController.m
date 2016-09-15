//
//  ViewController.m
//  hellomap-cocoapods
//
//  Created by Aare Undo on 14/09/16.
//  Copyright © 2016 Aare Undo. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // GLKViewController-specific parameters for smoother animations
    [self setResumeOnDidBecomeActive: NO];
    [self setPreferredFramesPerSecond: 60];
    
    // The storyboard has NTMapView connected as a view
    NTMapView* mapView = (NTMapView*) self.view;
    
    // Set the base projection, that will be used for most MapView, MapEventListener and Options methods
    NTEPSG3857* proj = [[NTEPSG3857 alloc] init];
    // EPSG3857 is actually the default base projection, so this is actually not needed
    [[mapView getOptions] setBaseProjection:proj];
    
    // General options
    [[mapView getOptions] setRotatable:YES]; // make map rotatable (this is actually the default)
    [[mapView getOptions] setTileThreadPoolSize:2]; // use 2 threads to download tiles
    
    // Set initial location and other parameters, don't animate
    [mapView setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.650415 y:59.428773]]  durationSeconds:0];
    [mapView setZoom:14 durationSeconds:0];
    [mapView setRotation:0 durationSeconds:0];
    
    // Create online vector tile layer, use style asset embedded in the project
    NTVectorTileLayer* vectorTileLayer = [[NTNutiteqOnlineVectorTileLayer alloc] initWithStyleAssetName:@"nutibright-v3.zip"];
    
    // Add vector tile layer
    [[mapView getLayers] add:vectorTileLayer];
    
    // Load bitmaps for custom markers
    UIImage* markerImage = [UIImage imageNamed:@"marker.png"];
    NTBitmap* markerBitmap = [NTBitmapUtils createBitmapFromUIImage:markerImage];

    // Create a marker style, use it for both markers, because they should look the same
    NTMarkerStyleBuilder* markerStyleBuilder = [[NTMarkerStyleBuilder alloc] init];
    [markerStyleBuilder setBitmap:markerBitmap];
    [markerStyleBuilder setSize:30];
    NTMarkerStyle* sharedMarkerStyle = [markerStyleBuilder buildStyle];
    
    // Initialize a local vector data source
    NTLocalVectorDataSource* vectorDataSource = [[NTLocalVectorDataSource alloc] initWithProjection:proj];
    
    // Create marker, add it to the data source
    NTMapPos* pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.646469 y:59.426939]]; // Tallinn
    NTMarker* marker = [[NTMarker alloc] initWithPos:pos style:sharedMarkerStyle];
    [vectorDataSource add:marker];
    
    // Initialize a vector layer with the previous data source
    NTVectorLayer* vectorLayer = [[NTVectorLayer alloc] initWithDataSource:vectorDataSource];
    
    // Add the previous vector layer to the map
    [[mapView getLayers] add:vectorLayer];
}

@end











