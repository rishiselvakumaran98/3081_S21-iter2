#include "ISubject.h"

namespace csci3081 {
	void ISubject::AddObserver(IEntityObserver* observer_to_be_added) {
		observers_.push_back(observer_to_be_added);
	}

	void ISubject::RemoveObserver(IEntityObserver* observer_to_be_removed) {
		for (int i = 0; i < observers_.size(); i++) {
			if (observers_[i] = observer_to_be_removed) {
				observers_.erase(observers_.begin()+i);
				break;
			}//close if
		}//close for loop
	} //close function

	void ISubject::OnEvent(const picojson::value& object, const IEntity& entity_) {
		for (int i = 0; i < observers_.size(); i++) {
			(observers_[i])->OnEvent(object, entity_);
			std::cout << "calling observer : " << i << std::endl;
		}	// close for loop 
	} // close method 
}//end of namespace 