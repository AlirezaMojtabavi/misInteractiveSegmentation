#pragma once

namespace parcast
{

	template <typename T>
	class ParameterCapturer
	{
	public:
		ParameterCapturer(T & capturedParameter) : m_CapturedParameter(capturedParameter) { }
		void operator()(const T & receivedParameter) { m_CapturedParameter = receivedParameter; }

	private:
		T & m_CapturedParameter;
	};

}