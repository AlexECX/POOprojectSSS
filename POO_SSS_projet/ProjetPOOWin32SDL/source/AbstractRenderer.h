#pragma once
class AbstractRenderer
{
public:
	AbstractRenderer();
	~AbstractRenderer();

	void RenderEntity(categorie TextureNum, int x, int y) = 0;
	void RenderScore(int score) = 0;
	void MakeAnimationRequest(categorie TextureNum, int x, int y) = 0;
	void RenderEventAnimations() = 0;
	void RenderClear() = 0;
	void RenderPresent() = 0;
};

