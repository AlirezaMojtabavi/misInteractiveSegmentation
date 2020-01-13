#pragma once

// Provides a non-thread-safe wrapper around a numeric (float, double, int, ...) value that is resistant to jitter. That is, small
// changes to the value, rather than changing the value itself, affect the average of its previous values. Small changes are those
// that have a smaller magnitude than the standard deviation of the recorded history for the value. Large changes clear all history
// for the value and set the value. The length of the history recorded for the value is alterable. Greater lengths provide further
// stability but might impose extra overhead due to statistics performed at every assignment operation. When the value history has
// less values than specified by history length, the new average is taken as the dejitterized value, but the deviation is not taken
// into account.
// ValueType must support and be closed with regard to arithmetic operations.
// Warning: misDejitterizedValue is NOT thread-safe and if access from multiple threads, it MUST be mutually excluded.
// VT = Value Type
template <typename VT>
class misDejitterizedValue
{
public:
	typedef VT ValueType;

	// Creates a misDejitterizedValue with the default value and an empty history.
	misDejitterizedValue() : m_MaximumHistoryLength(5)
	{
		m_WeightFunction = &misDejitterizedValue::DefaultWeightFunction;
	};

	// Creates and initializes a misDejitterizedValue with the specified value.
	misDejitterizedValue(const ValueType & other)
		: m_Value(other), m_MaximumHistoryLength(5)
	{
		m_WeightFunction = &misDejitterizedValue::DefaultWeightFunction;
		RecordNewValue(other);
	}

	// Convenience operator synonymous to SetValue()
	misDejitterizedValue & operator= (const	ValueType &other)
	{
		return SetValue(other);
	}

	// Convenience operator synonymous to GetValue()
	operator ValueType() const
	{
		return m_Value;
	}

	// Assigns the specified value to the misDejitterizedValue after performing necessary statistics on the value history and the 
	// magnitude of the requested change.
	misDejitterizedValue &SetValue(const ValueType &other)
	{
		RecordNewValue(other);	
		ComputeHistoryAverage(m_Value);
		return *this;
	}

	// Gets the current dejitterized value stored.
	ValueType GetValue() const
	{
		return m_Value;
	}
	const std::deque<ValueType>& GetValueHistorty()
	{
		return m_ValueHistory;
	}

	// Set the function used to calculate weight for element of the specified index within the value history. Lower indexes refer
	// to more recent values assigned. The total count might be important for some functions.
	void SetWeightFunction(std::function<double (int index, int totalCount)> weightFunc)
	{
		m_WeightFunction = weightFunc;
		ComputeNormalizedWeights();
	}

	std::function<double (int index, int totalCount)> GetWeightFunction()
	{
		return m_WeightFunction;
	}

	// Sets the maximum number of items too keep in the value history.
	void SetMaximumHistoryLength(int maxHistoryLength)
	{
		m_MaximumHistoryLength = maxHistoryLength;
	}

	void ClearValueHistory()
	{
		m_ValueHistory.clear();
	}


 	void SetZero(ValueType val) { m_Zero = val; }
private:
 
	ValueType m_Zero = ValueType();
	// Computes the normalized weights for all the elements within the history. It must be called if the history length or the
	// weight function is changed. It populates m_Weights.
	void ComputeNormalizedWeights()
	{
		auto histLen = m_ValueHistory.size();
		m_Weights.resize(histLen);
		double totalWeight = 0;
		for (int i = 0; i < histLen; i++)
		{
			m_Weights[i] = m_WeightFunction(i, histLen);
			totalWeight += m_Weights[i];
		}
		for (auto & weight : m_Weights)	// Normalize weights
			weight /= totalWeight;
	}

	// Computes the weighted average of the values within the history based on normalized weights within m_Weights.
	void ComputeHistoryAverage(ValueType &average)
	{
		if (m_Weights.size() != m_ValueHistory.size())
			ComputeNormalizedWeights();
		average = std::inner_product(m_Weights.cbegin(), m_Weights.cend(), m_ValueHistory.cbegin(), m_Zero);
	}

	// Pushes a new value to the front of the history (as the most recent value), updates the history length and assures that it
	// will not exceed MaximumHistoryLength
	void RecordNewValue(const ValueType &newValue)
	{
		m_ValueHistory.push_front(newValue);	// The most recent value has lower index within the weights vector
		while (m_ValueHistory.size() > m_MaximumHistoryLength)	// History full:
			m_ValueHistory.pop_back();	// Get rid of the least recent value
	}

	static double DefaultWeightFunction(int index, int totalCount)
	{
		return std::exp(-index / 150.0);
	}

	ValueType m_Value;	// Current dejitterized value
	std::deque<ValueType> m_ValueHistory;	// The last set of values assigned.
	std::vector<double> m_Weights;	// The normalized weights assigned to each positioned element within the history.
	int m_MaximumHistoryLength;	// See SetMaximumHistoryLength

	// The function used to calculate average weights for each history element.
	std::function<double (int index, int totalCount)> m_WeightFunction;	
};

typedef misDejitterizedValue<double> misDejitterizedDouble;
typedef misDejitterizedValue<float> misDejitterizedFloat;
typedef misDejitterizedValue<int> misDejitterizedInt;