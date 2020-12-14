#ifndef __MODULES_OBEJCTS_OBJECT_MANAGER_H__
#define __MODULES_OBEJCTS_OBJECT_MANAGER_H__

#include <stdint.h>
#include <map>



#include "Object.h"

////////////////////////////////////
//
// 오브젝트 생성시 Outer을 함께 줘서 ObjectArr에 추가함과 동시에 OuterMap에 추가
// 1번 ObjectId를 가지는 RootObject 필요.
//
//
//

class ObjectManager
{
private:
	ObjectManager();

private:
	static ObjectManager* ObjectManagerInstance;
	static Object* Root;

	static const uint32_t ROOT_ID = 1;

	// 현재 존재하는 전체 object가 포함된 map. key : objectId
	std::map<uint32_t, Object*> EveryObjects;

	uint32_t ObjectIdIssuer;

public:
	static ObjectManager* Get();
	static void ClearManager();

	// @ return : ObjectId
	uint32_t AddObjectToManager(Object* newObject);
	void RemoveFromObjectManager(Object* removingObject);

	void AddObjectToRootChild(Object* targetObject);

	void GarbageCollectObjects();

private:
	void clearManager();

	// ~for gc
	std::map<uint32_t, Object*>::iterator findReferencedAndNotCheckedObject();
	// ~for gc
};


#endif //__MODULES_OBEJCTS_OBJECT_MANAGER_H__