#ifndef CMAP_H
#define CMAP_H

#include "CRectangle.h"

extern CTexture Texture;

class CMap : public CRectangle {
public:
	int mFy;
	int GameClear;
	void Render() {
		if (mEnabled) {
			CRectangle::Render(Texture, 48, 95, 191, 144);
		}
	}
};

#endif
