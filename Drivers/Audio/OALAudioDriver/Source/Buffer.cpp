#include "../Internal/Buffer.h"

namespace CB{
	COALBuffer::COALBuffer(CRefPtr<COALDevice> pDevice, const Audio::BufferFormat uFormat, const uint32 uFrequency, const void* pData, const uint32 uLength) :
		Manage::IManagedObject<COALDevice, COALBuffer>(pDevice),
		m_uFormat(uFormat),
		m_uFrequency(uFrequency),
		m_uBuffer(0)
	{
		alGenBuffers(1, &this->m_uBuffer);

		if(pData != 0){
			
		}
	}

}