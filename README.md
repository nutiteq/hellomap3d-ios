Nutiteq HelloMap 3D for iOs
===========================

Here are some simple example apps with Nutiteq Maps SDK 3.x for iOS.

   * HelloMap3: an example showing marker (pin) on top of vector tile base map
   * AdvancedMap3: various advanced samples showing different aspects and APIs of the SDK
   * Hellomap3swift: Basic Swift sample 


*NB!* You need to be careful when using the samples:

If you are **cloning** the sample project, then make sure you have [GIT-LFS](https://git-lfs.github.com/) installed. Otherwise SDK binary is not downloaded properly, and you get build error, something like `Nuti.framework/Nuti, file was built for unsupported file format ( 0x76 0x65 0x72 0x73 0x69 0x6F 0x6E 0x20 0x68 0x74 0x74 0x70 0x73 0x3A 0x2F 0x2F ) which is not the architecture being linked`

If you are **downloading** the sample project instead of cloning then you need to download SDK latest build separately. Get suitable development build for ios: [sdk3-ios-snapshot-latest.zip](https://nutifront.s3.amazonaws.com/sdk_snapshots/sdk3-ios-snapshot-latest.zip), unzip it and put to hellomap folder. With cloning the library should be downloaded automatically from GIT-LFS.


Developer getting started and doc references are in [Nutiteq Developer site](https://developer.nutiteq.com/docs)

Developing also for Android? [Hellomap3d-Android](https://github.com/nutiteq/hellomap3d-android) is our project with Nutiteq SDK for Android

![screenshot](https://dl.dropboxusercontent.com/u/3573333/public_web/ios_overlays_sample.png)


#### Podfile
```
pod 'Nutiteq', '= 3.3.1'
```
