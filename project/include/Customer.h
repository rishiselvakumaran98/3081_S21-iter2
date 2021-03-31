/**
 * @file Customer.h
 */
#ifndef CUSTOMER_H_
#define CUSTOMER_H_

/*******************************************************************************
 * include
 */
#include "Vector3D.h"
#include "entity_base.h"
namespace csci3081 {
   /*******************************************************************************
    * Class Definitions
	*/
   /**
    * @brief The base class for creating customers.
	 * enherits from the upper class entity class, using its constructor to generate new customers
	 */
class Customer : public csci3081::EntityBase {

public:
	/**
	 * @brief constructor for the customer class. Also sets position accordingly as the customers need to have a set position to perform their actions of receiving packages.
	 * @param  details_ the main constructor from entity_base to get the picojson details for the new customer being created
	 */
	Customer(const picojson::object& details_):EntityBase(details_){
		details = details_;
	}

};//close class 
}//end of the namespace 
#endif

