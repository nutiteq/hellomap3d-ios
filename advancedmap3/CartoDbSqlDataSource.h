//
//  CartoDbSqlDataSource.h
//  advancedmap3
//
//  Created by Jaak Laineste on 09/12/15.
//  Copyright © 2015 Nutiteq. All rights reserved.
//

#import <Nuti/Nuti.h>

@interface CartoDbSqlDataSource : NTVectorDataSource

-(id)initWithServer: (NSString*)server query:(NSString*)query style: (NTStyle*)style proj: (NTProjection*) proj;

@property (strong, nonatomic) NTStyle* style;
@property (strong, nonatomic) NSString* server;
@property (strong, nonatomic) NSString* query;
                      
-(NTVectorElementVector*)loadElements: (NTCullState*)cullState;

@end
