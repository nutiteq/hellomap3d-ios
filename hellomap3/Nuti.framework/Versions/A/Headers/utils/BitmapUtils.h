/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_BITMAPUTILS_H_
#define _NUTI_BITMAPUTILS_H_

#include <memory>

#import <UIKit/UIKit.h>

namespace Nuti {
    class Bitmap;

    /**
     * A helper class for converting Bitmaps to UIImages an vice versa.
     */
    class BitmapUtils {
    public:
        /**
         * Creates a new Bitmap object from an existing UIImage.
         * @param image The reference UIImage.
         */
        static std::shared_ptr<Bitmap> CreateBitmapFromUIImage(const UIImage* image);
    	
        /**
         * Creates a new Bitmap object from an existing UIImage. If the power of two conversion flag is set,
         * additional padding will be added to the image to make it's dimensions power of two.
         * @param image The reference UIImage.
         * @param pow2Padding The power of two conversion flag.
         */
        static std::shared_ptr<Bitmap> CreateBitmapFromUIImage(const UIImage* image, bool pow2Padding);
        
        /**
         * Creates a new UIImage object from an existing Bitmap.
         * @return The UIImage.
         */
        static UIImage* CreateUIImageFromBitmap(const std::shared_ptr<Bitmap>& bitmap);

    private:
         BitmapUtils();
    };

}

#endif
