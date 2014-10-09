#ifndef Bitmap_H_
#define Bitmap_H_

#include "utils/GLES2.h"

#include <memory>
#include <string>
#include <vector>

namespace Nuti {
    
namespace ColorFormat {
    /**
     * Possible image formats.
     */
	enum ColorFormat {
        /**
         * Options for identifiny unsupported image formats.
         */
		COLOR_FORMAT_UNSUPPORTED = 0,
        /**
         * An image format that describes images with a single color channel.
         */
		COLOR_FORMAT_GRAYSCALE = 0x1909, //GL_LUMINANCE,
        /**
         * An image format that describes images with two channels, one for color and the other
         * for alpha.
         */
		COLOR_FORMAT_GRAYSCALE_ALPHA = 0x190A, //GL_LUMINANCE_ALPHA,
        /**
         * An image format that describes images with three channels, one for each color: red, green and blue.
         */
		COLOR_FORMAT_RGB = 0x1907, //GL_RGB,
        /**
         * An image format that describes images with four channels, one for each color: red, green and blue
         * and one for alpha.
         */
		COLOR_FORMAT_RGBA = 0x1908, //GL_RGBA,
        /**
         * An image format that describes images with four channels, one for each color: blue, green and red
         * and one for alpha. This color format will be converted to RGBA.
         */
		COLOR_FORMAT_BGRA = 1,
		/**
		 * An image format that describes images with four channels, one for each color: red, green, and blue
		 * and one for alpha. Each color is only four bits. This color format will be converted to RGBA.
		 */
		COLOR_FORMAT_RGBA_4444 = 2,
		/**
		 * An image format that describes images with three channels, one for each color: red, green, and blue.
		 * Red and blue colors are each packed into 5 bits, green into 6 bits. This color format will be converted to RGB.
		 */
		COLOR_FORMAT_RGB_565 = 3
	};
};

/**
 * A class that provides the functionality to store, compress, uncompress and resize basic image formats.
 * Currently supported formats are png and jpeg. Upon loading compressed images will be converted to
 * alpha premultiplied uncompressed bitmaps of various image formats.
 */
class Bitmap {
public:
    /**
     * Constructs a bitmap by loading a compressed image bundled with the application. If the power of two conversion flag
     * is set, additional padding will be added to the image to make it's dimensions power of two. This can be useful when creating
     * OpenGL textures from the Bitmap, because some GPUs perform badly with non power of two textures.
     * @param assetPath The path to the image to be loaded.
     * @param pow2Padding The power of two conversion flag.
     */
	Bitmap(const std::string& assetPath, bool pow2Padding);
    /**
     * Constructs a bitmap by decoding a vector of compressed image bytes. If the power of two conversion flag
     * is set, additional padding will be added to the image to make it's dimensions power of two. This can be useful when creating
     * OpenGL textures from the Bitmap, because some GPUs perform badly with non power of two textures.
     * @param compressedData A vector of compressed image bytes.
     * @param pow2Padding The power of two conversion flag.
     */
	Bitmap(const std::vector<unsigned char>& compressedData, bool pow2Padding);
    /**
     * Constructs a bitmap by decoding an array of compressed image bytes. If the power of two conversion flag
     * is set, additional padding will be added to the image to make it's dimensions power of two. This can be useful when creating
     * OpenGL textures from the Bitmap, because some GPUs perform badly with non power of two textures.
     * @param compressedData The pointer to the beginning of an array containing the compressed image bytes.
     * @param compressedData The number of bytes in the given byte array.
     * @param pow2Padding The power of two conversion flag.
     */
	Bitmap(const unsigned char* compressedData, int dataSize, bool pow2Padding);
	/**
     * Constructs a bitmap from an already decoded vector of bytes. The bitmap data is expected to be alpha premultiplied.
     * If the power of two conversion flag is set, additional padding will be added to the image to make it's dimensions power of two.
     * This can be useful when creating OpenGL textures from the Bitmap, because some GPUs perform badly with non power of two textures.
     * @param compressedData A vector of decoded, premultiplied bitmap bytes.
     * @param width The width of the bitmap.
     * @param height The height of the bitmap.
     * @param colorFormat The color format of the bitmap.
     * @param bytesPerRow The total number of bytes per row. Some bitmaps have additional padding at the end of each row.
     * @param pow2Padding The power of two conversion flag.
     */
	Bitmap(const std::vector<unsigned char>& uncompressedData, unsigned int width, unsigned int height,
               ColorFormat::ColorFormat colorFormat, unsigned int bytesPerRow, bool pow2Padding);
	/**
     * Constructs a bitmap from an already decoded array of bytes. The bitmap data is expected to be alpha premultiplied.
     * If the power of two conversion flag is set, additional padding will be added to the image to make it's dimensions power of two.
     * This can be useful when creating OpenGL textures from the Bitmap, because some GPUs perform badly with non power of two textures.
     * @param compressedData The pointer to the beginning of an array containing the decoded, premultiplied bitmap bytes.
     * @param width The width of the bitmap.
     * @param height The height of the bitmap.
     * @param colorFormat The color format of the bitmap.
     * @param bytesPerRow The total number of bytes per row. Some bitmaps have additional padding at the end of each row.
     * @param pow2Padding The power of two conversion flag.
     */
	Bitmap(const unsigned char* uncompressedData, unsigned int width, unsigned int height,
               ColorFormat::ColorFormat colorFormat, unsigned int bytesPerRow, bool pow2Padding);
	virtual ~Bitmap();

    /**
     * Returns the width of the bitmap.
     * @return The width of the bitmap.
     */
	unsigned int getWidth() const;
    /**
     * Returns the height of the bitmap.
     * @return The height of the bitmap.
     */
	unsigned int getHeight() const;
    /**
     * Returns the unpadded width of this bitmap. If power of two padding was added when constructing this bitmap, the original unpadded
     * bitmap's width will be returned. If no padding was added, this method is equivalent to the getWidth() method.
     * @return The width of the bitmap without power of two padding.
     */
	unsigned int getOrigWidth() const;
    /**
     * Returns the unpadded height of this bitmap. If power of two padding was added when constructing this bitmap, the original unpadded
     * bitmap's height will be returned. If no padding was added, this method is equivalent to the getHeight() method.
     * @return The height of the bitmap without power of two padding.
     */
	unsigned int getOrigHeight() const;

    /**
     * Returns the color format of this bitmap.
     * @return The color format of this bitmap.
     */
	ColorFormat::ColorFormat getColorFormat() const;
    /**
     * Returns the bytes per pixel parameter of this bitmap. Valid values are 1, 2, 3 and 4.
     * @return The bytes per pixel parameter of this bitmap.
     */
	unsigned int getBytesPerPixel() const;

    /**
     * Returns the pixel data of this bitmap.
     * @return A byte vector of the bitmap's pixel data.
     */
	const std::vector<unsigned char>& getPixelData() const;

    /**
     * Compresses this bitmap to a png.
     * @return A byte vector of the png's data.
     */
	std::shared_ptr<std::vector<unsigned char> > compressToPng() const;

    /** 
     * Resizes the bitmap to the desired dimensions. The power of two padding added during the construction of this bitmap 
     * will be removed prior to resizing. If the power of two conversion flag is set, new padding will be added to the image 
     * after resizing to make it's dimensions power of two.
     * @param width The new width of this bitmap.
     * @param width The new height of this bitmap.
     * @param pow2Padding The power of two conversion flag.
     */
	void resize(unsigned int width, unsigned int height, bool pow2Padding);

protected:
    Bitmap();
    
	bool loadFromAssets(const std::string& path, bool makePow2);
	bool loadFromCompressedBytes(const unsigned char* compressedData, int dataSize, bool makePow2);
	bool loadFromUncompressedBytes(const unsigned char* uncompressedData, unsigned int width, unsigned int height,
                                   ColorFormat::ColorFormat colorFormat, unsigned int bytesPerRow, bool makePow2);

	bool isJPEG(const unsigned char* compressedData, int dataSize);
	bool isPNG(const unsigned char* compressedData, int dataSize);
    bool isWEBP(const unsigned char* compressedData, int dataSize);

	bool loadJPEG(const unsigned char* compressedData, int dataSize, bool makePow2);
	bool loadPNG(const unsigned char* compressedData, int dataSize, bool makePow2);
    bool loadWEBP(const unsigned char* compressedData, int dataSize, bool makePow2);

	static const unsigned int PNG_SIGNATURE_LENGTH = 8;

	unsigned int _origWidth;
	unsigned int _origHeight;
	unsigned int _width;
	unsigned int _height;

    unsigned int _bytesPerPixel;
	ColorFormat::ColorFormat _colorFormat;

	std::vector<unsigned char> _pixelData;
};

}

#endif
