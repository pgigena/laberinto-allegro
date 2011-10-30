#include "ResBitmap.h"

CResBitmap::CResBitmap(string sPath)
{
	m_sPath = sPath;
}

CResBitmap::CResBitmap()
{
}

CResBitmap::~CResBitmap()
{
}

int CResBitmap::load() {
	// Si ya estaba creado retorna -1
	if (m_bmpImage) {
		return -1;
	}

	m_bmpImage = al_load_bitmap(m_sPath.c_str());

	// No se generó
	if (!m_bmpImage) {
		return 1;
	}

	// OK
	return 0;
}

int CResBitmap::unload() {
	al_destroy_bitmap(m_bmpImage);

	return 0;
}

ALLEGRO_BITMAP * CResBitmap::getResource() {
	return m_bmpImage;
}