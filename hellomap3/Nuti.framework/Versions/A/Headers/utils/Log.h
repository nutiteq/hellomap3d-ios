#ifndef LOG_H_
#define LOG_H_

#include <atomic>
#include <mutex>
#include <string>

namespace Nuti {

class Log {
public:
	static void Fatal(const char* text, ...);
	static void Error(const char* text, ...);
	static void Warn(const char* text, ...);
	static void Info(const char* text, ...);
	static void Debug(const char* text, ...);

	static void SetShowError(bool showError);
	static void SetShowWarn(bool showWarn);
	static void SetShowInfo(bool showError);
	static void SetShowDebug(bool showError);

private:
	static const std::string SDK_3D_TAG;

	static std::atomic<bool> _ShowError;
	static std::atomic<bool> _ShowWarn;
	static std::atomic<bool> _ShowInfo;
	static std::atomic<bool> _ShowDebug;
};

}

#endif
