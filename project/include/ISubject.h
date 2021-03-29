#include <EntityProject/facade/delivery_system.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "json_helper.h"
#include <vector>

namespace csci3081 {

	class ISubject {
	private:
		std::vector<IEntityObserver*> observers_;
		
	public:
		void AddObserver(IEntityObserver* observer_to_be_added);
		void RemoveObserver(IEntityObserver* observer_to_be_removed);

	protected:
		void OnEvent(const picojson::value& object, const IEntity& entity_);

	}; //close class.
	
}//close namespace 