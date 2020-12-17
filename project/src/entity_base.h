#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

#include <EntityProject/facade/delivery_system.h>

namespace csci3081 {

class EntityBase : public IEntity {
 public:
    virtual ~EntityBase() {}

    const picojson::object& GetDetails() { return details_; }

 protected:
    picojson::object details_;
};

}  // namespace csci3081


#endif  // ENTITY_BASE_H_
