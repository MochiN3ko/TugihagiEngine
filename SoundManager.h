#pragma once

#include<xaudio2.h>
#include<wrl.h>


class SoundManager
{
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public:	//インナークラス
	class XAudio2VoiceCallback :public IXAudio2VoiceCallback
	{
	public:
		// ボイス処理パスの開始時
	//STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
		void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
		// ボイス処理パスの終了時
		STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
		// バッファストリームの再生が終了した時
		STDMETHOD_(void, OnStreamEnd) (THIS) {};
		// バッファの使用開始時
		STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
		// バッファの末尾に達した時
		STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {
			// バッファを解放する
			delete[] pBufferContext;
		};
		// 再生がループ位置に達した時
		STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
		// ボイスの実行エラー時
		STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
	};
	//チャンクヘッダ
	struct Chunk
	{
		char id[4];		//チャンクごとのID
		int size;	//チャンクサイズ
	};
	//RIFFヘッダチャンク
	struct RiffHeader
	{
		Chunk chunk;	//"RIFF"
		char type[4];	//"WAVE"
	};
	//FMTチャンク
	struct FormatChunk
	{
		Chunk chunk;	//"fmt"
		WAVEFORMAT fmt;	//波形フォーマット
	};

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// サウンドファイルの読み込みと再生
	/// </summary>
	/// <param name="filename">Waveファイル名</param>
	void PlayWave(const char* filename);
private:	//メンバ変数
	//XAudio2のインスタンス
	ComPtr<IXAudio2> xAudio2;
	//マスターボイス
	IXAudio2MasteringVoice* masterVoice;

	XAudio2VoiceCallback voiceCallback;

};

