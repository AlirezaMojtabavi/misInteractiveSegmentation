#pragma once

#include <turtle/mock.hpp>

#include "ITimedValidator.h"
//
//template< typename T >
//MOCK_BASE_CLASS(MockTimedValidator, ITimedValidator<T>)
//{
//	typename MOCK_NON_CONST_METHOD(Value, 0, T &());
//	typename MOCK_CONST_METHOD(Value, 0, const T& ());
//	MOCK_CONST_METHOD(IsValid, 0, bool ());
//	MOCK_CONST_METHOD(IsTimed, 0, bool ());
//	MOCK_CONST_METHOD(RemainingLifeTime, 0, double ());
//};

//template< typename T >
//struct base_class
//{
//	virtual void VoidFunc();
//	virtual void OneParamFunc(T param);
//	virtual T ReturnTFunc();
//	virtual T& ReturnTRefFunc();
//	virtual const T& ReturnTConstRefFunc() const;
//};
//
//template< typename SubjectType >
//MOCK_BASE_CLASS( mock_class, base_class< SubjectType > )
//{
//	MOCK_NON_CONST_METHOD(VoidFunc, 0, void ());
//	MOCK_NON_CONST_METHOD(OneParamFunc, 0, void (typename SubjectType param));
//	MOCK_NON_CONST_METHOD(ReturnTFunc, 0, typename SubjectType ());
//	MOCK_NON_CONST_METHOD(ReturnTRefFunc, 0, typename SubjectType& ());
//	MOCK_NON_CONST_METHOD(ReturnTConstRefFunc, 0, const typename SubjectType& ());
//};
//
//BOOST_AUTO_TEST_CASE( demonstrates_instantiating_a_template_derived_mock_class )
//{
//	mock_class< int > c;
//}