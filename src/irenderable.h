#ifndef IRENDERABLE_H
#define IRENDERABLE_H

/**
 * Simple interface for interacting with renderable objects.
 */

class IRenderable
{
public:
    virtual void Render() = 0;
    virtual ~IRenderable() {}
};



#endif //IRENDERABLE_H
