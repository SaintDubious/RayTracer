#ifndef INCLUDED_COLOR
#define INCLUDED_COLOR

#include <cstdint>
#include <algorithm>

class Color
{
public:
	Color()
		: m_Red( 0 )
		, m_Green( 0 )
		, m_Blue( 0 )
	{}

	Color( uint8_t Intensity )
		: m_Red( Intensity )
		, m_Green( Intensity )
		, m_Blue( Intensity )
	{}

	Color( uint8_t R, uint8_t G, uint8_t B )
		: m_Red( R )
		, m_Green( G )
		, m_Blue( B )
	{}

	~Color()
	{}

	static const int	BITS_PER_PIXEL = 24;

	uint8_t				Red() const { return m_Red; }
	uint8_t				Green() const { return m_Green; }
	uint8_t				Blue() const { return m_Blue; }

private:
	uint8_t				m_Red;
	uint8_t				m_Green;
	uint8_t				m_Blue;
};

inline Color operator+ (const Color& A, const Color& B)
{
	return Color( std::min( A.Red() + B.Red(), 255 ), std::min( A.Green() + B.Green(), 255 ), std::min( A.Blue() + B.Blue(), 255 ) );
}

inline Color operator* (const Color& A, float Scalar )
{
	return Color( std::min( static_cast<int>(A.Red() * Scalar), 255 ), 
			      std::min( static_cast<int>(A.Green() * Scalar), 255 ), 
				  std::min( static_cast<int>(A.Blue() * Scalar), 255 ) );
}

#endif
