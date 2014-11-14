#import "VectorMapSampleBaseController.h"

@interface VectorMapSampleBaseController ()

@end

@implementation VectorMapSampleBaseController

- (void)viewDidLoad
{
	[super viewDidLoad];
	
	// Enable logging
	[NTLog SetShowDebug:YES];
	[NTLog SetShowInfo:YES];
	
	// Set the base projection, that will be used for most MapView, MapEventListener and Options methods
	NTEPSG3857* proj = [[NTEPSG3857 alloc] init];
	[[self getOptions] setBaseProjection:proj];
	
	// Set initial location and other parameters, don't animate
	[self setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.650415 y:59.428773]]  durationSeconds:0];
	[self setZoom:14 durationSeconds:0];
	[self setRotation:0 durationSeconds:0];
	
	// General options
	[[self getOptions] setTileDrawSize:256];
	
	// Use modern vector background. Suggested strongly, especially if you rotate and tilt the map
		
	// Load vector tile styleset
	UnsignedCharVector *vectorTileStyleSetData = [NTAssetUtils loadBytes: @"osmbright.zip"];
	NTMBVectorTileStyleSet *vectorTileStyleSet = [[NTMBVectorTileStyleSet alloc] initWithData:vectorTileStyleSetData];
	// Create vector tile decoder using the styleset
	self.vectorTileDecoder = [[NTMBVectorTileDecoder alloc] initWithStyleSet:vectorTileStyleSet];
		
	// Create global online vector tile data source, use Nutiteq test account
	NTTileDataSource *vectorTileDataSource = [[NTHTTPTileDataSource alloc] initWithMinZoom:0 maxZoom:14 baseURL:@"http://api.nutiteq.com/v1/nutiteq.mbstreets/{zoom}/{x}/{y}.vt?user_key=15cd9131072d6df68b8a54feda5b0496"];

	// Create vector tile layer, using previously created data source and decoder
	self.baseLayer = [[NTVectorTileLayer alloc] initWithDataSource:vectorTileDataSource decoder:self.vectorTileDecoder];
	// Add vector tile layer
	[[self getLayers] add:self.baseLayer];
}

- (void)didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
	// Dispose of any resources that can be recreated.
}

@end
