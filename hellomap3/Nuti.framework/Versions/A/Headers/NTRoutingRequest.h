/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.11
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#import <Foundation/Foundation.h>


#ifdef __cplusplus
extern "C" {
#endif


#import "NTMapPos.h"
#import "NTProjection.h"
#import "NTMapPosVector.h"

/**
 * A class that defines required attributes for routing (end points, etc).
 */
__attribute__ ((visibility("default"))) @interface NTRoutingRequest : NSObject
{
  void *swigCPtr;
  BOOL swigCMemOwn;
}
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**  
 * Checks if this object is equal to the specified object.
 * @return True when objects are equal, false otherwise.
 */
-(BOOL)isEqual:(id)object;

/**
 * Returns the hash value of this object.
 * @return The hash value of this object.
 */
-(NSUInteger)hash;

/**
 * Constructs a new RoutingRequest instance from projection and via points.<br>
 * @param projection The projection of the points.<br>
 * @param points The list of points that the route must pass. Must contains at least 2 elements.
 */
-(id)initWithProjection: (NTProjection*)projection points: (NTMapPosVector*)points;
/**
 * Returns the projection of the points in the request.<br>
 * @return The projection of the request.
 */
-(NTProjection*)getProjection;
/**
 * Returns the point list of the request.<br>
 * @return The point list of the request.
 */
-(NTMapPosVector*)getPoints;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

