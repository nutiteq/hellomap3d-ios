//
//  CartoDbSqlDataSource.m
//  advancedmap3
//
//  Created by Jaak Laineste on 09/12/15.
//  Copyright © 2015 Nutiteq. All rights reserved.
//

#import "CartoDbSqlDataSource.h"

@implementation CartoDbSqlDataSource

-(id) initWithServer: (NSString*)server query:(NSString*)query style: (NTStyle*)style proj: (NTProjection*) proj
{
    self = [super initWithProjection:proj];
    if (self != nil) {
        _server = server;
        _query = query;
        _style = style;
    }
    return self;
}

-(NTVectorElementVector*)loadElements: (NTCullState*)cullState{
    
    NTVectorElementVector* elements = [[NTVectorElementVector alloc] init];
    
    NTMapEnvelope* mapViewBounds = [cullState getProjectionEnvelope:[[NTEPSG3857 alloc] init]];
    NTMapPos* min = [[mapViewBounds getBounds] getMin];
    NTMapPos* max = [[mapViewBounds getBounds] getMax];
    
    //run query here
    [self loadData: elements minX:[min getX] minY:[min getY] maxX:[max getX] maxY:[max getY] zoom: [[cullState getViewState] getZoom]];
    
    return elements;
}

// load data from SQL API
- (void) loadData: (NTVectorElementVector*) elements minX:(double)minX minY:(double)minY maxX:(double)maxX maxY:(double)maxY zoom:(double)zoom{
    
    // load and parse JSON
    NSString* bbox = [NSString stringWithFormat:@"ST_SetSRID(ST_MakeEnvelope(%f,%f,%f,%f),3857) && the_geom",minX, minY, maxX, maxY];
    
    NSString* unencodedQuery = [_query stringByReplacingOccurrencesOfString:@"the_geom_webmercator" withString:@"the_geom_webmercator as the_geom"];

    unencodedQuery = [unencodedQuery stringByReplacingOccurrencesOfString:@"!bbox!" withString:bbox];
    
    unencodedQuery = [unencodedQuery stringByReplacingOccurrencesOfString:@"zoom('!scale_denominator!')" withString:[NSString stringWithFormat:@"%d",(int)zoom]];

 
    NSString* encodedQuery = CFBridgingRelease(CFURLCreateStringByAddingPercentEscapes(NULL,
                                                                                      (CFStringRef) unencodedQuery,
                                                                                      NULL,
                                                                                      (CFStringRef) @"!*'();:@&=+$,/?%#[]",
                                                                                      kCFStringEncodingUTF8));

    
    NSString* urlAddress =[NSString stringWithFormat:@"%@?format=GeoJSON&q=%@", _server, encodedQuery];
    
    NSLog(@"URL: %@",urlAddress);

    NSMutableURLRequest *request =
    [NSMutableURLRequest requestWithURL:[NSURL
                                         URLWithString:urlAddress]
//                            cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData
                                 cachePolicy:NSURLRequestReturnCacheDataElseLoad
                        timeoutInterval:30
     ];
    
    [request setHTTPMethod: @"GET"];
    [request setValue:@"gzip" forHTTPHeaderField:@"Accept-Encoding"];
    
    NSError *requestError = nil;
    NSURLResponse *urlResponse = nil;
    
    NSData *response1 =
    [NSURLConnection sendSynchronousRequest:request
                          returningResponse:&urlResponse error:&requestError];
    
        // parse geojson
    if(response1 == nil){
        NSLog(@"Could not load url: %@",requestError);
        return;
    }
        NSError* error;
        NSDictionary* json = [NSJSONSerialization
                              JSONObjectWithData:response1
                              options:kNilOptions
                              error:&error];
        
        
        NTGeoJSONGeometryReader* geoJsonReader = [[NTGeoJSONGeometryReader alloc] init];
        
        int i=0;
        NSArray *features = [json valueForKey:@"features"];
        for (NSDictionary *feature in features) {
           
            
            NSDictionary *geometry = [feature valueForKey:@"geometry"];
            NSDictionary *properties = [feature valueForKey:@"properties"];
            
            NSData *jsonData = [NSJSONSerialization dataWithJSONObject:geometry
                                                               options:NSJSONWritingPrettyPrinted
                                                                 error:nil];
            
            NSString* geomJson = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];;
            
            NTPointGeometry *geom = [geoJsonReader readGeometry:geomJson];
            
            //FIXME: temp filter, not needed for SQL
//            if([[geom getCenterPos] getX] < minX || [[geom getCenterPos] getY] < minY ||
//                [[geom getCenterPos] getX] > maxX ||
//               [[geom getCenterPos] getY] > maxY ||
//               i > 50){
//                continue; // skip rest if outside bounds
//            }
            
            NTVectorElement* element;
            
            if ([_style isKindOfClass:[NTPointStyle class]]){
                // add Point
                element = [[NTPoint alloc] initWithGeometry:geom style:
                           _style];
            }else if ([_style isKindOfClass:[NTMarkerStyle class]]){
                // Marker
                element = [[NTMarker alloc] initWithGeometry:geom style:
                           _style];
            }else if([_style isKindOfClass:[NTLineStyle class]]){
                // Line
                element = [[NTLine alloc] initWithGeometry:geom style:_style];
            }
            //TODO : add other geometry/style options
            
            // add all properties as MetaData, so you can use it with click handling
            for (NSString *key in [properties allKeys]) {
                [element setMetaDataElement:key element:[NSString stringWithFormat:@"%@",[properties valueForKey:key]]];
            }
            
            [elements add:element];
            i++;
        }
        [NTLog debug:[NSString stringWithFormat:@"Added %d features", i]];
}



@end
