/**********************************************************************
 *                                                                    *
 * tgt - Tiny Graphics Toolbox                                        *
 *                                                                    *
 * Copyright (C) 2006-2008 Visualization and Computer Graphics Group, *
 * Department of Computer Science, University of Muenster, Germany.   *
 * <http://viscg.uni-muenster.de>                                     *
 *                                                                    *
 * This file is part of the tgt library. This library is free         *
 * software; you can redistribute it and/or modify it under the terms *
 * of the GNU Lesser General Public License version 2.1 as published  *
 * by the Free Software Foundation.                                   *
 *                                                                    *
 * This library is distributed in the hope that it will be useful,    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU Lesser General Public License for more details.                *
 *                                                                    *
 * You should have received a copy of the GNU Lesser General Public   *
 * License in the file "LICENSE.txt" along with this library.         *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 **********************************************************************/

#ifndef TGT_MATRIX_H
#define TGT_MATRIX_H

#include <cstring>

//#include "tgt/config.h"
#include "tgt/vector.h"
#include "tgtassert.h"
#define TGTROTATE(a,i,j,k,l) g=a[i][j];h=a[k][l];a[i][j]=g-s*(h+g*tau);\
	a[k][l]=h+s*(g-h*tau)
#define VTK_MAX_ROTATIONS 20
/*
    FIXME build a SSE-optimized mat4
*/

/*
    Performance remarks:

    - Most functions and operators are programmed with loops.
    Compilers can unroll that.
    gcc for instance will do this with -funroll-loops.

    - Modern compilers (gcc 4.x and icc) can even vectorize these loops
    and do these caclulations with SIMD-instructions.

    - Almost all functions are inline!
    This can have signifcant advantages in codegeneration

    - The return-value optimization which is supported by all
    modern compilers (gcc, icc and msvc for instance)
    will optimize unnecessary constructor-overhead away.

    - it could be usefull to use options like -funroll-loops
*/

namespace tgt {

/**
    Matrix2 class. Works basicly like the matrix stuff in GLSL.
    But remember that this is a ROW-MATRIX and NOT a COL-MATRIX
    like in OpenGL or GLSL respectively.
*/
template<class T>
struct Matrix2 {
    typedef T ElemType;

    enum {
        size = 4,
        cols = 2,
        rows = 2
    };
    typedef Vector2<T> RowType;

    union {
        struct {
            T t00, t01;
            T t10, t11;
        };
        T elemRowCol[2][2];
        T elem[4];
    };

/*
    constructors
*/
    /// default constructor
    Matrix2() {}
    /// Init all elements with the same value
    explicit Matrix2(T t) {
        for (size_t i = 0; i < size; ++i)
            elem[i] = t;
    }
    /// Init with another Matrix of another type
    template<class U>
    Matrix2(const Matrix2<U>& m) {
        for (size_t i = 0; i < m.size; ++i)
            elem[i] = T(m.elem[i]);
    }
    /// Init from array with equal size
    explicit Matrix2(const T* t) {
        for (size_t i = 0; i < size; ++i)
            elem[i] = t[i];
    }
    /// Init componentwisely
    Matrix2(T _t00, T _t01,
            T _t10, T _t11) {
        t00 = _t00; t01 = _t01;
        t10 = _t10; t11 = _t11;
    }
    /// Init with two Vector2
    Matrix2(const Vector2<T>& v1, const Vector2<T>& v2) {
        for (size_t i = 0; i < v1.size; ++i)
            elem[0*rows + i] = v1.elem[i];
        for (size_t i = 0; i < v2.size; ++i)
            elem[1*rows + i] = v2.elem[i];
    }

/*
    create special matrices
*/

    static const Matrix2<T> zero;
    static const Matrix2<T> identity;

    static Matrix2<T> createZero() {
        return zero;
    }

    static Matrix2<T> createIdentity() {
        return identity;
    }

    static Matrix2<T> createScale(const Vector2<T>& v) {
        Matrix2<T> result = identity;
        result.t00 = v.elem[0];
        result.t11 = v.elem[1];
        return result;
    }

    /**
     * Creates a planar rotation with a given \p angle in \em RADIAN AND NOT \em DEGREE.
     *
     * @param angle The angle of rotation in \em radian.
     */
    static Matrix2<T> createRotation(T angle) {
        Matrix2<T> result = identity;
        result.t00 =  cos(angle);
        result.t01 = -sin(angle);
        result.t10 =  sin(angle);
        result.t11 =  cos(angle);
        return result;
    }

/*
    index operators
*/
    /*
        The C++ standard forbids classes with non trivial constructors
        as union members. Thus this hack provides functionality similar
        to the GLSL matrix index operator.
    */
    /// return arbitrary row-vector similar to GLSL. <br>
    /// BUT REMEMBER: GLSL gives you COLS NOT ROWS!
    const Vector2<T>& operator [] (size_t i) const {
        //tgtAssert(i < size, "i must be less than size");
        return *((Vector2<T>*) elemRowCol[i]);
    }
    /// return arbitrary row-vector similar to GLSL. <br>
    /// BUT REMEMBER: GLSL gives you COLS NOT ROWS!
    Vector2<T>& operator [] (size_t i) {
        //tgtAssert(i < size, "i must be less than size");
        return *((Vector2<T>*) elemRowCol[i]);
    }
};

/*
    init statics
*/

template<class T>
const Matrix2<T> Matrix2<T>::zero = Matrix2<T>
(
    T(0), T(0),
    T(0), T(0)
);

template<class T>
const Matrix2<T> Matrix2<T>::identity = Matrix2<T>
(
    T(1), T(0),
    T(0), T(1)
);

//

/**
    Matrix3 class. Works basicly like the matrix stuff in GLSL.
    But remember that this is a ROW-MATRIX and NOT a COL-MATRIX
    like in OpenGL or GLSL respectively.
*/
template<class T>
struct Matrix3 {
    typedef T ElemType;

    enum {
        size = 9,
        cols = 3,
        rows = 3
    };
    typedef Vector3<T> RowType;

    union {
        struct {
            T t00, t01, t02;
            T t10, t11, t12;
            T t20, t21, t22;
        };
        T elemRowCol[3][3];
        T elem[9];
    };

/*
    constructors
*/

    /// default constructor
    Matrix3() {}
    /// Init all elements with the same value
    explicit Matrix3(T t) {
        for (size_t i = 0; i < size; ++i)
            elem[i] = t;
    }
    /// Init with another Matrix of another type
    template<class U>
    Matrix3(const Matrix3<U>& m) {
        for (size_t i = 0; i < m.size; ++i)
            elem[i] = T(m.elem[i]);
    }
    /// Init from array with equal size
    explicit Matrix3(const T* t) {
        for (size_t i = 0; i < size; ++i)
            elem[i] = t[i];
    }
    /// Init componentwisely
    Matrix3(T _t00, T _t01, T _t02,
            T _t10, T _t11, T _t12,
            T _t20, T _t21, T _t22) {
        t00 = _t00; t01 = _t01; t02 = _t02;
        t10 = _t10; t11 = _t11; t12 = _t12;
        t20 = _t20; t21 = _t21; t22 = _t22;
    }
    /// Init with three Vector3
    Matrix3(const Vector3<T>& v1, const Vector3<T>& v2, const Vector3<T>& v3) {
        for (size_t i = 0; i < v1.size; ++i)
            elem[0*rows + i] = v1.elem[i];
        for (size_t i = 0; i < v2.size; ++i)
            elem[1*rows + i] = v2.elem[i];
        for (size_t i = 0; i < v3.size; ++i)
            elem[2*rows + i] = v3.elem[i];
    }

/*
    create special matrices
*/
    static const Matrix3<T> zero;
    static const Matrix3<T> identity;

    static Matrix3<T> createZero() {
        return zero;
    }

    static Matrix3<T> createIdentity() {
        return identity;
    }

    static Matrix3<T> createTranslation(const Vector2<T>& v) {
        Matrix3<T> result = identity;
        result.t02 = v.elem[0];
        result.t12 = v.elem[1];
        return result;
    }

    static Matrix3<T> createScale(const Vector3<T>& v) {
        Matrix3<T> result = identity;
        result.t00 = v.elem[0];
        result.t11 = v.elem[1];
        result.t22 = v.elem[2];
        return result;
    }
	 

	// helper function, swap two 3-vectors
	
	inline void SwapVectors3(ElemType v1[3], T v2[3])
	{
		for (int i = 0; i < 3; i++)
		{
			T tmp = v1[i];
			v1[i] = v2[i];
			v2[i] = tmp;
		}
	}


 
	
	
int JacobiN(ElemType **a, int n, ElemType *w, ElemType **v)
{
  int i, j, k, iq, ip, numPos;
  ElemType tresh, theta, tau, t, sm, s, h, g, c, tmp;
  ElemType bspace[4], zspace[4];
  ElemType *b = bspace;
  ElemType *z = zspace;

  // only allocate memory if the matrix is large
  if (n > 4)
    {
    b = new T[n];
    z = new T[n]; 
    }

  // initialize
  for (ip=0; ip<n; ip++) 
    {
    for (iq=0; iq<n; iq++)
      {
      v[ip][iq] = 0.0;
      }
    v[ip][ip] = 1.0;
    }
  for (ip=0; ip<n; ip++) 
    {
    b[ip] = w[ip] = a[ip][ip];
    z[ip] = 0.0;
    }

  // begin rotation sequence
  for (i=0; i<VTK_MAX_ROTATIONS; i++) 
    {
    sm = 0.0;
    for (ip=0; ip<n-1; ip++) 
      {
      for (iq=ip+1; iq<n; iq++)
        {
        sm += fabs(a[ip][iq]);
        }
      }
    if (sm == 0.0)
      {
      break;
      }

    if (i < 3)                                // first 3 sweeps
      {
      tresh = 0.2f*sm/(n*n);
      }
    else
      {
      tresh = 0.0;
      }

    for (ip=0; ip<n-1; ip++) 
      {
      for (iq=ip+1; iq<n; iq++) 
        {
        g = 100.0f*fabs(a[ip][iq]);

        // after 4 sweeps
        if (i > 3 && (fabs(w[ip])+g) == fabs(w[ip])
        && (fabs(w[iq])+g) == fabs(w[iq]))
          {
          a[ip][iq] = 0.0;
          }
        else if (fabs(a[ip][iq]) > tresh) 
          {
          h = w[iq] - w[ip];
          if ( (fabs(h)+g) == fabs(h))
            {
            t = (a[ip][iq]) / h;
            }
          else 
            {
            theta = 0.5f*h / (a[ip][iq]);
            t = 1.0f / (fabs(theta)+sqrt(1.0f+theta*theta));
            if (theta < 0.0)
              {
              t = -t;
              }
            }
          c = 1.0f / sqrt(1+t*t);
          s = t*c;
          tau = s/(1.0f+c);
          h = t*a[ip][iq];
          z[ip] -= h;
          z[iq] += h;
          w[ip] -= h;
          w[iq] += h;
          a[ip][iq]=0.0;

          // ip already shifted left by 1 unit
          for (j = 0;j <= ip-1;j++) 
            {
            TGTROTATE(a,j,ip,j,iq);
            }
          // ip and iq already shifted left by 1 unit
          for (j = ip+1;j <= iq-1;j++) 
            {
            TGTROTATE(a,ip,j,j,iq);
            }
          // iq already shifted left by 1 unit
          for (j=iq+1; j<n; j++) 
            {
            TGTROTATE(a,ip,j,iq,j);
            }
          for (j=0; j<n; j++) 
            {
            TGTROTATE(v,j,ip,j,iq);
            }
          }
        }
      }

    for (ip=0; ip<n; ip++) 
      {
      b[ip] += z[ip];
      w[ip] = b[ip];
      z[ip] = 0.0;
      }
    }

  //// this is NEVER called
  if ( i >= VTK_MAX_ROTATIONS )
    {
    /*vtkGenericWarningMacro(
       "vtkMath::Jacobi: Error extracting eigenfunctions");
    */
		return 0;
    }

  // sort eigenfunctions                 these changes do not affect accuracy 
  for (j=0; j<n-1; j++)                  // boundary incorrect
    {
    k = j;
    tmp = w[k];
    for (i=j+1; i<n; i++)                // boundary incorrect, shifted already
      {
      if (w[i] >= tmp)                   // why exchage if same?
        {
        k = i;
        tmp = w[k];
        }
      }
    if (k != j) 
      {
      w[k] = w[j];
      w[j] = tmp;
      for (i=0; i<n; i++) 
        {
        tmp = v[i][j];
        v[i][j] = v[i][k];
        v[i][k] = tmp;
        }
      }
    }
  // insure eigenvector consistency (i.e., Jacobi can compute vectors that
  // are negative of one another (.707,.707,0) and (-.707,-.707,0). This can
  // reek havoc in hyperstreamline/other stuff. We will select the most
  // positive eigenvector.
  int ceil_half_n = (n >> 1) + (n & 1);
  for (j=0; j<n; j++)
    {
    for (numPos=0, i=0; i<n; i++)
      {
      if ( v[i][j] >= 0.0 )
        {
        numPos++;
        }
      }
//    if ( numPos < ceil(double(n)/double(2.0)) )
    if ( numPos < ceil_half_n)
      {
      for(i=0; i<n; i++)
        {
        v[i][j] *= -1.0;
        }
      }
    }

  if (n > 4)
    {
    delete [] b;
    delete [] z;
    }
  return 1;
}
 

//----------------------------------------------------------------------------
// Cross product of two 3-vectors. Result (a x b) is stored in z[3].
inline void Cross(const float x[3], const float y[3], float z[3])
{
	float Zx = x[1] * y[2] - x[2] * y[1];
	float Zy = x[2] * y[0] - x[0] * y[2];
	float Zz = x[0] * y[1] - x[1] * y[0];
	z[0] = Zx; z[1] = Zy; z[2] = Zz;
}
//----------------------------------------------------------------------------
float Norm(const float* x, int n)
{
	double sum=0;
	for (int i=0; i<n; i++)
	{
		sum += x[i]*x[i];
	}

	return (float)sqrt(sum);
}

//----------------------------------------------------------------------------

 
//----------------------------------------------------------------------------
inline float Normalize(float x[3])
{
	float den;
	if ( ( den = Norm( x ,3) ) != 0.0 )
	{
		for (int i=0; i < 3; i++)
		{
			x[i] /= den;
		}
	}
	return den;
}
inline void QuaternionToMatrix3x3(ElemType quat[4])
{
	ElemType ww = quat[0]*quat[0];
	ElemType wx = quat[0]*quat[1];
	ElemType wy = quat[0]*quat[2];
	ElemType wz = quat[0]*quat[3];

	ElemType xx = quat[1]*quat[1];
	ElemType yy = quat[2]*quat[2];
	ElemType zz = quat[3]*quat[3];

	ElemType xy = quat[1]*quat[2];
	ElemType xz = quat[1]*quat[3];
	ElemType yz = quat[2]*quat[3];

	ElemType rr = xx + yy + zz;
	// normalization factor, just in case quaternion was not normalized
	ElemType f = ElemType(1)/ElemType(sqrt(ww + rr));
	ElemType s = (ww - rr)*f;
	f *= 2;

	elemRowCol[0][0] = xx*f + s;
	elemRowCol[1][0] = (xy + wz)*f;
	elemRowCol[2][0] = (xz - wy)*f;

	elemRowCol[0][1] = (xy - wz)*f;
	elemRowCol[1][1] = yy*f + s;
	elemRowCol[2][1] = (yz + wx)*f;

	elemRowCol[0][2] = (xz + wy)*f;
	elemRowCol[1][2] = (yz - wx)*f;
	elemRowCol[2][2] = zz*f + s;
}

	inline void Matrix3x3ToQuaternion(ElemType quat[4])
	{
		ElemType N[4][4];

		// on-diagonal elements
		N[0][0] =  elemRowCol[0][0]+elemRowCol[1][1]+elemRowCol[2][2];
		N[1][1] =  elemRowCol[0][0]-elemRowCol[1][1]-elemRowCol[2][2];
		N[2][2] = -elemRowCol[0][0]+elemRowCol[1][1]-elemRowCol[2][2];
		N[3][3] = -elemRowCol[0][0]-elemRowCol[1][1]+elemRowCol[2][2];

		// off-diagonal elements
		N[0][1] = N[1][0] = elemRowCol[2][1]-elemRowCol[1][2];
		N[0][2] = N[2][0] = elemRowCol[0][2]-elemRowCol[2][0];
		N[0][3] = N[3][0] = elemRowCol[1][0]-elemRowCol[0][1];

		N[1][2] = N[2][1] = elemRowCol[1][0]+elemRowCol[0][1];
		N[1][3] = N[3][1] = elemRowCol[0][2]+elemRowCol[2][0];
		N[2][3] = N[3][2] = elemRowCol[2][1]+elemRowCol[1][2];

		ElemType eigenvectors[4][4],eigenvalues[4];

		// convert into format that JacobiN can use,
		// then use Jacobi to find eigenvalues and eigenvectors
		ElemType *NTemp[4],*eigenvectorsTemp[4];
		for (int i = 0; i < 4; i++)
		{
			NTemp[i] = N[i];
			eigenvectorsTemp[i] = eigenvectors[i];
		}
		JacobiN(NTemp,4,eigenvalues,eigenvectorsTemp);

		// the first eigenvector is the one we want
		quat[0] = eigenvectors[0][0];
		quat[1] = eigenvectors[1][0];
		quat[2] = eigenvectors[2][0];
		quat[3] = eigenvectors[3][0];
	}

	inline void Diagonalize3x3(ElemType w[3], Matrix3& V)
	{
		int i,j,k,maxI;
		ElemType tmp, maxVal;

		// do the matrix[3][3] to **matrix conversion for Jacobi
		ElemType C[3][3];
		ElemType *ATemp[3],*VTemp[3];
		for (i = 0; i < 3; i++)
		{
			C[i][0] = elemRowCol[i][0];
			C[i][1] = elemRowCol[i][1];
			C[i][2] = elemRowCol[i][2];
			ATemp[i] = C[i];
			VTemp[i] = V[i].elem;
		}

		// diagonalize using Jacobi
		JacobiN(ATemp,3,w,VTemp);

		// if all the eigenvalues are the same, return identity matrix
		if (w[0] == w[1] && w[0] == w[2])
		{
			V=V.createIdentity();
			return;
		}

		// transpose temporarily, it makes it easier to sort the eigenvectors
		V.Transpose3x3();

		// if two eigenvalues are the same, re-orthogonalize to optimally line
		// up the eigenvectors with the x, y, and z axes
		for (i = 0; i < 3; i++)
		{
			if (w[(i+1)%3] == w[(i+2)%3]) // two eigenvalues are the same
			{
				// find maximum element of the independant eigenvector
				maxVal = fabs(V[i][0]);
				maxI = 0;
				for (j = 1; j < 3; j++)
				{
					if (maxVal < (tmp = fabs(V[i][j])))
					{
						maxVal = tmp;
						maxI = j;
					}
				}
				// swap the eigenvector into its proper position
				if (maxI != i)
				{
					tmp = w[maxI];
					w[maxI] = w[i];
					w[i] = tmp;
					SwapVectors3(V[i].elem,V[maxI].elem);
				}
				// maximum element of eigenvector should be positive
				if (V[maxI][maxI] < 0)
				{
					V[maxI][0] = -V[maxI][0];
					V[maxI][1] = -V[maxI][1];
					V[maxI][2] = -V[maxI][2];
				}

				// re-orthogonalize the other two eigenvectors
				j = (maxI+1)%3;
				k = (maxI+2)%3;

				V[j][0] = 0.0;
				V[j][1] = 0.0;
				V[j][2] = 0.0;
				V[j][j] = 1.0;
				Cross(V[maxI].elem,V[j].elem,V[k].elem);
				Normalize(V[k].elem);
				Cross(V[k].elem,V[maxI].elem,V[j].elem);
				V.Transpose3x3();
				return;
			}
		}

		// the three eigenvalues are different, just sort the eigenvectors
		// to align them with the x, y, and z axes

		// find the vector with the largest x element, make that vector
		// the first vector
		maxVal = fabs(V[0][0]);
		maxI = 0;
		for (i = 1; i < 3; i++)
		{
			if (maxVal < (tmp = fabs(V[i][0])))
			{
				maxVal = tmp;
				maxI = i;
			}
		}
		// swap eigenvalue and eigenvector
		if (maxI != 0)
		{
			tmp = w[maxI];
			w[maxI] = w[0];
			w[0] = tmp;
			SwapVectors3(V[maxI].elem,V[0].elem);
		}
		// do the same for the y element
		if (fabs(V[1][1]) < fabs(V[2][1]))
		{
			tmp = w[2];
			w[2] = w[1];
			w[1] = tmp;
			SwapVectors3(V[2].elem,V[1].elem);
		}

		// ensure that the sign of the eigenvectors is correct
		for (i = 0; i < 2; i++)
		{
			if (V[i][i] < 0)
			{
				V[i][0] = -V[i][0];
				V[i][1] = -V[i][1];
				V[i][2] = -V[i][2];
			}
		}
		// set sign of final eigenvector to ensure that determinant is positive
		if (V.det() < 0)
		{
			V[2][0] = -V[2][0];
			V[2][1] = -V[2][1];
			V[2][2] = -V[2][2];
		}

		// transpose the eigenvectors back again
		V.Transpose3x3();
	}

 
	inline void Orthogonalize3x3(Matrix3<T>& B)
	{
		int i;

		// copy the matrix
		for (i = 0; i < 3; i++)
		{
			B[0][i] = elemRowCol[0][i];
			B[1][i] = elemRowCol[1][i];
			B[2][i] = elemRowCol[2][i];
		}

		// Pivot the matrix to improve accuracy
		ElemType scale[3];
		int index[3];
		ElemType largest;

		// Loop over rows to get implicit scaling information
		for (i = 0; i < 3; i++)
		{
			ElemType x1 = fabs(B[i][0]);
			ElemType x2 = fabs(B[i][1]);
			ElemType x3 = fabs(B[i][2]);
			largest = (x2 > x1 ? x2 : x1);
			largest = (x3 > largest ? x3 : largest);
			scale[i] = 1;
			if (largest != 0)
			{
				scale[i] /= largest;
			}
		}

		// first column
		ElemType x1 = fabs(B[0][0])*scale[0];
		ElemType x2 = fabs(B[1][0])*scale[1];
		ElemType x3 = fabs(B[2][0])*scale[2];
		index[0] = 0;
		largest = x1;
		if (x2 >= largest) 
		{
			largest = x2;
			index[0] = 1;
		}
		if (x3 >= largest) 
		{
			index[0] = 2;
		}
		if (index[0] != 0) 
		{
			SwapVectors3(B[index[0]].elem,B[0].elem);
			scale[index[0]] = scale[0];
		}

		// second column
		ElemType y2 = fabs(B[1][1])*scale[1];
		ElemType y3 = fabs(B[2][1])*scale[2];
		index[1] = 1;
		largest = y2;
		if (y3 >= largest) 
		{
			index[1] = 2;
			SwapVectors3(B[2].elem,B[1].elem);
		}

		// third column
		index[2] = 2;

		// A quaternion can only describe a pure rotation, not
		// a rotation with a flip, therefore the flip must be
		// removed before the matrix is converted to a quaternion.
		int flip = 0;
		if (B.det()< 0)
		{
			flip = 1;
			for (i = 0; i < 3; i++)
			{
				B[0][i] = -B[0][i];
				B[1][i] = -B[1][i];
				B[2][i] = -B[2][i];
			}
		}

		// Do orthogonalization using a quaternion intermediate
		// (this, essentially, does the orthogonalization via
		// diagonalization of an appropriately constructed symmetric
		// 4x4 matrix rather than by doing SVD of the 3x3 matrix)
		ElemType quat[4];
		B.Matrix3x3ToQuaternion(quat);
		B.QuaternionToMatrix3x3(quat);

		// Put the flip back into the orthogonalized matrix.
		if (flip)
		{
			for (i = 0; i < 3; i++)
			{
				B[0][i] = -B[0][i];
				B[1][i] = -B[1][i];
				B[2][i] = -B[2][i];
			}
		}

		// Undo the pivoting
		if (index[1] != 1)
		{
			SwapVectors3(B[index[1]].elem,B[1].elem);
		}
		if (index[0] != 0)
		{
			SwapVectors3(B[index[0]].elem,B[0].elem);
		}
	}


	//----------------------------------------------------------------------------
	
	inline void MultiplyMatrix3x3( Matrix3<T>& B,
		 Matrix3<T>& C)
	{
		ElemType D[3][3];

		for (int i = 0; i < 3; i++)
		{
			D[0][i] = elemRowCol[0][0]*B[0][i] + elemRowCol[0][1]*B[1][i] + elemRowCol[0][2]*B[2][i];
			D[1][i] = elemRowCol[1][0]*B[0][i] + elemRowCol[1][1]*B[1][i] + elemRowCol[1][2]*B[2][i];
			D[2][i] = elemRowCol[2][0]*B[0][i] + elemRowCol[2][1]*B[1][i] + elemRowCol[2][2]*B[2][i];
		}

		for (int j = 0; j < 3; j++)
		{
			C[j][0] = D[j][0];
			C[j][1] = D[j][1];
			C[j][2] = D[j][2];
		}
	}
	//----------------------------------------------------------------------------
	
	inline void Transpose3x3()
	{
		ElemType tmp;
		tmp = elemRowCol[1][0];
		elemRowCol[1][0] = elemRowCol[0][1];
		elemRowCol[0][1] = tmp;
		tmp = elemRowCol[2][0];
		elemRowCol[2][0] = elemRowCol[0][2];
		elemRowCol[0][2] = tmp;
		tmp = elemRowCol[2][1];
		elemRowCol[2][1] = elemRowCol[1][2];
		elemRowCol[1][2] = tmp;

		elemRowCol[0][0] = elemRowCol[0][0];
		elemRowCol[1][1] = elemRowCol[1][1];
		elemRowCol[2][2] = elemRowCol[2][2];
	}

	void SingularValueDecomposition3x3( Matrix3<T>& U, Vector3<float>& w,Matrix3<T>& VT)
{
  int i;
  Matrix3 B;

  // copy so that A can be used for U or VT without risk
  for (i = 0; i < 3; i++)
    {
    B[0][i] = elemRowCol[0][i];
    B[1][i] = elemRowCol[1][i];
    B[2][i] = elemRowCol[2][i];
    }

  // temporarily flip if determinant is negative
  //ElemType d = vtkMath::Determinant3x3(B);
  ElemType d = B.det();
  if (d < 0)
    {
    for (i = 0; i < 3; i++)
      {
      B[0][i] = -B[0][i];
      B[1][i] = -B[1][i];
      B[2][i] = -B[2][i];
      }
    }

  // orthogonalize, diagonalize, etc.
  B.Orthogonalize3x3(U);
 B.Transpose3x3();
  B.MultiplyMatrix3x3( U, VT);
  VT.Diagonalize3x3( w.elem, VT);
  U.MultiplyMatrix3x3(VT, U);
  VT.Transpose3x3();;

  // re-create the flip
  if (d < 0)
  {
	  w[0] = -w[0];
	  w[1] = -w[1];
	  w[2] = -w[2];
  }
}

    /**
     * Rotation the x-axis as rotation axis.
     * The angle is in \em RADIAN AND NOT \em DEGREE.
     *
     * @param angle The angle of rotation in \em radian.
     */
    static Matrix3<T> createRotationX(T angle) {
        Matrix3<T> result = identity;
        result.t11 =  cos(angle);
        result.t12 = -sin(angle);
        result.t21 =  sin(angle);
        result.t22 =  cos(angle);
        return result;
    }

    /**
     * Rotation the y-axis as rotation axis.
     * The angle is in \em RADIAN AND NOT \em DEGREE.
     *
     * @param angle The angle of rotation in \em radian.
     */
    static Matrix3<T> createRotationY(T angle) {
        Matrix3<T> result = identity;
        result.t00 =  cos(angle);
        result.t02 =  sin(angle);
        result.t20 = -sin(angle);
        result.t22 =  cos(angle);
        return result;
    }

    /**
     * Rotation the z-axis as rotation axis.
     * The angle is in \em RADIAN AND NOT \em DEGREE.
     *
     * @param angle The angle of rotation in \em radian.
     */
    static Matrix3<T> createRotationZ(T angle) {
        Matrix3<T> result = identity;
        result.t00 =  cos(angle);
        result.t01 = -sin(angle);
        result.t10 =  sin(angle);
        result.t11 =  cos(angle);
        return result;
    }

    /**
     * Simliar to glRotate but \p angle is in \em RADIAN AND NOT \em DEGREE.
     *
     * @param angle The angle in \em radian.
     * @param axis The axis of rotation. Needn't be in unit length.
     */
    static Matrix3<T> createRotation(T angle, Vector3<T> axis);

    /**
     * inverts the matrix.
     * @return true - if successful -- otherwise false
    */
    bool invert(Matrix3<T>& result) const;

    float det() {
        return elem[0]*elem[4]*elem[8] + elem[1]*elem[5]*elem[6] + elem[2]*elem[3]*elem[7] - elem[0]*elem[5]*elem[7] - elem[1]*elem[3]*elem[8] - elem[2]*elem[4]*elem[6];
    }
/*
    index operator
*/
    /*
        The C++ standard forbids classes with non trivial constructors
        as union members. Thus this hack provides functionality similar
        to the GLSL matrix index operator.
    */
    /// return arbitrary row-vector similar to GLSL. <br>
    /// BUT REMEMBER: GLSL gives you COLS NOT ROWS!
    const Vector3<T>& operator [] (size_t i) const {
        //tgtAssert(i < size, "i must be less than size");
        return *((Vector3<T>*) elemRowCol[i]);
    }
    /// return arbitrary row-vector similar to GLSL. <br>
    /// BUT REMEMBER: GLSL gives you COLS NOT ROWS!
    Vector3<T>& operator [] (size_t i) {
        //tgtAssert(i < size, "i must be less than size");
        return *((Vector3<T>*) elemRowCol[i]);
    }
};

/*
    init statics
*/

/// init statics
template<class T>
const Matrix3<T> Matrix3<T>::zero = Matrix3<T>
(
    T(0), T(0), T(0),
    T(0), T(0), T(0),
    T(0), T(0), T(0)
);

template<class T>
const Matrix3<T> Matrix3<T>::identity = Matrix3<T>
(
    T(1), T(0), T(0),
    T(0), T(1), T(0),
    T(0), T(0), T(1)
);

template<class T>
bool Matrix3<T>::invert(Matrix3<T>& result) const {
    using std::abs; // use overloaded abs
    result = Matrix3<T>::identity;

    float z = elem[0]*(elem[4]*elem[8] - elem[5]*elem[7]) + elem[1]*(elem[5]*elem[6] - elem[3]*elem[8]) + elem[2]*(elem[3]*elem[7] - elem[4]*elem[6]);

    if(abs(z) < 0.00001f)
        return false;

    //we have a row-matrix:
    result.elem[0] = (elem[4]*elem[8] - elem[5]*elem[7]);
    result.elem[1] = (elem[2]*elem[7] - elem[1]*elem[8]);
    result.elem[2] = (elem[1]*elem[5] - elem[2]*elem[4]);

    result.elem[3] = (elem[5]*elem[6] - elem[3]*elem[8]);
    result.elem[4] = (elem[0]*elem[8] - elem[2]*elem[6]);
    result.elem[5] = (elem[2]*elem[3] - elem[0]*elem[5]);

    result.elem[6] = (elem[3]*elem[7] - elem[4]*elem[6]);
    result.elem[7] = (elem[1]*elem[6] - elem[0]*elem[7]);
    result.elem[8] = (elem[0]*elem[4] - elem[1]*elem[3]);

    result /= z;

    return true;
}
//

/**
    Matrix4 class. Works basicly like the matrix stuff in GLSL.
    But remember that this is a ROW-MATRIX and NOT a COL-MATRIX
    like in OpenGL or GLSL respectively.
*/
template<class T>
struct Matrix4 {
    typedef T ElemType;

    enum {
        size = 16,
        cols = 4,
        rows = 4
    };
    typedef Vector4<T> RowType;

    union {
        struct {
            T t00, t01, t02, t03;
            T t10, t11, t12, t13;
            T t20, t21, t22, t23;
            T t30, t31, t32, t33;
        };
        T elemRowCol[4][4];
        T elem[16];
    };

/*
    constructors
*/
    /// default constructor
    Matrix4() {}
    /// Init all elements with the same value
    explicit Matrix4(T t) {
        for (size_t i = 0; i < size; ++i)
            elem[i] = t;
    }
    /// Init with another Matrix of another type
    template<class U>
    Matrix4(const Matrix4<U>& m) {
        for (size_t i = 0; i < m.size; ++i)
            elem[i] = T(m.elem[i]);
    }
    /// Init from array with equal size
    explicit Matrix4(const T* t) {
        for (size_t i = 0; i < size; ++i)
            elem[i] = t[i];
    }
    /// Init componentwisely
    Matrix4(T _t00, T _t01, T _t02, T _t03,
            T _t10, T _t11, T _t12, T _t13,
            T _t20, T _t21, T _t22, T _t23,
            T _t30, T _t31, T _t32, T _t33) {
        t00 = _t00; t01 = _t01; t02 = _t02; t03 = _t03;
        t10 = _t10; t11 = _t11; t12 = _t12; t13 = _t13;
        t20 = _t20; t21 = _t21; t22 = _t22; t23 = _t23;
        t30 = _t30; t31 = _t31; t32 = _t32; t33 = _t33;
    }
    /// Init with four Vector4
    Matrix4(const Vector4<T>& v1, const Vector4<T>& v2,
            const Vector4<T>& v3, const Vector4<T>& v4) {
        for (size_t i = 0; i < v1.size; ++i)
            elem[0*rows + i] = v1.elem[i];
        for (size_t i = 0; i < v2.size; ++i)
            elem[1*rows + i] = v2.elem[i];
        for (size_t i = 0; i < v3.size; ++i)
            elem[2*rows + i] = v3.elem[i];
        for (size_t i = 0; i < v4.size; ++i)
            elem[3*rows + i] = v4.elem[i];
    }

    /// Return the upper left 3x3-submatrix in a 4x4 matrix
    Matrix4<T> getRotationalPart() const {
        Matrix4<T> result(T(0));
        result.t00 = t00; result.t01  = t01; result.t02 = t02;
        result.t10 = t10; result.t11  = t11; result.t12 = t12;
        result.t20 = t20; result.t21  = t21; result.t22 = t22;
        result.t33 = T(1);
        return result;
    }

    /// Return the main diagonal of the upper left 3x3-submatrix
    Vector3<T> getScalingPart() const 
	{


        Vector3<T> result(T(0));
        result.elem[0] = t00;
        result.elem[1] = t11;
        result.elem[2] = t22;
        return result;
    }

 

/*
    create special matrices
*/
    static const Matrix4<T> zero;
    static const Matrix4<T> identity;

    static Matrix4<T> createZero() {
        return zero;
    }

    static Matrix4<T> createIdentity() {
        return identity;
    }

    static Matrix4<T> createTranslation(const Vector3<T>& v) {
        Matrix4<T> result = identity;
        result.t03 = v.elem[0];
        result.t13 = v.elem[1];
        result.t23 = v.elem[2];
        return result;
    }

    static Matrix4<T> createScale(const Vector3<T>& v) {
        Matrix4<T> result = identity;
        result.t00 = v.elem[0];
        result.t11 = v.elem[1];
        result.t22 = v.elem[2];
        return result;
    }

    /**
     * Rotation the x-axis as rotation axis.
     * The angle is in \em RADIAN AND NOT \em DEGREE.
     *
     * @param angle The angle of rotation in \em radian.
     */
    static Matrix4<T> createRotationX(T angle) {
        using namespace std; // use overloaded cos and sin
        Matrix4<T> result = identity;
        result.t11 =  cos(angle);
        result.t12 = -sin(angle);
        result.t21 =  sin(angle);
        result.t22 =  cos(angle);
        return result;
    }

    /**
     * Rotation the y-axis as rotation axis.
     * The angle is in \em RADIAN AND NOT \em DEGREE.
     *
     * @param angle The angle of rotation in \em radian.
     */
    static Matrix4<T> createRotationY(T angle) {
        using namespace std; // use overloaded cos and sin
        Matrix4<T> result = identity;
        result.t00 =  cos(angle);
        result.t02 =  sin(angle);
        result.t20 = -sin(angle);
        result.t22 =  cos(angle);
        return result;
    }

    /**
     * Rotation the z-axis as rotation axis.
     * The angle is in \em RADIAN AND NOT \em DEGREE.
     *
     * @param angle The angle of rotation in \em radian.
     */
    static Matrix4<T> createRotationZ(T angle) {
        using namespace std; // use overloaded cos and sin
        Matrix4<T> result = identity;
        result.t00 =  cos(angle);
        result.t01 = -sin(angle);
        result.t10 =  sin(angle);
        result.t11 =  cos(angle);
        return result;
    }

    /**
     * Simliar to glRotate but \p angle is in \em RADIAN AND NOT \em DEGREE.
     *
     * @param angle The angle in \em radian.
     * @param axis The axis of rotation. Needn't be in unit length.
     */
    static Matrix4<T> createRotation(T angle, Vector3<T> axis);

    /**
    * This function returns the Matrix that gluLookAt would create and put onto the OpenGL
    * Matrix-Stack, given the position, focus-point, and up-Vector of a camera.
    */
    static Matrix4<T> createLookAt(const Vector3<T>& eye, const Vector3<T>& focus, const Vector3<T>& up);

    /**
     * This function provides a glFrustum() replacement.  In case you just need the matrix that glFrustum would
     * produce, you can use this function instead of putting the matrix on the OpenGL stack and then reading it.
     */
    static Matrix4<T> createFrustum(T left, T right, T top, T bottom, T pnear, T pfar);

    /**
     * This function provides a gluPerspective() replacement.
     * See its documentation for an explanation of the parameters. \em BUT:
     * \p fov expects \em RADIAN and not \em DEGREE.
     */
    static Matrix4<T> createPerspective(T fov, T aspect, T pnear, T pfar);

    static Matrix4<T> createOrtho(T left, T right, T top, T bottom, T pnear, T pfar);

/*
    index operator
*/

   /*
        The C++ standard forbids classes with non trivial constructors
        as union members. Thus this hack provides functionality similar
        to the GLSL matrix index operator.
    */
    /// return arbitrary row-vector similar to GLSL. <br>
    /// BUT REMEMBER: GLSL gives you COLS NOT ROWS!
    const Vector4<T>& operator [] (size_t i) const {
        //tgtAssert(i < size, "i must be less than size");
        return *((Vector4<T>*) elemRowCol[i]);
    }
    /// return arbitrary row-vector similar to GLSL. <br>
    /// BUT REMEMBER: GLSL gives you COLS NOT ROWS!
    Vector4<T>& operator [] (size_t i) {
        //tgtAssert(i < size, "i must be less than size");
        return *((Vector4<T>*) elemRowCol[i]);
    }

    /**
     * inverts the matrix.
     * @return true - if successful -- otherwise false
    */
    bool invert(Matrix4<T>& result) const;
};

/*
    init statics
*/
template<class T>
const Matrix4<T> Matrix4<T>::zero = Matrix4<T>
(
    T(0), T(0), T(0), T(0),
    T(0), T(0), T(0), T(0),
    T(0), T(0), T(0), T(0),
    T(0), T(0), T(0), T(0)
);

template<class T>
const Matrix4<T> Matrix4<T>::identity = Matrix4<T>
(
    T(1), T(0), T(0), T(0),
    T(0), T(1), T(0), T(0),
    T(0), T(0), T(1), T(0),
    T(0), T(0), T(0), T(1)
);


/*
    typedefs for easy usage
*/

typedef Matrix2<float>  Matrix2f;
typedef Matrix2<double> Matrix2d;
typedef Matrix3<float>  Matrix3f;
typedef Matrix3<double> Matrix3d;
typedef Matrix4<float>  Matrix4f;
typedef Matrix4<double> Matrix4d;

typedef Matrix4f        Matrix;

/*
    types like in GLSL
*/
typedef Matrix2f        mat2;
typedef Matrix3f        mat3;
typedef Matrix4f        mat4;

typedef Matrix2<bool>   bmat2;
typedef Matrix3<bool>   bmat3;
typedef Matrix4<bool>   bmat4;

/*
    Prepare to implement 3 * 5 * 7 = 105 operators and a couple of functions
    the lazy way with evil voodoo macro magic
*/

#define TGT_MAT_TRANSPOSE \
template<class T> inline TGT_BASE_TYPE<T> transpose(const TGT_BASE_TYPE<T>& m) { \
    TGT_BASE_TYPE<T> mRes; \
    for (size_t row = 0; row < m.rows; ++row) \
        for (size_t col = 0; col < m.cols; ++col) \
            mRes.elemRowCol[col][row] = m.elemRowCol[row][col]; \
    return mRes; \
}

/*
    Similar to GLSL make an exception with the
    Matrix-Matrix, Vector-Matrix and Matrix-Vector multiplication.
    These are "correct" operations and do not go componentwisely
*/

#define TGT_MAT_MUL_VEC \
template<class T> inline typename TGT_BASE_TYPE<T>::RowType operator * (const TGT_BASE_TYPE<T>& m, const typename TGT_BASE_TYPE<T>::RowType& v) { \
    typename TGT_BASE_TYPE<T>::RowType vRes; \
    for (size_t i = 0; i < v.size; ++i) \
        vRes[i] = dot(m[i], v); \
    return vRes; \
}

#define TGT_VEC_MUL_MAT \
template<class T> inline typename TGT_BASE_TYPE<T>::RowType operator * (const typename TGT_BASE_TYPE<T>::RowType& v, const TGT_BASE_TYPE<T>& m) { \
    typename TGT_BASE_TYPE<T>::RowType vRes; \
    TGT_BASE_TYPE<T> transposed = transpose(m); \
    for (size_t i = 0; i < v.size; ++i) \
        vRes[i] = dot(v, transposed[i]); \
    return vRes; \
}

#define TGT_MAT_MUL_MAT \
template<class T> inline TGT_BASE_TYPE<T> operator * (const TGT_BASE_TYPE<T>& m1, const TGT_BASE_TYPE<T>& m2) { \
    TGT_BASE_TYPE<T> mRes; \
    TGT_BASE_TYPE<T> transposed = transpose(m2); \
    for (size_t row = 0; row < m1.rows; ++row) \
        for (size_t col = 0; col < m1.cols; ++col) \
            mRes.elemRowCol[row][col] = \
                dot(m1[row], transposed[col]); \
    return mRes; \
}

#define TGT_MAT_MULEQ_MAT \
template<class T> inline TGT_BASE_TYPE<T>& operator *= (TGT_BASE_TYPE<T>& m1, const TGT_BASE_TYPE<T>& m2) { \
    TGT_BASE_TYPE<T> temp = m1; \
    m1 = temp * m2; \
    return m1; \
}

#define TGT_MAT_COMP_MUL \
template<class T> inline TGT_BASE_TYPE<T> matrixCompMult (const TGT_BASE_TYPE<T>& v1, const TGT_BASE_TYPE<T>& v2) { \
    TGT_BASE_TYPE<T> vRes; \
    for (size_t i = 0; i < v1.size; ++i) \
        vRes.elem[i] = v1.elem[i] * v2.elem[i]; \
    return vRes; \
}

/*
det
m[0][0] * m[1][1] * m[2][2]
+ m[0][1] * m[1][2] * m[2][0]
+ m[0][2] * m[1][0] * m[2][1]
- m[0][2] * m[1][1] * m[2][0]
- m[0][1] * m[1][0] * m[2][2]
- m[0][0] * m[1][2] * m[2][1]
*/

#define TGT_IMPLEMENT_MAT_FUNCTIONS \
    TGT_VEC_UNARY_MINUS \
    TGT_VEC_MIN \
    TGT_VEC_MAX \
    TGT_VEC_FLOOR \
    TGT_VEC_CEIL \
    TGT_VEC_MIN_SINGLE \
    TGT_VEC_MAX_SINGLE \
    TGT_VEC_MIN_SELF \
    TGT_VEC_MAX_SELF \
    TGT_VEC_CLAMP \
    TGT_VEC_CLAMP_SINGLE \
    TGT_VEC_HADD \
    TGT_VEC_HSUB \
    TGT_VEC_HMUL \
    TGT_VEC_HDIV \
    TGT_VEC_HMOD \
    TGT_VEC_HAND \
    TGT_VEC_HOR \
    TGT_VEC_HXOR \
    TGT_VEC_REL_OP_EQUAL  \
    TGT_VEC_REL_OP_NOT_EQUAL \
    TGT_VEC_LESS_THAN \
    TGT_VEC_LESS_THAN_EQUAL \
    TGT_VEC_GREATER_THAN \
    TGT_VEC_GREATER_THAN_EQUAL \
    TGT_VEC_EQUAL \
    TGT_VEC_NOT_EQUAL \
    TGT_MAT_TRANSPOSE \
    TGT_MAT_COMP_MUL \
    TGT_MAT_MUL_VEC \
    TGT_VEC_MUL_MAT \
    TGT_MAT_MUL_MAT \
    TGT_MAT_MULEQ_MAT

/*
    Implementation of Matrix2<T> operators
*/

#define TGT_BASE_TYPE Matrix2
    #define TGT_VEC_OP +
    #define TGT_VEC_OPEQ +=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP -
    #define TGT_VEC_OPEQ -=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP *
    #define TGT_VEC_OPEQ *=
        /*
            According to GLSL matrix * matrix should be exceptionally a
            "correct" algebraic multiplication.
            Instead use matrixCompMult if you need this operatrion.
        */
        TGT_VEC_OP_BASE
        TGT_BASE_OP_VEC
        TGT_VEC_OPEQ_BASE
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP /
    #define TGT_VEC_OPEQ /=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP &
    #define TGT_VEC_OPEQ &=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP |
    #define TGT_VEC_OPEQ |=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP ^
    #define TGT_VEC_OPEQ ^=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    TGT_IMPLEMENT_MAT_FUNCTIONS
#undef TGT_BASE_TYPE

/*
    Implementation of Matrix3<T> operators
*/

#define TGT_BASE_TYPE Matrix3
    #define TGT_VEC_OP +
    #define TGT_VEC_OPEQ +=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP -
    #define TGT_VEC_OPEQ -=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP *
    #define TGT_VEC_OPEQ *=
        /*
            According to GLSL matrix * matrix should be exceptionally a
            "correct" algebraic multiplication.
            Instead use matrixCompMult if you need this operatrion.
        */
        TGT_VEC_OP_BASE
        TGT_BASE_OP_VEC
        TGT_VEC_OPEQ_BASE
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP /
    #define TGT_VEC_OPEQ /=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP &
    #define TGT_VEC_OPEQ &=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP |
    #define TGT_VEC_OPEQ |=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP ^
    #define TGT_VEC_OPEQ ^=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    TGT_IMPLEMENT_MAT_FUNCTIONS
#undef TGT_BASE_TYPE

/*
    Implementation of Matrix4<T> operators
*/

#define TGT_BASE_TYPE Matrix4
    #define TGT_VEC_OP +
    #define TGT_VEC_OPEQ +=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP -
    #define TGT_VEC_OPEQ -=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP *
    #define TGT_VEC_OPEQ *=
        /*
            According to GLSL matrix * matrix should be exceptionally a
            "correct" algebraic multiplication.
            Instead use matrixCompMult if you need this operatrion.
        */
        TGT_VEC_OP_BASE
        TGT_BASE_OP_VEC
        TGT_VEC_OPEQ_BASE
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP /
    #define TGT_VEC_OPEQ /=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP &
    #define TGT_VEC_OPEQ &=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP |
    #define TGT_VEC_OPEQ |=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    #define TGT_VEC_OP ^
    #define TGT_VEC_OPEQ ^=
        TGT_IMPLEMENT_OPERATORS
    #undef  TGT_VEC_OP
    #undef  TGT_VEC_OPEQ

    TGT_IMPLEMENT_MAT_FUNCTIONS
#undef TGT_BASE_TYPE

/*
    Undefine macros   
*/

#undef TGT_IMPLEMENT_MAT_FUNCTIONS
#undef TGT_MAT_COMP_MUL
#undef TGT_MAT_MULEQ_MAT
#undef TGT_MAT_MUL_MAT
#undef TGT_MAT_MUL_VEC
#undef TGT_MAT_TRANSPOSE
#undef TGT_VEC_MUL_MAT
       
        
//
// Non inline implementation
//

/*
    createRotation for Matrix3<T> and Matrix4<T>
*/

template<class T>
Matrix3<T> Matrix3<T>::createRotation(T angle, Vector3<T> axis) {
    using namespace std; // use overloaded cos and sin
    axis = normalize(axis);
    T s = sin(angle);
    T c = cos(angle);
    T x = axis.x;
    T y = axis.y;
    T z = axis.z;

    Matrix3<T> result
    (
        x*x*(1-c) + c,      x*y*(1-c) - z*s,    x*z*(1-c) + y*s,
        x*y*(1-c) + z*s,    y*y*(1-c) + c,      y*z*(1-c) - x*s,
        x*z*(1-c) - y*s,    y*z*(1-c) + x*s,    z*z*(1-c) + c
    );

    return result;
}

template<class T>
Matrix4<T> Matrix4<T>::createRotation(T angle, Vector3<T> axis) {
    using namespace std; // use overloaded cos and sin
    axis = normalize(axis);
    T s = sin(angle);
    T c = cos(angle);
    T x = axis.x;
    T y = axis.y;
    T z = axis.z;

    Matrix4<T> result
    (
        x*x*(1-c) + c,      x*y*(1-c) - z*s,    x*z*(1-c) + y*s, T(0),
        x*y*(1-c) + z*s,    y*y*(1-c) + c,      y*z*(1-c) - x*s, T(0),
        x*z*(1-c) - y*s,    y*z*(1-c) + x*s,    z*z*(1-c) + c,   T(0),
        T(0),               T(0),               T(0),            T(1)
    );

    return result;
}


/*
    createFrustum, createPerspective and createLookAt
*/

template<class T>
Matrix4<T> Matrix4<T>::createLookAt(const Vector3<T>& eye, const Vector3<T>& focus, const Vector3<T>& up) {

    Vector3<T> look   = normalize(focus - eye);
    Vector3<T> strafe = normalize(cross(look, normalize(up)));
    Vector3<T> up2    = cross(strafe, look);

    Matrix4<T> m(Vector4<T>( strafe, T(0) ),
                 Vector4<T>( up2, T(0) ),
                 Vector4<T>( -look, T(0) ),
                 Vector4<T>( T(0), T(0), T(0), T(1) ));

    return m * Matrix4<T>::createTranslation(-eye);
}

template<class T>
Matrix4<T> Matrix4<T>::createFrustum(T left, T right, T bottom, T top, T pnear, T pfar) {
#ifdef TGT_DEBUGLOGGING
    if ((pnear == pfar) || (left == right) || (top == bottom)) {
        //tgtAssert(false, "The parameters passed to createFrustum cannot be used to form a projection matrix.");
        return Matrix4<T>::identity;
    }
#endif // TGT_DEBUGLOGGING

    Matrix4<T> m(	
        T(2)*pnear/(right-left),        T(0),               (right+left)/(right-left),             T(0),
                T(0),           T(2)*pnear/(top-bottom),    (top+bottom)/(top-bottom),             T(0),
                T(0),                   T(0),               (pnear+pfar)/(pnear-pfar),  (T(2)*pfar*pnear)/(pnear-pfar),
                T(0),                   T(0),                          -T(1),                      T(0)
    );

    return m;
}

template<class T>
Matrix4<T> Matrix4<T>::createPerspective(T fov, T aspect, T pnear, T pfar) {
#ifdef TGT_DEBUGLOGGING
    if ((pnear == pfar) || (rad2deg(fov) > T(355)) || (rad2deg(fov) < T(5)) || (aspect == T(0))) {
        //tgtAssert(false, "The parameters passed to createPerspective cannot be used to form a projection matrix.");
        return Matrix4<T>::identity;
    }
#endif // TGT_DEBUGLOGGING

    T f = T(1) / tanf( fov/T(2) );
    Matrix4<T> m(
        f / aspect,         T(0),            T(0),                          T(0),
            T(0),             f,             T(0),                          T(0),
            T(0),           T(0),   (pnear+pfar)/(pnear-pfar),  (T(2)*pfar*pnear)/(pnear-pfar),
            T(0),           T(0),           -T(1),                          T(0)
    );

    return m;
}

template<class T>
Matrix4<T> Matrix4<T>::createOrtho(T left, T right, T top, T bottom, T pnear, T pfar) {
#ifdef TGT_DEBUGLOGGING
    if ((pnear == pfar) || (left == right) || (top == bottom)) {
        //tgtAssert(false, "The parameters passed to createOrthogonal cannot be used to form a projection matrix.");
        return Matrix4<T>::identity;
    }
#endif // TGT_DEBUGLOGGING
    
    Matrix4<T> m(
        T(2)/(right-left),      T(0),              T(0),         -(right+left)/(right-left),
             T(0),         T(2)/(top-bottom),      T(0),         -(top+bottom)/(top-bottom),
             T(0),              T(0),         T(2)/(pfar-pnear), -(pfar+pnear)/(pfar-pnear),
             T(0),              T(0),              T(0),                      T(1)
    );

    return m;
}

/*
    ostream operators
*/

/// ostream-operator
template<class T>
std::ostream& operator << (std::ostream& s, const Matrix2<T>& m) {
    return (s
        << "| " << m.elem[0] << " " << m.elem[1] << " |" << std::endl
        << "| " << m.elem[2] << " " << m.elem[3] << " |" << std::endl);
}

/// ostream-operator
template<class T>
std::ostream& operator << (std::ostream& s, const Matrix3<T>& m) {
    return (s
        << "| " << m.elem[0] << " " << m.elem[1] << " " << m.elem[2] << " |" << std::endl
        << "| " << m.elem[3] << " " << m.elem[4] << " " << m.elem[5] << " |" << std::endl
        << "| " << m.elem[6] << " " << m.elem[7] << " " << m.elem[8] << " |" << std::endl);
}

/// ostream-operator
template<class T>
std::ostream& operator << (std::ostream& s, const Matrix4<T>& m) {
    return (s
        << "| " << m.elem[ 0] << " " << m.elem[ 1] << " " << m.elem[ 2] << " " << m.elem[ 3] << " |" << std::endl
        << "| " << m.elem[ 4] << " " << m.elem[ 5] << " " << m.elem[ 6] << " " << m.elem[ 7] << " |" << std::endl
        << "| " << m.elem[ 8] << " " << m.elem[ 9] << " " << m.elem[10] << " " << m.elem[11] << " |" << std::endl
        << "| " << m.elem[12] << " " << m.elem[13] << " " << m.elem[14] << " " << m.elem[15] << " |" << std::endl);
}

/// This operator is not available in GLSL but very usefull: A mat4 * vec3 operator, returning a vec3
/// note: the resulting vec3 is divided by the w component of the temporary result!
template<class T>
Vector3<T> operator * (const Matrix4<T>& m, const Vector3<T>& v) {
    Vector4<T> v4(v, 1);
    v4 = m * v4;
    v4 /= v4.w;
    return Vector3<T>(v4.elem);
}

// addtional matrix functions

template<class T>
bool Matrix4<T>::invert(Matrix4<T>& result) const {
    using std::abs; // use overloaded abs
    float t;
    Matrix4<T> tmp = *this;
    result = Matrix4<T>::identity;

    for (size_t i = 0; i < 4; ++i) {
        // Look for largest element in column
        size_t swap = i;
        for (size_t j = i + 1; j < 4; ++j) {
            if (abs(tmp.elemRowCol[j][i]) > abs(tmp.elemRowCol[i][i]))
                swap = j;
        }

        if (swap != i) {
            // Swap rows.
            for (size_t k = 0; k < 4; ++k) {
                t = tmp.elemRowCol[i][k];
                tmp.elemRowCol[i][k] = tmp.elemRowCol[swap][k];
                tmp.elemRowCol[swap][k] = t;

                t = result.elem[i*4+k];
                result.elem[i*4+k] = result.elem[swap*4+k];
                result.elem[swap*4+k] = t;
            }
        }

        if (tmp.elemRowCol[i][i] == 0) {
            // The matrix is singular
            return false;
        }

        t = tmp.elemRowCol[i][i];
        for (size_t k = 0; k < 4; k++) {
            tmp.elemRowCol[i][k] /= t;
            result.elem[i*4+k] /= t;
        }
        for (size_t j = 0; j < 4; j++) {
            if (j != i) {
                t = tmp.elemRowCol[j][i];

                for (size_t k = 0; k < 4; k++) {
                    tmp.elemRowCol[j][k] -= tmp.elemRowCol[i][k]*t;
                    result.elem[j*4+k] -= result.elem[i*4+k]*t;
                }
            }
        }
    }
    return true;
}

};
#endif //TGT_MATRIX_H
