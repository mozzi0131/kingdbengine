
#include "Object.h"
#include "ObjectManager.h"

#include "KDBLog.h"

Object::Object() {
	reset();
}

Object::~Object() {
	KDB_LOG("object Id %d destroyed", ObjectId);
	reset();
}

void Object::reset() {
	ObjectId = 0;
	Outer = nullptr;
	GcState = EObjectGCState::None;
}

void Object::setObjectGCState(EObjectGCState newState) {
	// root일 경우 상태 변경 불가능
	if (GcState != EObjectGCState::ROOT)
	{
		GcState = newState;
	}
}

bool Object::isObjectGCState(EObjectGCState gcState) const {
	return (GcState == gcState);
}

void Object::addChild(Object* newChild) {
	Children.insert(newChild);
}

void Object::removeChild(Object* targetChild) {
	Children.erase(targetChild);
}

void Object::clearOuter() {
	// 기존 outer
	if (Outer)
	{
		Outer->removeChild(this);
	}
	Outer = nullptr;
}

void Object::changeOuter(Object* newOuter) {
	// 기존 outer
	if (Outer) {
		Outer->removeChild(this);
	}
	
	SetOuter(newOuter);
}

void Object::clearChildren() {
	for (auto iter = Children.begin(); iter != Children.end(); ++iter) {
		(*iter)->Outer = nullptr;
	}

	Children.empty();
}

Object* Object::CreateObject(Object* outer) {
	Object* createdObject = new Object();

	uint32_t createdObjectId = ObjectManager::Get()->AddObjectToManager(createdObject);
	KDB_LOG("object Id %d Created", createdObjectId);

	createdObject->ObjectId = createdObjectId;

	if (outer != nullptr) {
		outer->addChild(createdObject);
	}
	createdObject->SetOuter(outer);
	return createdObject;
}

void Object::SetOuter(Object* newOuter) {
	// todo : 새 outer의 부모(recursive)중 자신이 있는지 확인 필요
	Outer = newOuter;
}

void Object::Destroy() {
	// 자신의 Outer의 Children에서 자신 삭제
	if (Outer != nullptr) {
		Outer->removeChild(this);
	}

	// 자신의 child의 outer 삭제

	clearChildren();
	ObjectManager::Get()->RemoveFromObjectManager(this);

	delete this;
}