#pragma once
#include "e2dbase.h"
#include <random>

namespace e2d
{

class MusicManager;
class InputManager;
class ColliderManager;

// 随机数产生器
class Random
{
public:
	// 取得范围内的一个整型随机数
	template<typename T>
	static inline T range(T min, T max) 
	{ 
		return e2d::Random::__randomInt(min, max); 
	}

	// 取得范围内的一个浮点数随机数
	static inline double range(float min, float max) 
	{ 
		return e2d::Random::__randomReal(min, max); 
	}

	// 取得范围内的一个浮点数随机数
	static inline double range(double min, double max) 
	{ 
		return e2d::Random::__randomReal(min, max); 
	}

private:
	template<typename T>
	static T __randomInt(T min, T max)
	{
		std::uniform_int_distribution<T> dist(min, max);
		return dist(Random::__getEngine());
	}

	template<typename T>
	static T __randomReal(T min, T max)
	{
		std::uniform_real_distribution<T> dist(min, max);
		return dist(Random::__getEngine());
	}

	// 获取随机数产生器
	static std::default_random_engine &__getEngine();
};


// 音乐播放器
class Music :
	public Object
{
	friend Game;

public:
	Music();

	Music(
		String strFileName	/* 音乐文件路径 */
	);

	virtual ~Music();

	// 打开音乐文件
	bool open(
		String strFileName	/* 音乐文件路径 */
	);

	// 播放
	bool play(
		int nLoopCount = 0	/* 重复播放次数，设置 -1 为循环播放 */
	);

	// 暂停
	void pause();

	// 继续
	void resume();

	// 停止
	void stop();

	// 关闭音乐文件
	void close();

	// 获取音乐播放状态
	bool isPlaying() const;

	// 获取音量
	double getVolume() const;

	// 获取频率比
	double getFrequencyRatio() const;

	// 设置音量
	bool setVolume(
		double fVolume			/* 音量范围为 -224 ~ 224，其中 0 是静音，1 是正常音量 */
	);

	// 设置频率比
	bool setFrequencyRatio(
		double fFrequencyRatio	/* 频率比范围为 1/1024.0f ~ 1024.0f，其中 1.0 为正常声调 */
	);

private:
	static bool __init();

	static void __uninit();

#if HIGHER_THAN_VS2010

public:
	// 获取 IXAudio2 对象
	static IXAudio2 * getIXAudio2();

	// 获取 IXAudio2MasteringVoice 对象
	static IXAudio2MasteringVoice * getIXAudio2MasteringVoice();

	// 获取 IXAudio2SourceVoice 对象
	IXAudio2SourceVoice* getIXAudio2SourceVoice() const;

protected:
	bool _readMMIO();

	bool _resetFile();

	bool _read(
		BYTE* pBuffer,
		DWORD dwSizeToRead
	);

	bool _findMediaFileCch(
		wchar_t* strDestPath,
		int cchDest,
		const wchar_t * strFilename
	);

protected:
	bool m_bOpened;
	mutable bool m_bPlaying;
	DWORD m_dwSize;
	CHAR* m_pResourceBuffer;
	BYTE* m_pbWaveData;
	HMMIO m_hmmio;
	MMCKINFO m_ck;
	MMCKINFO m_ckRiff;
	WAVEFORMATEX* m_pwfx;
	IXAudio2SourceVoice* m_pSourceVoice;

#else

protected:
	void _sendCommand(int nCommand, DWORD_PTR param1 = 0, DWORD_PTR parma2 = 0);

	static LRESULT WINAPI MusicProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

protected:
	MCIDEVICEID m_dev;
	HWND        m_wnd;
	UINT		m_nMusicID;
	bool        m_bPlaying;
	int			m_nRepeatTimes;

#endif
};


// 定时器
class Timer
{
	friend Game;

public:
	// 启动定时器
	static void start(
		Function func,			/* 执行函数 */
		String name				/* 定时器名称 */
	);

	// 启动定时器
	static void start(
		Function func,			/* 执行函数 */
		double delay = 0,		/* 时间间隔（秒） */
		int times = -1,			/* 执行次数（设 -1 为永久执行） */
		bool paused = false,	/* 是否暂停 */
		String name = L""		/* 定时器名称 */
	);

	// 启动仅执行一次的定时器
	static void startOnce(
		Function func,		/* 执行的函数 */
		double timeOut		/* 等待的时长（秒） */
	);

	// 暂停具有相同名称的定时器
	static void pause(
		String name
	);

	// 继续具有相同名称的定时器
	static void resume(
		String name
	);

	// 停止具有相同名称的定时器
	static void stop(
		String name
	);

	// 暂停所有定时器
	static void pauseAll();

	// 继续所有定时器
	static void resumeAll();

	// 停止所有定时器
	static void stopAll();

private:
	// 更新定时器
	static void __update();

	// 重置定时器状态
	static void __resetAll();

	// 清空定时器
	static void __uninit();
};


// 数据管理工具
class Data
{
public:
	// 保存 int 类型的值
	static void saveInt(
		String key,					/* 键值 */
		int value,					/* 数据 */
		String field = L"Defalut"	/* 字段名称 */
	);

	// 保存 double 类型的值
	static void saveDouble(
		String key,					/* 键值 */
		double value,				/* 数据 */
		String field = L"Defalut"	/* 字段名称 */
	);

	// 保存 bool 类型的值
	static void saveBool(
		String key,					/* 键值 */
		bool value,					/* 数据 */
		String field = L"Defalut"	/* 字段名称 */
	);

	// 保存 字符串 类型的值
	static void saveString(
		String key,					/* 键值 */
		String value,				/* 数据 */
		String field = L"Defalut"	/* 字段名称 */
	);

	// 获取 int 类型的值
	// （若不存在则返回 defaultValue 参数的值）
	static int getInt(
		String key,					/* 键值 */
		int defaultValue,			/* 默认值 */
		String field = L"Defalut"	/* 字段名称 */
	);

	// 获取 double 类型的值
	// （若不存在则返回 defaultValue 参数的值）
	static double getDouble(
		String key,					/* 键值 */
		double defaultValue,		/* 默认值 */
		String field = L"Defalut"	/* 字段名称 */
	);

	// 获取 bool 类型的值
	// （若不存在则返回 defaultValue 参数的值）
	static bool getBool(
		String key,					/* 键值 */
		bool defaultValue,			/* 默认值 */
		String field = L"Defalut"	/* 字段名称 */
	);

	// 获取 字符串 类型的值
	// （若不存在则返回 defaultValue 参数的值）
	static String getString(
		String key,					/* 键值 */
		String defaultValue,		/* 默认值 */
		String field = L"Defalut"	/* 字段名称 */
	);

	// 修改数据文件的名称
	static void setDataFileName(
		String strFileName			/* 文件名称 */
	);

	// 获取数据文件的完整路径
	static String getDataFilePath();
};


// 路径工具
class Path
{
public:
	// 获取系统的 AppData Local 路径
	static String getLocalAppDataPath();

	// 获取临时文件目录
	static String getTempPath();

	// 获取数据的默认保存路径
	static String getDefaultSavePath();

	// 获取文件扩展名
	static String getFileExtension(
		String filePath
	);

	// 打开保存文件对话框
	static String getSaveFilePath(
		const String title = L"保存到",		/* 对话框标题 */
		const String defExt = L""			/* 默认扩展名 */
	);

	// 创建文件夹
	static bool createFolder(
		String strDirPath	/* 文件夹路径 */
	);
};

}