#include <d3dx9.h>
#include "mydirect3d.h"
#include "texture.h"


// globals
#define TEXTURE_FILENAME_MAX (64)

// texture data struct
typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX];  // path to the texture
	int width;  // width of texture
	int height; // height of texture
} TextureFile;


// texture path
static const TextureFile g_TextureFiles[] = {
	{"asset/texture/sand.jpg",		1024, 1024},
	{"asset/texture/title.dds",		1920, 1080},
	{"asset/texture/crosshair.png",	144, 144},
	{"asset/texture/score.png",		1025,  503},
	{"asset/texture/result.png",	1920, 1080},
	{"asset/texture/mountain.png",	900, 600},
	{"asset/texture/sky.png",	900, 600},
};

// texture file count
static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);
// static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_TextureFiles); // required Windows.h

// check if texture enum length == texture file count
static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");



// stores texture data
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {};




// load textures
int Texture_Load(void)
{   
    LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if( !pDevice ) {
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if (D3DXCreateTextureFromFileEx(pDevice, g_TextureFiles[i].filename, 
			0, 0, 
			1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 
			D3DCOLOR_ARGB(150, 100, 100, 100), NULL, NULL, &g_pTextures[i]))
			failed_count++;
	}

	return failed_count;
}

// release memory
void Texture_Release(void)
{
	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( g_pTextures[i] ) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

// retuen texture of given index
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_pTextures[index];
}

// return width
int Texture_GetWidth(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].width;
}

// return height
int Texture_GetHeight(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].height;
}
