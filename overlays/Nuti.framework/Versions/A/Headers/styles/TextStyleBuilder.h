#ifndef TEXTSTYLEBUILDER_H_
#define TEXTSTYLEBUILDER_H_

#include "styles/LabelStyleBuilder.h"
#include "styles/TextStyle.h"

#include <memory>

namespace Nuti {

/**
 * A builder class for TextStyle.
 */
class TextStyleBuilder : public LabelStyleBuilder {
public:
    /**
     * Constructs a TextStyleBuilder object with all parameters set to defaults.
     */
	TextStyleBuilder();
	virtual ~TextStyleBuilder();

    /**
     * Sets the font name for the text label.
     * @param The new platfrom dependent font name for the text label.
     */
	void setFontName(const std::string& fontName);

    /**
     * Sets the font size for the text label.
     * @param The new font size for the text label in points.
     */
	void setFontSize(int size);

    /**
     * Sets the stroke color for the text label.
     * @param The new stroke color for the text label.
     */
	void setStrokeColor(const Color& strokeColor);

    /**
     * Sets the stroke width for the text label.
     * @param The new stroke widht for the text label in screen density independent pixels.
     */
	void setStrokeWidth(float strokeWidth);

    /**
     * Builds a new instance of the TextStyle object using previously set parameters.
     * @return A new TextStyle object.
     */
	std::shared_ptr<TextStyle> buildStyle();

protected:
	std::string _fontName;

	int _fontSize;
    
	Color _strokeColor;

	float _strokeWidth;

};

}

#endif
