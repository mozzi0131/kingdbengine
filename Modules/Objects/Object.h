#ifndef __MODULES_OBEJCTS_OBJECT_H__
#define __MODULES_OBEJCTS_OBJECT_H__


#include <stdint.h>
#include <set>

// Base Object Class

class Object
{
	friend class ObjectManager;

	enum class EObjectGCState {
		/*should be GCed*/ None = 0,
		/*Referenced from other object, do not check child*/ ReferencedAndNotChecked = 1,
		/*Referenced from other object, checked all child*/ ReferencedAndCheckedChildren = 2,
		/*Root Object should not be garbage collected and change to other state. */ ROOT = 3,

		// GC (Tri-color marking): https://www.slideshare.net/QooJuice/ue4-garbage-collection-2
		// 1) 모두 None으로 초기화
		// 2) Root에서 접근 가능한 객체를 ReferencedAndNotChecked로 변경
		// 3) ReferencedAndNotChecked에서 참조하는 객체를 ReferencedAndNotChecked로 변경,
		//	  ReferencedAndNotChecked를 ReferencedAndCheckedChildren로 변경
		// 4) ReferencedAndNotChecked인 객체가 존재하지 않으면 None인 객체들을 메모리 해제
	};
private:
	// Object::CreateObject() 외의 생성 막기
	Object();
	~Object();

	void reset();
	
	void setObjectGCState(EObjectGCState newState);
	bool isObjectGCState(EObjectGCState gcState) const;

	void addChild(Object* newChild);
	void removeChild(Object* targetChild);
	void clearOuter();
	void changeOuter(Object* newOuter);
	void clearChildren();
	
private:
	// 오브젝트 고유 Id
	uint32_t ObjectId = 0;

	// GC를 위한 오브젝트 스테이트
	EObjectGCState GcState = EObjectGCState::None;

	// 현재 오브젝트를 가르키는 부모 Object
	Object* Outer = nullptr;

	// 자신을 Outer로 가지는 자식 오브젝트
	std::set<Object*> Children;

public:
	
	uint32_t GetObjectId() const { return ObjectId; }
	Object* GetOuter() const { return Outer; }
	void SetOuter(Object* newOuter);

	const std::set<Object*>& GetChildren() { return Children; }
	int32_t GetChildrenNum() { return Children.size(); }

	void Destroy();

	bool operator==(const Object& other) const {
		return (other.ObjectId == ObjectId);
	}

	bool operator!=(const Object& other) const {
		return !(*this == other);
	}

	static Object* CreateObject(Object* outer);
};

#endif //__MODULES_OBEJCTS_OBJECT_H__