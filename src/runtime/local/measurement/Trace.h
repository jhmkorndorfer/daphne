#pragma once

#include <string>

class Trace {
private:
    double startTime;
    double endTime;
    std::string traceSignature;
public:
    void RecordStart(double startTime) {
        this->startTime = startTime;
    }

    void RecordEnd(double endTime) {
        this->endTime = endTime;
    }

    void RecordSignature(const std::string& signature) {
        traceSignature = signature;
    }

    double GetDuration() const {
        return endTime - startTime;
    }

    const std::string& GetSignature() const {
        return traceSignature;
    }

    double GetStart() const {
        return startTime;
    }

    double GetEnd() const {
        return endTime;
    }

};