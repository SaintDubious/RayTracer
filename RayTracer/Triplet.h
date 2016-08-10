#ifndef INCLUDED_TRIPLET
#define INCLUDED_TRIPLET

class Triplet
{
public:
	Triplet()
		: m_X( 0 )
		, m_Y( 0 )
		, m_Z( 0 )
	{}

	Triplet(float x, float y, float z)
		: m_X( x )
		, m_Y( y )
		, m_Z( z )
	{}

	~Triplet()
	{}

	float X() const { return m_X; }
	float Y() const { return m_Y; }
	float Z() const { return m_Z; }

private:
	float m_X;
	float m_Y;
	float m_Z;
};

inline Triplet operator+ (const Triplet &A, const Triplet &B)
{
	return Triplet( A.X()+B.X(), A.Y()+B.Y(), A.Z()+B.Z() );
}

inline Triplet operator- (const Triplet &A, const Triplet &B)
{
	return Triplet( A.X()-B.X(), A.Y()-B.Y(), A.Z()-B.Z() );
}

inline Triplet operator* (const Triplet& A, float Scalar)
{
	return Triplet( A.X()*Scalar, A.Y()*Scalar, A.Z()*Scalar );
}

inline Triplet operator/ (const Triplet& A, float Scalar)
{
	return Triplet( A.X()/Scalar, A.Y()/Scalar, A.Z()/Scalar );
}

inline bool operator== (const Triplet &A, const Triplet &B)
{
	return (A.X()==B.X()) && (A.Y()==B.Y()) && (A.Z()==B.Z());
}

#endif