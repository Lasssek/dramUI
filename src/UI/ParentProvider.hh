#pragma once


class ParentProvider {
public:
    virtual int GetWidth()  = 0;
    virtual int GetHeight() = 0;
    virtual ~ParentProvider() = default;
};