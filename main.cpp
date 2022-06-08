#include"DirectXGame.h"

#ifdef _DEBUG
int main()
{
#else
//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	DirectXGame sampleScene;
	sampleScene.Run();
	return 0;
}