#pragma once
template<typename Pointer> 
class PointerWrapper;
//template<typename Pointer> 
//Pointer *operator->();

template<typename Pointer>
class PointerWrapper
{
private:
	
	
public:
	Pointer* WrappedPointer;

	PointerWrapper() { WrappedPointer = nullptr; }

	template<typename Pointer>
	PointerWrapper(Pointer* const RawPointer) {
		//Pointer* temp = RawPointer;
		WrappedPointer = RawPointer;
	}

	template<typename Pointer>
	Pointer* operator-> () const{
		return WrappedPointer;
	}
	
	//friend Pointer *operator-> <>();


	~PointerWrapper() { delete WrappedPointer; }

	//template<typename Pointer>
	//void operator= (Pointer const &newPointer) {
	//	temp = newPointer;
	//}

	template<typename Pointer>
	void operator= (Pointer* const newPointer) {
		WrappedPointer = newPointer;
	}

	template<typename Pointer>
	void operator= (const PointerWrapper<Pointer> &copy) {
		WrappedPointer = copy.WrappedPointer;
	}



	//template<typename Pointer>
	//void operator= (Pointer &const newObject) {
	//	WrappedPointer = newObject;
	//}

	//template<typename Pointer>
	Pointer* get() {
		return WrappedPointer;
	}


};




