
#include "ObjectManager.h"
#include <vector>

// for log
#include "KDBLog.h"

ObjectManager* ObjectManager::ObjectManagerInstance = nullptr;
Object* ObjectManager::Root = nullptr;

ObjectManager::ObjectManager() {
	Root = new Object();
	//ROOT로 상태 지정
	Root->setObjectGCState(Object::EObjectGCState::ROOT);
	KDB_LOG("Root Created");

	Root->ObjectId = ROOT_ID;
	EveryObjects.insert(std::pair<uint32_t, Object*>(ROOT_ID, Root));
	// ROOT_ID부터 시작해 오브젝트 추가될 때마다 ++한다.
	ObjectIdIssuer = ROOT_ID;
}

ObjectManager* ObjectManager::Get() {
	if (ObjectManagerInstance == nullptr)
	{
		ObjectManagerInstance = new ObjectManager();
	}
	
	return ObjectManagerInstance;
}

void ObjectManager::ClearManager() {
	ObjectManager* NowManager = Get();
	NowManager->clearManager();

	delete NowManager;

	ObjectManagerInstance = nullptr;
}

uint32_t ObjectManager::AddObjectToManager(Object* newObject) {
	ObjectIdIssuer++;

	EveryObjects.insert(std::pair<uint32_t, Object*>(ObjectIdIssuer, newObject));

	return ObjectIdIssuer;
}

void ObjectManager::RemoveFromObjectManager(Object* removingObject) {
	EveryObjects.erase(removingObject->GetObjectId());
}

void ObjectManager::AddObjectToRootChild(Object* targetObject) {
	targetObject->changeOuter(Root);
	targetObject->setObjectGCState(Object::EObjectGCState::ReferencedAndNotChecked);
}

void ObjectManager::GarbageCollectObjects() {
	// 1) ReferencedAndNotChecked를 찾음
	//		-> 없을 경우 None인 객체들을 찾아 메모리 해제(GC),
	//		   그리고 모두 None으로 상태를 초기화해줌
	//			(루트부터 시작하는건... 어떻하지... 바로 루트가 참조하는 애들을 변경해줘야 하나)

	// 2) 해당 오브젝트가 Outer인 오브젝트들을 해쉬맵에서 찾아 ReferencedAndNotChecked로 변경, 자기 자신은 ReferencedAndCheckedChildren로 변경

	std::map<uint32_t, Object*>::iterator checkStartObjectIter = findReferencedAndNotCheckedObject();
	if (checkStartObjectIter == EveryObjects.end()) {
		// gc 진행. 
		std::map<uint32_t, Object*> leftObjects;
		std::vector<Object*> removingObjects;
		removingObjects.reserve(EveryObjects.size() - 1);
		for (auto iter = EveryObjects.begin(); iter != EveryObjects.end(); ++iter) {
			if ((*iter).second->isObjectGCState(Object::EObjectGCState::None)) {
				removingObjects.push_back((*iter).second);
			}
			else {
				leftObjects.insert(*iter);
			}
		}

		EveryObjects.swap(leftObjects);

		// removingObjects 메모리 해제
		for (uint32_t i = 0; i< removingObjects.size(); i++) {
			KDB_LOG("object Id %d Removed bg GC", removingObjects[i]->GetObjectId());

			delete removingObjects[i];			
		}

		// root가 outer인 애들을 즉시 ReferencedAndNotChecked로 변경
		const std::set<Object*>& childrenSet = Root->GetChildren();

		for (auto iter = childrenSet.begin(); iter != childrenSet.end(); ++iter) {
			// for testing
			if (!(*iter)->isObjectGCState(Object::EObjectGCState::None) && !(*iter)->isObjectGCState(Object::EObjectGCState::ROOT)) {
				KDB_LOG("double referenced %d", (*iter)->GetObjectId());
			}

			(*iter)->setObjectGCState(Object::EObjectGCState::ReferencedAndNotChecked);
		}
	}
	else {
		// 레퍼런스 체크 진행
		constexpr int32_t MAX_REFERENCE_CHECK_ITEM_NUM = 100;
		int32_t refCheckCount = 0;

		for (checkStartObjectIter; (checkStartObjectIter != EveryObjects.end() && refCheckCount < MAX_REFERENCE_CHECK_ITEM_NUM); ++checkStartObjectIter) {
			Object* checkingObject = (*checkStartObjectIter).second;

			if (checkingObject->GetOuter() == nullptr) {
				continue;
			}

			const std::set<Object*> childrenSet = checkingObject->GetChildren();

			for (auto iter = childrenSet.begin(); iter != childrenSet.end(); ++iter) {
				// for testing
				if (!(*iter)->isObjectGCState(Object::EObjectGCState::None) && !(*iter)->isObjectGCState(Object::EObjectGCState::ROOT)) {
					KDB_LOG("double referenced %d", (*iter)->GetObjectId());
				}

				if ((*iter)->isObjectGCState(Object::EObjectGCState::None)) {
					(*iter)->setObjectGCState(Object::EObjectGCState::ReferencedAndNotChecked);
				}
			}

			checkingObject->setObjectGCState(Object::EObjectGCState::ReferencedAndCheckedChildren);
			refCheckCount++;
		}
	}

	KDB_LOG("GC Finished");
}

void ObjectManager::clearManager() {
	// 전체 오브젝트 메모리 해제
	for (auto iter = EveryObjects.begin(); iter != EveryObjects.end(); iter++) {
		delete (iter->second);
	}

	EveryObjects.empty();
	Root = nullptr;

	//// hash bucket 빈것 확인
	//if (Root->GetChildrenNum() != 0)
	//{
	//	std::cout << "not all object cleared!!!";
	//}
}

std::map<uint32_t, Object*>::iterator ObjectManager::findReferencedAndNotCheckedObject() {
	std::map<uint32_t, Object*>::iterator iter = EveryObjects.begin();

	//std::iterator<Object*> a = EvetyObjects.begin();
	//std::_Tree<Object*>::iterator a = EvetyObjects.begin();

	for (iter; iter != EveryObjects.end(); ++iter) {
		if ((*iter).second->isObjectGCState(Object::EObjectGCState::ReferencedAndNotChecked)) {
			return iter;
		}
	}

	// ReferencedAndNotChecked인 오브젝트가 없다면 gc할때임
	return iter;
}