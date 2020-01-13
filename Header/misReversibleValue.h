#pragma once

// The misReversibleValue class template implements RAII logic for the value of a certain variable. It makes sure that the 
// associated variable is reverted to its initial value (its value at the time of creation of the misReversibleValue object)
// when the misReversibleValue object is destroyed (leaving the scope). Creation and destruction of the managed variable 
// is obviously not managed by this class, only its value during the lifetime of the misReversibleValue object. For this reason, 
// this class receives and holds a reference to the associated variable that is created before the misReversibleValue object.
template <typename ValueType>
class misReversibleValue
{
public:
	misReversibleValue(ValueType& associatedVariable)
		: m_AssociatedVariable(associatedVariable), m_InitialValue(associatedVariable), m_ShouldRevert(true)
	{
	}

	virtual ~misReversibleValue(void)
	{
		if (m_ShouldRevert)
			m_AssociatedVariable = m_InitialValue;
	}

	// Determines whether the associated variable under protection should automatically be reverted to its initial value 
	// at the end of scope of this object.
	void SetShouldRevert(bool shouldRevert)
	{
		m_ShouldRevert = shouldRevert;
	}

private:
	// RAII demands that the protector object have specific copy semantics.
	misReversibleValue(const misReversibleValue&);
	misReversibleValue& operator=(const misReversibleValue&);

	ValueType& m_AssociatedVariable;	// Associated variable being under protection of this object.
	ValueType m_InitialValue;	// Value of the associated variable at the time of creation of this object.
	bool m_ShouldRevert;	// See SetShouldRevert()
};

