#pragma once

#include<xaudio2.h>
#include<wrl.h>


class SoundManager
{
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public:	//�C���i�[�N���X
	class XAudio2VoiceCallback :public IXAudio2VoiceCallback
	{
	public:
		// �{�C�X�����p�X�̊J�n��
	//STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
		void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
		// �{�C�X�����p�X�̏I����
		STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
		// �o�b�t�@�X�g���[���̍Đ����I��������
		STDMETHOD_(void, OnStreamEnd) (THIS) {};
		// �o�b�t�@�̎g�p�J�n��
		STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
		// �o�b�t�@�̖����ɒB������
		STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {
			// �o�b�t�@���������
			delete[] pBufferContext;
		};
		// �Đ������[�v�ʒu�ɒB������
		STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
		// �{�C�X�̎��s�G���[��
		STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
	};
	//�`�����N�w�b�_
	struct Chunk
	{
		char id[4];		//�`�����N���Ƃ�ID
		int size;	//�`�����N�T�C�Y
	};
	//RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		Chunk chunk;	//"RIFF"
		char type[4];	//"WAVE"
	};
	//FMT�`�����N
	struct FormatChunk
	{
		Chunk chunk;	//"fmt"
		WAVEFORMAT fmt;	//�g�`�t�H�[�}�b�g
	};

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �T�E���h�t�@�C���̓ǂݍ��݂ƍĐ�
	/// </summary>
	/// <param name="filename">Wave�t�@�C����</param>
	void PlayWave(const char* filename);
private:	//�����o�ϐ�
	//XAudio2�̃C���X�^���X
	ComPtr<IXAudio2> xAudio2;
	//�}�X�^�[�{�C�X
	IXAudio2MasteringVoice* masterVoice;

	XAudio2VoiceCallback voiceCallback;

};

