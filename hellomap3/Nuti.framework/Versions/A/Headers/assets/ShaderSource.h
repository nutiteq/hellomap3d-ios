#ifndef SHADERSOURCE_H_
#define SHADERSOURCE_H_

#include <string>

namespace Nuti {

class ShaderSource {
public:
    ShaderSource(const std::string& name, const std::string* vertSource, const std::string* fragSource, const unsigned char* progData, unsigned int progDatalen) :
        _name(name),
        _vertSource(vertSource),
        _fragSource(fragSource),
        _progData(progData),
        _progDataLen(progDatalen)
    {
    }
    virtual ~ShaderSource() {}
    
    const std::string& getName() const { return _name; }
    
    const std::string* getVertSource() const { return _vertSource; }
    const std::string* getFragSource() const { return _fragSource; }
    
    const unsigned char* getProgData() const { return _progData; }
    unsigned int getProgDataLen() const { return _progDataLen; }

private:
    std::string _name;
    
    const std::string* _vertSource;
    const std::string* _fragSource;
    
    const unsigned char* _progData;
    unsigned int _progDataLen;
};
    
}

#endif

