#include"DirectXGame.h"

#ifdef _DEBUG
int main()
{
#else
//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	DirectXGame sampleScene;
	sampleScene.Run();
	return 0;
}