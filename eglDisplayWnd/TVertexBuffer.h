
#pragma once

#include "IphoneGraphics.h"
#include <vector>

template<class T> 
class TVertexBuffer : public std::vector<T>
{
public:
	TVertexBuffer()
	{
		VertexBuffer = NULL;
	}

	virtual ~TVertexBuffer()
	{
		clear();
		Release();
	}

	// InSize is the maximum size the vertex buffer will ever grow to.  Leaving it at zero will create a vertex buffer at this arrays current size.
	// Setting InSize to something larger than zero allows you to pad the vertex buffer.
	virtual bool Create(int InSize)
	{
		if (!InSize)
			InSize = size();

		if (!InSize)	
			return 1;

		VOID* Buffer = NULL;
		VertexBuffer = gIphoneGraphics->createIphoneVertexBuffer(IVF_POSITION | IVF_TEXCOORD0, Buffer, InSize*GetVertexSize(), false);

		return (VertexBuffer !=NULL);
	}

	virtual bool Upload()
	{
		if (!size())	return 1;

		int vCount = size()*GetVertexSize();

		VOID* Buffer;
		Buffer = VertexBuffer->lock(); //->Lock(0, size()*GetVertexSize(), (byte**)&Buffer, D3DLOCK_DISCARD);
		
		//memcpy(((T*)Buffer), this->data, size()*GetVertexSize());
		
		//std::copy((T*)Buffer, &data[0] + 1, begin());
		VertexBuffer->unlock(vCount);

		/*int numBytes = vbuffer->GetNumBytes();
		char* srcData = vbuffer->GetData();
		void* trgData = Lock(vbuffer, Buffer::BL_WRITE_ONLY);
		memcpy(trgData, srcData, numBytes);
		Unlock(vbuffer);*/


		return 1;
	}


	virtual void Release()
	{
		if (VertexBuffer)
			VertexBuffer->release();
		VertexBuffer = NULL;
	}

	inline int GetVertexSize()
	{
		return sizeof(T);
	}
	inline DWORD GetFVF()
	{	
		return T::FVF;
	}

	void SetPrimType(IphoneVertexFormat InPrimType)
	{
		PrimType = InPrimType;
	}


	virtual int GetPrimCount()
	{
		switch (PrimType)
		{
	/*	case D3DPT_TRIANGLELIST:	return size() / 3;
		case D3DPT_TRIANGLEFAN:		return size() - 2;
		case D3DPT_TRIANGLESTRIP:	return size() - 2;
		case D3DPT_LINESTRIP:		return size() - 1;
		case D3DPT_LINELIST:		return size() / 2;
		case D3DPT_POINTLIST:		return size();*/
		}

		_ASSERT(0);	// Unknown primitive type
		return 0;
	}


	IphoneVertexBuffer*		VertexBuffer;
	IphoneVertexFormat		PrimType;
};
