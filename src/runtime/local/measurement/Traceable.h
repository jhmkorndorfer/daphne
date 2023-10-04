#pragma once

#include <string>
#include <runtime/local/measurement/Trace.h>

class Traceable {
public:
    virtual void Start() = 0;
    virtual void End() = 0;
    virtual void Signature(const std::string& signature) = 0;
    virtual Trace GetTrace() = 0;
    virtual ~Traceable() {}
};
