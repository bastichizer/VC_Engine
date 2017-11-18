//===============================================================
// Callback.h
//===============================================================

#ifndef CALLBACK_H
#define CALLBACK_H

template<typename Ret, typename Param0>
class BasicCallback
{
public:
	virtual Ret DoCallback(Param0 param0) = 0;
};

template <typename Ret, typename Param0, typename T, typename Method>
class MethodCallback : public BasicCallback<Ret, Param0>
{
public:
	MethodCallback(void* object, Method method) : m_pObject(object), m_method(method) {}

	virtual Ret DoCallback(Param0 param0)
	{
		T* obj = static_cast<T*>(m_pObject);
		return (obj->*m_method)(param0);
	}

private:
	void* m_pObject;
	Method m_method;
};

#endif // CALLBACK_H

