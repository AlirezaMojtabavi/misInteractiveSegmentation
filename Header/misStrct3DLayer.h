
#include "misStrctLayer.h"


class    misStrct3DLayer :public  misStrctLayer
{
public:
	misStrct3DLayer();
	misOpenglTexture* GetTexure() const;
	void SetTexure(misOpenglTexture* val);
private:

	misOpenglTexture* m_pTexure;



	
};
