#include "stdafx.h"
#include "GameLevel.h"

#include "TGA.h"


namespace gamelevel
{



	class IpSimpleVertex
	{
	public:
		IpSimpleVertex(void){}

		IpSimpleVertex(float x, float y, float z, float u, float v)
		{
			set(x, y, z, u, v);
		}

		void set(float x, float y, float z, float u, float v)
		{
			mPosition = glm::vec3(x, y, z);
			mTexel = glm::vec2(u, v);
		}

		glm::vec3  mPosition;
		glm::vec2  mTexel;
	};

	int getInt(const char * &data)
	{
		int *v = (int *)data;
		data += sizeof(int);
		return *v;
	}

	bool getBool(const char * &data)
	{
		bool *v = (bool *)data;
		data += sizeof(bool);
		return *v;
	}

	class Texture
	{
	public:
		void init(const char * &data)
		{
			mX = getInt(data);
			mY = getInt(data);
			mWidth = getInt(data);
			mHeight = getInt(data);
			mFlipped = getBool(data);
		}

		int mX;
		int mY;
		int mWidth;
		int mHeight;
		bool mFlipped;
	};

	class Tile
	{
	public:
		void init(const char * &data, int &maxLayer)
		{
			mIndex = getInt(data) - 1;
			mX = getInt(data);
			mY = getInt(data);
			mLayer = getInt(data);
			if (mLayer > maxLayer)
			{
				maxLayer = mLayer;
			}
		}

		int mIndex;
		int mX;
		int mY;
		int mLayer;
	};


	typedef std::vector< IpSimpleVertex > IpSimpleVertexVector;
	typedef std::vector< unsigned short > GameIndexVector;

	class GameLayer
	{
	public:
		GameLayer(void)
		{
			mIndexBuffer = 0;
			mVertexBuffer = 0;
		}

		~GameLayer(void)
		{
			if (mIndexBuffer)  mIndexBuffer->release();
			if (mVertexBuffer) mVertexBuffer->release();
		}

		void addTile(const Tile &t, const Texture &tex, float recipw, float reciph)
		{
			addTile(t.mX, t.mY, tex, recipw, reciph);
		}

		void addTile(int tx, int ty, const Texture &tex, float recipw, float reciph)
		{
			unsigned short index = mVertices.size();

			if (tex.mFlipped)
			{
				float x1 = (float)tx;
				float y1 = (float)ty;

				float x2 = (float)(tx + tex.mWidth);
				float y2 = (float)(ty + tex.mHeight);

				float tx1 = (float)tex.mX;
				float ty1 = (float)tex.mY;
				float tx2 = (float)(tex.mX + tex.mHeight);
				float ty2 = (float)(tex.mY + tex.mWidth);


				tx1 *= recipw;
				tx2 *= recipw;

				ty1 *= reciph;
				ty2 *= reciph;

				IpSimpleVertex v1(x1, y1, 0, tx1, ty1);
				IpSimpleVertex v2(x2, y1, 0, tx1, ty2);
				IpSimpleVertex v3(x2, y2, 0, tx2, ty2);
				IpSimpleVertex v4(x1, y2, 0, tx2, ty1);

				mVertices.push_back(v1);
				mVertices.push_back(v2);
				mVertices.push_back(v3);
				mVertices.push_back(v4);

			}
			else
			{
				float x1 = (float)tx;
				float y1 = (float)ty;

				float x2 = (float)(tx + tex.mWidth);
				float y2 = (float)(ty + tex.mHeight);

				float tx1 = (float)tex.mX;
				float ty1 = (float)tex.mY;
				float tx2 = (float)(tex.mX + tex.mWidth);
				float ty2 = (float)(tex.mY + tex.mHeight);

				tx1 *= recipw;
				tx2 *= recipw;
				ty1 *= reciph;
				ty2 *= reciph;

				IpSimpleVertex v1(x1, y1, 0, tx1, ty1);
				IpSimpleVertex v2(x2, y1, 0, tx2, ty1);
				IpSimpleVertex v3(x2, y2, 0, tx2, ty2);
				IpSimpleVertex v4(x1, y2, 0, tx1, ty2);


				mVertices.push_back(v1);
				mVertices.push_back(v2);
				mVertices.push_back(v3);
				mVertices.push_back(v4);
			}

			mIndices.push_back(index + 0);
			mIndices.push_back(index + 1);
			mIndices.push_back(index + 2);

			mIndices.push_back(index + 0);
			mIndices.push_back(index + 2);
			mIndices.push_back(index + 3);


		}

		void createBuffers(void)
		{
			if (!mVertices.empty())
			{
				mVertexBuffer = gIphoneGraphics->createIphoneVertexBuffer(IVF_POSITION | IVF_TEXCOORD0, &mVertices[0], mVertices.size(), false);
				mIndexBuffer = gIphoneGraphics->createIphoneIndexBuffer(&mIndices[0], mIndices.size(), false);
				mVertices.clear();
				mIndices.clear();
			}
		}

		void render(const glm::mat4 &world)
		{
			if (mVertexBuffer && mIndexBuffer)
			{

				gIphoneGraphics->renderTriangleList(world, mVertexBuffer, mIndexBuffer);
#if 0
				IphoneTexture *tex = gIphoneGraphics->getActiveTexture();
				gIphoneGraphics->setActiveTexture(0);
				gIphoneGraphics->setWireframe(true);
				gIphoneGraphics->renderTriangleList(world, mVertexBuffer, mIndexBuffer);
				gIphoneGraphics->setWireframe(false);
				gIphoneGraphics->setActiveTexture(tex);
#endif
			}
		}


		IphoneVertexBuffer *mVertexBuffer;
		IphoneIndexBuffer  *mIndexBuffer;
		IpSimpleVertexVector    mVertices;
		GameIndexVector     mIndices;
	};


	class MyGameLevel : public GameLevel
	{
	public:
		MyGameLevel(const char *data)
		{
			mZoomLevel = 1;
			mOrientation = 0;
			mPosition = glm::vec3(0, 0, 0);
			mTiles = 0;
			mTextures = 0;
			mIphoneTexture = 0;
			mMaxLayer = 0;
			if (data[0] == 'T' &&
				data[1] == 'I' &&
				data[2] == 'L' &&
				data[3] == 'E')
			{
				data += 4;
				mTextureCount = getInt(data);
				mTextures = new Texture[mTextureCount];
				for (int i = 0; i<mTextureCount; i++)
				{
					mTextures[i].init(data);
				}
				mBackgroundId = getInt(data);
				mTileCount = getInt(data);
				mTiles = new Tile[mTileCount];
				for (int i = 0; i<mTileCount; i++)
				{
					mTiles[i].init(data, mMaxLayer);
				}
				unsigned int tlen = getInt(data);
				if (tlen > 0)
				{
					std::string fileToRead;
					int imgBpp = -1;
					const unsigned char *image = (unsigned char*)LoadTGA(fileToRead.c_str(), (int*)(&mTextureWidth), (int*)(&mTextureHeight), &imgBpp);

					// ready to load PNG here..
					//const unsigned char *image = loadPng((const unsigned char *)data, tlen, mTextureWidth, mTextureHeight);
					if (image)
					{
						mIphoneTexture = gIphoneGraphics->createIphoneTexture(image, mTextureWidth, mTextureHeight);
						delete []image;
					}
				}
				mMaxLayer++;
				mLayers = new GameLayer[mMaxLayer];

				float recipw = 1.0f / (float)mTextureWidth;
				float reciph = 1.0f / (float)mTextureHeight;

				for (int i = 0; i<mTileCount; i++)
				{
					Tile &t = mTiles[i];
					Texture &tex = mTextures[t.mIndex];
					mLayers[t.mLayer].addTile(t, tex, recipw, reciph);
				}
				for (int i = 0; i<mMaxLayer; i++)
				{
					mLayers[i].createBuffers();
				}

				if (mBackgroundId)
				{
					Texture &t = mTextures[mBackgroundId - 1];
					mBackgroundLayer.addTile(0, 0, t, recipw, reciph);
					mBackgroundLayer.createBuffers();
				}

			}
		}

		~MyGameLevel(void)
		{
			delete[]mTextures;
			delete[]mTiles;
			if (mIphoneTexture)
			{
				mIphoneTexture->release();
			}
		}

		virtual void render(const glm::mat4 &world)
		{
			if (mIphoneTexture)
			{
				glm::mat4 combined;
				combined = (world * mWorld);

				gIphoneGraphics->setAlphaTest(false, 0.1f);
				gIphoneGraphics->setZenable(false);
				gIphoneGraphics->setActiveTexture(mIphoneTexture);
				mBackgroundLayer.render(combined);
				gIphoneGraphics->setAlphaTest(true, 0.1f);

				for (int i = 0; i<mMaxLayer; i++)
				{
					mLayers[i].render(combined);
				}
			}
		}

		/*
		int     sendIphoneCommand(IphoneCommand command,            // the command sent
			bool commandState,           // state true/false
			int commandValue,             // optional integer command value
			float commandFloatValue,          // optional float value
			void *commandData)               // optional additional command data. Not const, because it might possible be used to return data values.
		{
			int ret = 0;

#define MOVE_DELTA 4

			switch (command)
			{
			case IC_ZOOM_IN:
				mZoomLevel += 0.1f;
				break;
			case IC_ZOOM_OUT:
				mZoomLevel -= 0.1f;
				break;
			case IC_LEFT:
				mPosition.x += MOVE_DELTA;
				break;
			case IC_RIGHT:
				mPosition.x -= MOVE_DELTA;
				break;
			case IC_UP:
				mPosition.y += MOVE_DELTA;
				break;
			case IC_DOWN:
				mPosition.y -= MOVE_DELTA;
				break;
			}

			mWorld.id();
			mWorld.setScale(mZoomLevel, mZoomLevel, mZoomLevel);
			mWorld.setToPosition(mPosition);

			return ret;
		}*/

	private:
		int             mMaxLayer;
		int             mTextureCount;
		Texture        *mTextures;
		int             mBackgroundId;
		int             mTileCount;
		Tile           *mTiles;
		IphoneTexture  *mIphoneTexture;
		GameLayer       mBackgroundLayer;
		GameLayer      *mLayers;
		unsigned int    mTextureWidth;
		unsigned int    mTextureHeight;
		glm::mat4       mWorld;
		glm::vec3       mPosition;
		float           mZoomLevel;
		int             mOrientation;

	};


	GameLevel * createGameLevel(const char *data)
	{
		MyGameLevel *ret = new MyGameLevel(data);
		return static_cast< GameLevel *>(ret);
	}

	void        releaseGameLevel(GameLevel *g)
	{
		MyGameLevel *mg = static_cast< MyGameLevel *>(g);
		delete mg;
	}


}