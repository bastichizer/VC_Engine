//===============================================================
// Delegate.h
//===============================================================

#ifndef DELEGATE_H
#define DELEGATE_H

#include "Callback.h"

template<typename Ret, typename Param0>
class Delegate
{
public:
	template<typename T, typename Method>
	Delegate(T* object, Method method) : m_pCallback(new MethodCallback<Ret, Param0, T, Method>(object, method)) {}

	~Delegate() { delete m_pCallback; }

	Ret operator()(Param0 param0) { return m_pCallback->DoCallback(param0); }

private:
	BasicCallback<Ret, Param0>* m_pCallback;
};

#endif // DELEGATE_H
