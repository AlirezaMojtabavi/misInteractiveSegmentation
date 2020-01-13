#pragma once

class  misShape
{
public:
	misShape(void);
	~misShape(void);

	void SetCenter(const double Center[3]);
	inline void SetMaxAcceptableMovementX(const double MaxAcceptableMovementX){m_MaxAcceptableMovementX = MaxAcceptableMovementX;}
	inline void SetMaxAcceptableMovementY(const double MaxAcceptableMovementY){m_MaxAcceptableMovementY = MaxAcceptableMovementY;}
	inline void SetMaxAcceptableMovementZ(const double MaxAcceptableMovementZ){m_MaxAcceptableMovementZ = MaxAcceptableMovementZ;}
	inline void SetID(const unsigned ID){m_ID = ID;}
	
	inline double* GetCenter(){return m_Center;} //?
	inline double GetCenterX(){return m_Center[0];}
	inline double GetCenterY(){return m_Center[1];}
	inline double GetCenterZ(){return m_Center[2];}
	
	inline double GetMaxAcceptableMovementX(){return m_MaxAcceptableMovementX;}
	inline double GetMaxAcceptableMovementY(){return m_MaxAcceptableMovementY;}
	inline double GetMaxAcceptableMovementZ(){return m_MaxAcceptableMovementZ;}
	
	inline int GetID(){return m_ID;}
	
	virtual int IsInShape(const double CapturedPoint[3]) = 0;  

protected:
private:
	double m_Center[3];

	double m_MaxAcceptableMovementX;
	double m_MaxAcceptableMovementY;
	double m_MaxAcceptableMovementZ;
	
	int m_ID; 
};

