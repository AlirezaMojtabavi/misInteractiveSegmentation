#pragma once
#include "BusinessEntities\Point.h"


namespace parcast
{
	class TransformMatrixSetter
	{
	public:
		TransformMatrixSetter(
			const parcast::VectorD3& xAxis,
			const parcast::VectorD3& yAxis,
			const parcast::VectorD3& zAxis,
			const parcast::PointD3& trans) :
			m_XAxis(xAxis),
			m_YAxis(yAxis),
			m_ZAxis(zAxis),
			m_Trans(trans)
		{
		}

		void operator()(double matrixElemet[16])
		{
			//x axis:
			matrixElemet[0] = m_XAxis[0];
			matrixElemet[4] = m_XAxis[1];
			matrixElemet[8] = m_XAxis[2];

			//y axis
			matrixElemet[1] = m_YAxis[0];
			matrixElemet[5] = m_YAxis[1];
			matrixElemet[9] = m_YAxis[2];

			//z axis
			matrixElemet[2] = m_ZAxis[0];
			matrixElemet[6] = m_ZAxis[1];
			matrixElemet[10] = m_ZAxis[2];

			//translation
			matrixElemet[3] = m_Trans[0];
			matrixElemet[7] = m_Trans[1];
			matrixElemet[11] = m_Trans[2];

			matrixElemet[12] = 0.0;
			matrixElemet[13] = 0.0;
			matrixElemet[14] = 0.0;
			matrixElemet[15] = 1.0;
		}

	private:
		const VectorD3 m_XAxis;
		const VectorD3 m_YAxis;
		const VectorD3 m_ZAxis;
		const PointD3 m_Trans;
	};
}