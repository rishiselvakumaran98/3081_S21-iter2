
	/**
 *@file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "json_helper.h"
#include "delivery_simulation.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for creating entities.
 *
 * This class can be used as the base for all entities in the delivery system.
 * The overall design is up to you (the student), but all entities must implement
 * the IEntity interface.
 *
 * See the documentation for IEntity for more information
 */
class EntityBase : public IEntity {
 public:
	   EntityBase(){}

	 /**
	  * @brief this is a constructor for the entity base class. This serves as the base constructor for all classes that uses the EntityBase as their base class. Drone.h Package.h and Customer.h are the ones using this constructor so far.
	  * @param details_ the picojson that is received from the simmulation.
	  */
  	 EntityBase(const picojson::object& details_) {
		 		 position =JsonHelper::GetStdFloatVector(details_, "position") ;
				 			 direction = JsonHelper::GetStdFloatVector(details_, "direction");
							 				 name = JsonHelper::GetString(details_, "name");
											 					 radius = JsonHelper::GetDouble(details_, "radius");
//																 																 simulation = simulation_;
	 }

	 /**
	  * @brief distructor for entity base. If needed serves as base distructor for the sub-classes.
	  */
  virtual ~EntityBase() {
	  std::cout << "destroying entity base" << std::endl;
  }

  /**
   * @brief this function returns the  reference to the picojson object that is sent from the simulation.
   */
const picojson::object& GetDetails(){ return details; }

/**
 * @brief a getter for the Id of the picojson object. returning it in integer format.
 */
int GetId() const    {
	  return id;
  } //close getId

  /**
   * @brief getter for the name of the picojson object. Used to determine the type of the object.
   */
const std::string& GetName()   {
	  return name;
  } //close getter name

  /**
  * @brief this function returns a vector float containing the position of the object.
   */
const std::vector<float>& GetPosition() const   {
//	position_vec = Vector3D::ConvertToVector(position);
//	return position_vec;
	return position;
  } //close position getter

  /**
   * @brief this function returns a reference to a vector float that will contain the direction of the object.
   */
const std::vector<float>& GetDirection() const    {
	return direction;
  } //close getter for direction

  /**
   * @brief returns the float containing the radius of the object. This will be important to determine if the drone is on the delivery radius to drop off the order.
   */
float GetRadius() const    {
	  return radius;
  } //close getter for radius

  /**
   * @brief returns an integer that represents the version of the object.
   */
int GetVersion() const    {
	  return version;
  } //close getter for version

  /**
   * @brief this function returns true if the object is dynamic and false otherwise.
   */
bool IsDynamic() const    {
	  return dynamic;
  } //close getter for dynamic

  /**
   * @brief this function is used to setup the position field of objects.
   * @param v  a Vector3D argument to use as the position.
   */
  void SetPosition(Vector3D v) {
	  position = Vector3D::ConvertToVector(v);
  }

  /**
   * @brief sets up the direction field of the object.
   * @param v a Vector3D argument to be used as the direction.
   */
  void SetVDir(Vector3D v) {
	  direction  = Vector3D::ConvertToVector(v);
  }

  /**
   * @brief returns the position in Vector3D format.
   */
  Vector3D GetVPos() {
	  return Vector3D(position);
  }

  /**
   * @brief returns the direction in Vector3D format.
   */
  Vector3D GetVDir() {
	  return Vector3D(direction);
  }

  /**
   * @brief function used to setup the Id of the entity
   * @param Id integer to be used as the ID
   */
  void SetId(int Id) {
	  id = Id;
  }

  void SetDeliverySimulation(DeliverySimulation& simu) {
	  simulation = simu;
  }

 protected:
  picojson::object details;
  bool dynamic;
    int id;
  std::string name;
  float radius;
  int version;
//      Vector3D position;
//	      Vector3D direction;
		  std::vector<float> position;
		    std::vector<float> direction;
			DeliverySimulation& simulation = nullptr;
}; //close class 

}  // namespace csci3081


#endif  // ENTITY_BASE_H_
