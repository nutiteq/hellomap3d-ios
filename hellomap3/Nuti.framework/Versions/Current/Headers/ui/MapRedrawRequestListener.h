/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#import "RedrawRequestListener_proxy.h"

@class GLKView;

@interface NTMapRedrawRequestListener : NTRedrawRequestListener

@property (weak, nonatomic) GLKView* view;

-(id)initWithView:(GLKView*)view;

@end
