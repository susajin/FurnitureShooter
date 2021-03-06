
#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <d3d9.h>


/*------------------------------------------------------------------------------
   テクスチャ列挙型
------------------------------------------------------------------------------*/
// テクスチャ管理番号
typedef enum TextureIndex
{
	TEXTURE_INDEX_GROUND,
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_CROSSHAIR,
	TEXTURE_INDEX_SCORE,
	TEXTURE_INDEX_RESULT,
	TEXTURE_INDEX_MOUNTAIN,
	TEXTURE_INDEX_SKY,

    TEXTURE_INDEX_MAX
};


/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/
// テクスチャの読み込み
//
// 戻り値:読み込めなかった数
//
int Texture_Load(void);

// テクスチャの解放
void Texture_Release(void);

// テクスチャインターフェースの取得
//
// 戻り値:テクスチャインターフェース
//        ただし存在しないindexを指定した場合、NULL
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);

// テクスチャ解像度幅の取得
//
// 引数 ... index テクスチャ管理番号
//
int Texture_GetWidth(TextureIndex index);

// テクスチャ解像度高さの取得
//
// 引数 ... index テクスチャ管理番号
//
int Texture_GetHeight(TextureIndex index);


#endif // TEXTURE_H_
