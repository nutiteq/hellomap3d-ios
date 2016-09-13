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


#import "NTPackageInfo.h"
#import "NTPackageMetaInfo.h"
#import "NTPackageStatus.h"
#import "NTPackageManagerListener.h"
#import "NTPackageInfoVector.h"

/**
 * Base class for offline map package manager. Package manager supports downloading/removing packages.<br>
 * It can be queried about available packages and status of the packages. It works asynchronously in<br>
 * the background and can inform app when packages have been updated.<br>
 * It works persistently. If a package download is started and app is closed, the download will resume<br>
 * when the package manager is started next time.
 */
__attribute__ ((visibility("default"))) @interface NTPackageManager : NSObject
{
  void *swigCPtr;
  BOOL swigCMemOwn;
}
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**
 * Creates a polymorphic instance of the given native object. This is used internally by the SDK.
 */
+(NTPackageManager*)swigCreatePolymorphicInstance:(void*)cPtr swigOwnCObject:(BOOL)cMemoryOwn;


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
 * Constructs a new package manager, given URL for package list and data folder.<br>
 * The data folder must exist before creating a new package manager and it is assumed to be persistent.<br>
 * Note: the package manager must be explicitly started using start() method!<br>
 * @param packageListUrl The URL that defines all packages.<br>
 * @param dataFolder The folder where downloaded packages are kept. It must exist and must be writable.<br>
 * @param serverEncKey Encryption key for server packages<br>
 * @param localEncKey Encryption key for local packages
 */
-(id)initWithPackageListUrl: (NSString*)packageListUrl dataFolder: (NSString*)dataFolder serverEncKey: (NSString*)serverEncKey localEncKey: (NSString*)localEncKey;
/**
 * Returns the current listener for package manager events.<br>
 * @return The current listener or null if none is set.
 */
-(NTPackageManagerListener*)getPackageManagerListener;
/**
 * Sets the package manager listener.<br>
 * @param listener The new package manager listener to use.
 */
-(void)setPackageManagerListener: (NTPackageManagerListener*)listener;
/**
 * Starts the package manager. All previous tasks will be resumed after this.<br>
 * @return True if package manager was successfully started. False otherwise (can not create/access database).
 */
-(BOOL)start;
/**
 * Stops the package manager. The stopping can be asynchronous or synchronous.<br>
 * @param wait If set to true, then synchronous stopping is performed and the operation may take a while.
 */
-(void)stop: (BOOL)wait;
/**
 * Returns the list of available server packages.<br>
 * Note that the list must be retrieved from the server first, using startPackageListDownload.<br>
 * @return The list of available server packages.
 */
-(NTPackageInfoVector*)getServerPackages;
/**
 * Returns the list of available local downloaded packages.<br>
 * @return The list of available local downloaded packages.
 */
-(NTPackageInfoVector*)getLocalPackages;
/**
 * Returns the metainfo of server packages.<br>
 * @return The metainfo data about server packages, or null if no metainfo is available.
 */
-(NTPackageMetaInfo*)getServerPackageListMetaInfo;
/**
 * Returns the age of server package list. This method can be used to measure the time of the download and check whether the list should be updated.<br>
 * @return The age of server package list in seconds.
 */
-(int)getServerPackageListAge;
/**
 * Returns the specified server package.<br>
 * Note that the list must be retrieved from the server first, using startPackageListDownload.<br>
 * @return The specified server package or null if it is not in the server package list.
 */
-(NTPackageInfo*)getServerPackage: (NSString*)packageId;
/**
 * Returns the specified local package.<br>
 * @return The specified local package or null if it can not be found in the package list.
 */
-(NTPackageInfo*)getLocalPackage: (NSString*)packageId;
/**
 * Returns the status of the specified package.<br>
 * @param packageId The id of the package.<br>
 * @param version The version of the package. Use -1 for the latest version.<br>
 * @return The status of the package or null if it is not yet downloaded or downloading.
 */
-(NTPackageStatus*)getLocalPackageStatus: (NSString*)packageId version: (int)version;
/**
 * Starts downloading package list asynchronously. When this task finishes, listener is called and server package list is updated.<br>
 * @return True if the package list will be downloaded and listener will be notified (if set). False if it can not be downloaded.
 */
-(BOOL)startPackageListDownload;
/**
 * Starts importing the specified package asynchronously. When this task finishes, listener is called and local package list is updated.<br>
 * Note 1: In general, package manager may need temporary storage equal to the size of the package during import. It is the responsibility of the app to perform such checks.<br>
 * Note 2: the package may not be deleted after this call, as the import is asynchronous operation. It is safe to delete the original file once import is complete (this is notified via manager listener).<br>
 * @param packageId The id of the package to download.<br>
 * @param version The version of the package.<br>
 * @param packageFileName The fully qualified path of the package.<br>
 * @return True is the package will be imported.
 */
-(BOOL)startPackageImport: (NSString*)packageId version: (int)version packageFileName: (NSString*)packageFileName;
/**
 * Starts downloading specified package asynchronously. When this task finishes, listener is called and local package list is updated.<br>
 * Note: In general, package manager may need temporary storage equal to the size of the package during download. It is the responsibility of the app to perform such checks.<br>
 * @param packageId The id of the package to download.<br>
 * @return True is the package is available and will be downloaded. False if the package was not found.
 */
-(BOOL)startPackageDownload: (NSString*)packageId;
/**
 * Starts the removal of specified package asynchronously. When this task finishes, listener is called and local package list is updated.<br>
 * @param packageId The id of the package to remove.<br>
 * @return True is the package was found and will be removed. False if the package was not found.
 */
-(BOOL)startPackageRemove: (NSString*)packageId;
/**
 * Cancels the current/pending tasks involving of the specified package.<br>
 * @param packageId The id of the package to cancel
 */
-(void)cancelPackageTasks: (NSString*)packageId;
/**
 * Sets the priority of the specific package.<br>
 * If the given priority is higher than priority of any other package, other operations will be paused and this package is processed immediately.<br>
 * If the given priority is set to negative value, package download will be paused until priority is reset to non-negative value.<br>
 * @param packageId The id of the download package.<br>
 * @param priority The priority of the download package. If it is less than zero, package download is paused.
 */
-(void)setPackagePriority: (NSString*)packageId priority: (int)priority;
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

