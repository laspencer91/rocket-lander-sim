#ifndef IUPDATEABLE_H
#define IUPDATEABLE_H

class IUpdateable {
public:
    virtual ~IUpdateable() = default;
    virtual void Update(float dt) = 0;
};

#endif //IUPDATEABLE_H
