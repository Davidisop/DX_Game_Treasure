#include "xStd.h"
class sprite
{
public:
	bool GameDataLoad(const TCHAR* pszLoad)
	{
		TCHAR pBuffer[256] = { 0 };
		TCHAR pTemp[256] = { 0 };
		int iNumSprite = 0;
		FILE* fp_src;
		_wfopen_s(&fp_src, pszLoad, _T("rt"));
		if (fp_src == NULL) return false;
		_fgetts(pBuffer, _countof(pBuffer), fp_src);
		_stscanf_s(pBuffer, _T("%s %d"), pTemp, _countof(pTemp), &iNumSprite);
		Sprite_Sturcture.resize(iNumSprite);

		for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
		{

			int iNumFrame = 0;
			_fgetts(pBuffer, _countof(pBuffer), fp_src);
			_stscanf_s(pBuffer, _T("%s %d"), pTemp, _countof(pTemp), &iNumFrame);
			RECT rt;
		
			for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
			{

				_fgetts(pBuffer, _countof(pBuffer), fp_src);
				_stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, _countof(pTemp),
					&rt.left, &rt.top, &rt.right, &rt.bottom);
				Sprite_Sturcture[iCnt].push_back(rt);
			}
		}

		fclose(fp_src);
		return true;
	}
	// 전체 스프라이트 로드

public:
	Select_Animation_Vector Sprite_Sturcture;


public:

	sprite()
	{
		GameDataLoad(L"sprite.txt");
	}

};