#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

#include <EntityProject/facade/delivery_system.h>

namespace csci3081 {

class EntityBase : public IEntity {
 public:
    virtual ~EntityBase() {}
};

class Customer : public EntityBase, public ICustomer {
 public:
    virtual ~Customer() {}
    
    IEntity* AsEntity() { return this; }
};

class Package : public EntityBase, public IPackage {
 public:
    virtual ~Package() {}
    
    IEntity* AsEntity() { return this; }
};

}  // namespace csci3081


#endif  // ENTITY_BASE_H_
