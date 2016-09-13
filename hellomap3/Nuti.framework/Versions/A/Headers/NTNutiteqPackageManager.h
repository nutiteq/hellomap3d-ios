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


#import "NTPackageManager.h"

/**
 * Offline map package manager that uses Nutiteq online service for map package downloads.<br>
 * After packages are downloaded, they can be used offline without any connection to the server.
 */
__attribute__ ((visibility("default"))) @interface NTNutiteqPackageManager : NTPackageManager
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**
 * Creates a polymorphic instance of the given native object. This is used internally by the SDK.
 */
+(NTNutiteqPackageManager*)swigCreatePolymorphicInstance:(void*)cPtr swigOwnCObject:(BOOL)cMemoryOwn;

/**
 * Constructs a NutiteqPackageManager object, given application context and data folder.<br>
 * The data folder must exist before creating a new package manager and it is assumed to be persistent.<br>
 * Note: the package manager must be explicitly started using start() method!<br>
 * @param source Name of the package source. Default: "nutiteq.osm"<br>
 * @param dataFolder The folder where downloaded packages are kept. It must exist and must be writable.
 */
-(id)initWithSource: (NSString*)source dataFolder: (NSString*)dataFolder;
/**
 * Returns the actual class name of this object. This is used internally by the SDK.<br>
 * @return The class name of this object.
 */
-(NSString*)swigGetClassName;
/**
 * Returns the pointer to the connected director object. This is used internally by the SDK.<br>
 * @return The pointer to the connected director object or null if director is not connected.
 */
-(void *)swigGetDirectorObject;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

