#import "MapSampleBaseController.h"

@implementation MapSampleBaseController

- (void)viewDidLoad
{
	[NTLog SetShowDebug:true];
	[NTLog SetShowInfo:true];

	// The initial step: register your license. This must be done before using MapView and before calling [super viewDidLoad]!
	// You can get your free/commercial license from: http://developer.nutiteq.com
	// The license string used here is intended only for Nutiteq demos and WILL NOT WORK with other apps!
	[NTMapViewController RegisterLicense:@"XTUN3Q0ZBd2NtcmFxbUJtT1h4QnlIZ2F2ZXR0Mi9TY2JBaFJoZDNtTjUvSjJLay9aNUdSVjdnMnJwVXduQnc9PQoKcHJvZHVjdHM9c2RrLWlvcy0zLiosc2RrLWFuZHJvaWQtMy4qCnBhY2thZ2VOYW1lPWNvbS5udXRpdGVxLioKYnVuZGxlSWRlbnRpZmllcj1jb20ubnV0aXRlcS4qCndhdGVybWFyaz1ldmFsdWF0aW9uCnVzZXJLZXk9MTVjZDkxMzEwNzJkNmRmNjhiOGE1NGZlZGE1YjA0OTYK"];
	
	[super viewDidLoad];
}

- (void)didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
	// Dispose of any resources that can be recreated.
}

@end
