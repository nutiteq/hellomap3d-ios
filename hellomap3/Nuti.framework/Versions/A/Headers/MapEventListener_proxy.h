/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.6
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


#import "MapClickInfo_proxy.h"
#import "VectorElementsClickInfo_proxy.h"

/**
 * Listener for events like map and vector element clicks etc.
 */
__attribute__ ((visibility("default"))) @interface NTMapEventListener : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;
/**
 * Listener method that gets called when the map is panned, rotated, tilted or zoomed.<br>
 * The thread this method is called from may vary.
 */
-(void)onMapMoved;
/**
 * Listener method that gets called when a click is performed on an empty area of the map.<br>
 * This method will NOT be called from the main thread.<br>
 * @param mapClickInfo A container that provides information about the click.
 */
-(void)onMapClicked: (NTMapClickInfo*)mapClickInfo;
/**
 * Listener method that gets called when a click is performed on a vector element.<br>
 * If there are multiple vector elements that are located at the click position, then the<br>
 * results will be sorted by their distance to the camera. The closest element will be the first one<br>
 * in the list. This method will NOT be called from the main thread.<br>
 * @param vectorElementsClickInfo A container that provides information about the click.
 */
-(void)onVectorElementClicked: (NTVectorElementsClickInfo*)vectorElementsClickInfo;
-(id)init;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif
