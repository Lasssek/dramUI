#pragma once


class IParentProvider {
public:
    virtual int GetWidth()  = 0;
    virtual int GetHeight() = 0;
    virtual ~IParentProvider() = default;
};