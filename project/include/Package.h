/**
 *@file package.h
 */
#ifndef PACKAGE_H_
#define PACKAGE_H_

/**
 * include
 */
#include "entity_base.h"
#include "Vector3D.h"
#include "Customer.h"
#include "ISubject.h"
namespace csci3081 {
	/**
	 * @brief class responsible for the generation of packages.
	 */
	class Package : public csci3081::EntityBase, public ISubject  {
		public:
			/**
			 * @brief Default constructor for package objects. Besides the base constructor from entity base, this constructor also sets up the weight, person_to_receive and destination arguments that are particular to the package.
			 * @param details_  the picojson object from the EntityBase class.
			 */
			Package(const picojson::object& details_):csci3081::EntityBase(details_) {
				weight = 0.0;
				person_to_receive = nullptr;
				this->details = details_;
			} //close constructor

			/**
			 * @brief This is the argument constructor for the packages. It sets up the weight, person_to_receive and direction fields to arguments not to default values.
			 * @param w   double for the weight,  value of the package
			 * @param p a pointer to a Customer object
			 * @param v  a Vector3D that will be used for the direction of the package
			 * @param details_  the picojson object from the facade
			 */
			Package(double w, Customer* p, Vector3D v, picojson::object& details_):csci3081::EntityBase(details_) {
				weight = w;
				person_to_receive = p;
				this->SetVDir(v); //this overwrites the direction from the picojson object
				details = details_;
			}//close constructor

			/**
			 * @brief function to setup the weight field.
			 * @param w double to be used on the weight field.
			 */
			void SetWeight(double w) {weight = w;}

			/**
			 * @brief This function returns the double value of the weight field.
			 */
			double GetWeight() {return weight;}

			/**
			 * @brief This function sets up the person_to_receive field to the argument passed.
			 * @param p Pointer to a customer object to be used as the person_to_receive the package.
			 */
			void SetCustomer(Customer* p) { person_to_receive = p;}

			/**
			 * @brief returns the pointer to the Customer object that is the person_to_receive field.
			 */
			Customer* GetRecipient() {return person_to_receive;}
			/**
			 * @brief The function intializes the observer pattern to notify that the package is scheduled
			 */
			void OnSchedule();
			/**
			 * @brief The function intializes the observer pattern to notify that the package is picked by the entities
			 */
			void OnPickUp();
			/**
			 * @brief The function intializes the observer pattern to notify that the package is dropped/delivered by the entities
			 */
			void OnDropOff();


		private:
			double weight;
			Customer* person_to_receive;
			Vector3D destination;

}; //close class

} //close namespace 

#endif