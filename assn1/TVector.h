#pragma once

template <class T, int n>
class TVector
{
	T arr[n];
public:
	const T& operator[](int i) const { return arr[i]; }
	T& operator[](int i) { return arr[i]; }


	explicit TVector(T a, ...)
	{
		va_list vl;
		va_start(vl, a);
		(*this)[0] = a;
		for (int i = 1; i < n; i++)
		{
			(*this)[i] = va_arg(vl, T);
		}
		va_end(vl);
	}
	template <class K>
	explicit TVector(const TVector<K, n>& Q)
	{
		for (int i = 0; i < n; i++)
		{
			(*this)[i] = Q[i];
		}
	}
	TVector() {}
	~TVector() {}

	//aux
	void clear(T a)
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = a;
		}
	}
	void set(T a, ...)
	{
		va_list vl;
		va_start(vl, a);
		(*this)[0] = a;
		for (int i = 1; i < n; i++)
		{
			(*this)[i] = va_arg(vl, T);
		}
		va_end(vl);
	}
	void operator=(const TVector<T, n>& P)
	{
		for (int i = 0; i < n; i++)
		{
			(*this)[i] = P[i];
		}
	}
	TVector<T, n> operator+(const TVector<T, n>& P)
	{
		TVector<T, n> K;
		for (int i = 0; i < n; i++)
		{
			K[i] = (*this)[i] + P[i];
		}
		return K;
	}
	TVector<T, n> operator*(double t)
	{
		TVector<T, n> K;
		for (int i = 0; i < n; i++)
		{
			K[i] = (*this)[i] * t;
		}
		return K;
	}
	bool operator==(const TVector<T, n>& P)
	{
		for (int i = 0; i < n; i++)
		{
			if ((*this)[i] != P[i]) return false;
		}
		return true;
	}
	bool operator!=(const TVector<T, n>& P)
	{
		return !((*this) == P);
	}
	///
	void operator +=(const TVector<T, n>& P)
	{
		for (int i = 0; i < n; i++)
		{
			(*this)[i] = (*this)[i] + P[i];
		}
	}
	void operator -=(const TVector<T, n>& P)
	{
		for (int i = 0; i < n; i++)
		{
			(*this)[i] = (*this)[i] - P[i];
		}
	}
	void operator *=(const TVector<T, n>& P)
	{
		for (int i = 0; i < n; i++)
		{
			(*this)[i] = (*this)[i] * P[i];
		}
	}
	void operator /=(const TVector<T, n>& P)
	{
		for (int i = 0; i < n; i++)
		{
			(*this)[i] = (*this)[i] / P[i];
		}
	}
};


class T2Double : public TVector<double, 2>
{
public:
	T2Double(void) {}
	T2Double(double a, double b) { (*this)[0] = a, (*this)[1] = b; }
	T2Double(const T2Double& x) { TVector<double, 2>::operator=(x); }
	void operator=(const T2Double& x) { TVector<double, 2>::operator=(x); }

};