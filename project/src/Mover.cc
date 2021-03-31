#include "Mover.h"

namespace csci3081 {


void Mover::OnIdle() {
	picojson::object obj = JsonHelper::CreateJsonObject();
	JsonHelper::AddStringToJsonObject(obj, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj, "value", "idle");
	const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
	simulation->OnEvent(val, *this);
}

void Mover::OnMove() {
	picojson::object obj = JsonHelper::CreateJsonObject();
	JsonHelper::AddStringToJsonObject(obj, "type", "notify");
	JsonHelper::AddStringToJsonObject(obj, "value", "moving");
	JsonHelper::AddStdVectorVectorFloatToJsonObject(obj, "value", *currentRout);
	const picojson::value val= JsonHelper::ConvertPicojsonObjectToValue(obj);
	simulation->OnEvent(val, *this);
}

}//close namespace