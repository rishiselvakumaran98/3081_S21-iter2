#include "Package.h"

namespace csci3081 {

	void Package::OnSchedule() {
		picojson::object obj = JsonHelper::CreateJsonObject();
		JsonHelper::AddStringToJsonObject(obj, "type", "notify");
		JsonHelper::AddStringToJsonObject(obj, "value", "scheduled");
		const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
		OnEvent(val, *this);
	}


	void Package::OnPickUp() {
		picojson::object obj = JsonHelper::CreateJsonObject();
		JsonHelper::AddStringToJsonObject(obj, "type", "notify");
		JsonHelper::AddStringToJsonObject(obj, "value", "en route");
		const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
		OnEvent(val, *this);
	}



	void Package::OnDropOff() {
		picojson::object obj = JsonHelper::CreateJsonObject();
		JsonHelper::AddStringToJsonObject(obj, "type", "notify");
		JsonHelper::AddStringToJsonObject(obj, "value", "delivered");
		const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
		OnEvent(val, *this);
	}


}//close namespace 